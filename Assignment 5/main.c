#include "pa5.h"
#include <stdlib.h>

START
{
    int i = 0;
    printf("\n'Convert...' for Conversion\n'Quit' to Quit Program\n\n");
    char sec[1000];
    char tryi;
    while (1)
    {
        tryi = getCommandWord(sec, 1000);
        if (!strcmp(sec, "quit"))
        {
            printf("Ending program...\n");
            break;
        }
        else if (!strcmp(sec, "convert"))
        {
            if (tryi == '\n')
            {
                printf("Be sure to Insert Sufficent Arguments...\n");
            }
            else
            {
                converting();
            }
        }
        else
        {
            printf("Invalid argument...\n");
            while (tryi != '\n')
                tryi = getCommandWord(sec, 1000);
        }
    }
 return 0;
END
