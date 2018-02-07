//
//  hw4
//
//  Created by Dinkar Khattar on 11/1/17.
//  Copyright © 2017 Dinkar Khattar. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/stat.h>
#include<unistd.h>

bool fOption = false;

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

//compare function
int frobcmp(const void* a, const void* b)
{
    const char* x = *(const char**)a;
    const char* y = *(const char**)b;
    
    if (!fOption)
    {
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
    }
    
    else
    {
        while ((*x)!=' ' || (*y)!=' ')
        {
            if (toupper((*x^42))<toupper((*y^42)))
            {
                return -1;
            }
            else if (toupper((*x^42))>toupper((*y^42)))
            {
                return 1;
            }
            else
            {
                x++;
                y++;
            }
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


int main(int argc, char *argv[]) {
    
    if (argc == 3 || argc == 2)
    {
        if (!(strncmp(argv[1], "-f", 2)))
            fOption = true;
    }
    
    struct stat inputFile;
    if(fstat(0,&inputFile) < 0)
    {
        fprintf(stderr, "Error acquiring file information!");
        exit(1);
    }
    
    char **words;
    char *fileData;
    
    size_t w=0;
    
    if(S_ISREG(inputFile.st_mode))
    {
        fileData = (char*)malloc(inputFile.st_size * sizeof(char));
        checkAllocErr(fileData);
        
        ssize_t ret = read(STDIN_FILENO, fileData, inputFile.st_size);
        if (ret<0)
        {
            fprintf(stderr, "Error reading the data");
            exit(1);
        }
        else
        {
            int noOfWords = 0;
            size_t p;
            
            for(p = 0; p < inputFile.st_size; p++)
            {
                if (p==inputFile.st_size - 1)
                {
                    fileData[p]=' ';
                }
                if (fileData[p]==' ')
                {
                    noOfWords++;
                }
            }
            
            words = (char**)malloc(noOfWords * sizeof(char*));
            checkAllocErr(words);
            
            int sawWord = 0;
            
            size_t j;
            
            for(j = 0; j < inputFile.st_size; j++)
            {
                if (sawWord == 0 && fileData[j] != ' ')
                {
                    words[w] = &fileData[j];
                    w++;
                    sawWord = 1;
                }
                else if (sawWord == 1 && fileData[j] == ' ')
                {
                    sawWord = 0;
                }
            }
        }
    }
    
    else
    {
        words = (char**)malloc(sizeof(char*));
        checkAllocErr(words);
    }
    
    //variables to hold each word
    int it = 0;
    char* word;
    word = (char*)malloc(sizeof(char));
    checkAllocErr(word);
    
   
    //variable to read from stdin
    char ch[1], chNext[1];
    
    ssize_t curRet = read(STDIN_FILENO, ch, 1);
    if(curRet < 0)
    {
        fprintf(stderr, "Error while reading file");
        exit(1);
    }
    
    ssize_t nextRet = read(STDIN_FILENO, chNext, 1);
    if(nextRet < 0)
    {
        fprintf(stderr, "Error while reading file");
        exit(1);
    }
    
    while(curRet>0)
    {
        if (ch[0]==' ')
        {
            word[it++] = ' ';
            words[w] = word;
            char** newArr = (char**) realloc(words, (w+2)*sizeof(char*));
            checkAllocErr(newArr);
            
            if (newArr!=NULL)
            {
                words = newArr;
                w++;
                word = NULL;
                word = (char*)malloc(sizeof(char));
            }
            
            if (chNext[0] == EOF)
            {
                break;
            }
            
            it = 0;
            
            ch[0] = chNext[0];
            nextRet = read(STDIN_FILENO, chNext, 1);
            if(nextRet < 0)
            {
                fprintf(stderr, "Error while reading file");
                exit(1);
            }
            
            continue;
        }
        
        if (chNext[0] == EOF && ch[0]!=' ')
        {
            word[it] = ch[0];
            it = it + 1;
            
            word[it++] = ' ';
            words[w] = word;
            char **newArr = (char**) realloc(words, (w+2)*sizeof(char*));
            checkAllocErr(newArr);
            
            if (newArr!=NULL)
            {
                words = newArr;
                w++;
            }
            break;
        }
        
        else if (chNext[0] == EOF && ch[0]==' ')
        {
            continue;
        }
        
        word[it] = ch[0];
        char* newWord = (char*) realloc(word, (it+2)*sizeof(char));
        checkAllocErr(newWord);
        word = newWord;
        
        it = it + 1;
        ch[0] = chNext[0];
        nextRet = read(STDIN_FILENO, chNext, 1);
        if(nextRet < 0)
        {
            fprintf(stderr, "Error while reading file");
            exit(1);
        }
    }
    
    qsort(words, w, sizeof(char*), frobcmp);
    
    size_t m;
    size_t n;
    
    for (m=0; m<w; m++)
    {
        int wordLen = 0;

        for (n=0;; n++)
        {
            wordLen++;
	    if(words[m][n] == ' ')
	    {
		break;
	    }
        }
        if(write(STDOUT_FILENO,words[m], wordLen) == 0)
        {
            fprintf(stderr, "Error while writing");
            exit(1);
        }
    }
        
    free(word);
    free(words);
}
