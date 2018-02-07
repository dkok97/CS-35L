#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//function to check for error in stnadard input
void checkRetErr(ssize_t r)
{
    if (r<0)
    {
        fprintf(stderr, "Reading/Writing error.\n");
        exit(1);
    }
}

char outputChar(char c, const char* from, const char* to, size_t len)
{
    size_t k;
    for (k = 0; k < len; k++)
    {
        if (c==from[k])
        {
            return to[k];
        }
    }
    return c;
}


int main(int argc, const char * argv[])
{
    if (argc!=3)
    {
        fprintf(stderr, "Number of arguements must be 2.\n");
        exit(1);
    }
    
    const char* from = argv[1];
    const char* to = argv[2];
    
    unsigned long f = strlen(from);
    unsigned long t = strlen(to);
    
    if (f!=t)
    {
        fprintf(stderr, "Arguements must be of the same length.\n");
        exit(1);
    }
    
    size_t i;
    size_t j;
    
    for (i = 0; i < f; i++)
    {
        for (j = i+1; j < f; j++)
        {
            if (from[j]==from[i])
            {
                fprintf(stderr, "from must not contain duplicate bytes.\n");
                exit(1);
            }
        }
    }
    
    char ch[1];
    ssize_t r = 0;
    
    for (;;)
    {
        r = read(STDIN_FILENO, ch, 1);
        checkRetErr(r);
        
        if (!r) break;
        
        ch[0]=outputChar(ch[0], from, to, f);
        r = write(STDOUT_FILENO, ch, 1);
        checkRetErr(r);
    }
    
    return 0;
}

