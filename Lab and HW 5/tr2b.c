#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//function to check for error in stnadard input
void checkStdInErr()
{
    if (ferror(stdin))
    {
        fprintf(stderr, "Reading from input error.");
        exit(1);
    }
}

void checkStdOutErr()
{
    if (ferror(stdout))
    {
        fprintf(stderr, "Writing to output error.");
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
        fprintf(stderr, "Number of arguements must be 2.");
        exit(1);
    }
    
    const char* from = argv[1];
    const char* to = argv[2];
    
    unsigned long f = strlen(from);
    unsigned long t = strlen(to);
    
    if (f!=t)
    {
        fprintf(stderr, "Arguements must be of the same length.");
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
                fprintf(stderr, "From must not contain duplicate bytes.");
                exit(1);
            }
        }
    }
    
    char ch = '\0';
    
    while (ch!=EOF)
    {
        ch = getchar();
        checkStdInErr();
        putchar(outputChar(ch, from, to, f));
        checkStdOutErr();
    }
    
    return 0;
}
