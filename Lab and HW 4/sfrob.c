//
//  main.c
//  hw4
//
//  Created by Dinkar Khattar on 11/1/17.
//  Copyright © 2017 Dinkar Khattar. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function to check for error in memory allocation
void checkAllocErr(void* p)
{
    if (p==NULL)
    {
        free(p);
        fprintf(stderr, "Memory Allocation Error");
        exit(1);
    }
}

//function to check for error in stnadard input
void checkStdInErr()
{
    if (ferror(stdin))
    {
        fprintf(stderr, "Reading from input error");
        exit(1);
    }
}

//compare function
int frobcmp(const void* a, const void* b)
{
    const char* x = *(const char**)a;
    const char* y = *(const char**)b;
    
    while ((*x)!=' ' || (*y)!=' ')
    {
        if ((*x^42)<(*y^42))
        {
            return -1;
        }
        else if ((*x^42)>(*y^42))
        {
            return 1;
        }
        else
        {
            x++;
            y++;
        }
    }
    
    if (*x!=' ' && *y!=' ')
    {
        return 0;
    }
    else if (*x==' ')
    {
        return -1;
    }
    else if (*y==' ')
    {
        return 1;
    }
    
    return 0;
}

int main() {
    
    //variables to hold each word
    int i = 0;
    char* word;
    word = (char*)malloc(sizeof(char));
    checkAllocErr(word);
    
    //variables to hold all words
    int words = 0;
    char** arrOfWords;
    arrOfWords = (char**)malloc(sizeof(char*));
    checkAllocErr(arrOfWords);
    
    //variable to read from stdin
    char ch, chNext;
    
    ch = getchar();
    checkStdInErr();
    
    chNext = getchar();
    checkStdInErr();
    
    for(; ch!=EOF; )
    {
        checkStdInErr();
        
        if (ch==' ')
        {
            word[i++] = ' ';
            arrOfWords[words] = word;
            char **newArr = (char**) realloc(arrOfWords, (words+2)*sizeof(char*));
            checkAllocErr(newArr);
            
            arrOfWords = newArr;
            words += 1;
            
            word = NULL;
            word = (char*)malloc(sizeof(char));
            
            if (chNext == EOF)
            {
                break;
            }
            
            i = 0;
            
            ch = chNext;
            chNext = getchar();
            checkStdInErr();
            
            continue;
        }
        
        if (chNext == EOF && ch!=' ')
        {
            word[i] = ch;
            i = i + 1;
            
            word[i++] = ' ';
            arrOfWords[words] = word;
            char **newArr = (char**) realloc(arrOfWords, (words+2)*sizeof(char*));
            checkAllocErr(newArr);
            
            arrOfWords = newArr;
            words += 1;
            
            break;
        }
        else if (chNext == EOF && ch==' ')
        {
            continue;
        }
        
        word[i] = ch;
        char* newWord = (char*) realloc(word, (i+2)*sizeof(char));
        checkAllocErr(newWord);
        word = newWord;
        
        i = i + 1;
        ch = chNext;
        chNext = getchar();
        checkStdInErr();
    }
    
    qsort(arrOfWords, words, sizeof(char*), frobcmp);
    
    size_t m;
    int n;
    for (m=0; m<words; m++)
    {
        for (n=0; arrOfWords[m][n]!= ' '; n++)
        {
            putchar(arrOfWords[m][n]);
        }
        
        putchar(' ');
    }
    
    free(word);
    free(arrOfWords);
}

