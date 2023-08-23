#include "pa5.h"
#include <stdlib.h>

void tl5Conv(char *sourceFile, char *targetFile, char *extend)
{
    int i = 0;
    int count = 0;
    int wid = 0;
    char *mast = (char *)malloc(1001);
    const int size = 5;
    char delimit[] = " |";
    char *tab[1000];
    char *token = (char *)malloc(1001);
    int index = 0;
    char line[1000];

    FILE *in = fopen(sourceFile, "r");
    if (in == NULL)
    {
        printf("\nThere is no file by that name...\n");
        printf("\nInsert 'Convert...' for another Conversion\n'Quit' to Quit Program\n\n");
        return;
    }
    for (; fgets(line, 1000, in) != NULL; i++)
    {
        tab[index++] = (char *)malloc(strlen(line) + 1);
        strcpy(tab[index - 1], line);
    }
    fclose(in);
    in = NULL;
    for (i = 0; i < index; i++)
    {
        mast = tab[i];
        for (; *mast != '\0';)
        {
            if (*mast != '|' && *mast != '\n')
            {
                ++count;
            }
            else
            {
                wid = count;
                if (wid != size)
                {
                    printf("\nError, Try Again..\n");
                    return;
                }
                count = 0;
            }
            mast++;
        }
    }

    if (!strcmp(extend, "csv"))
    {
        FILE *out = fopen(targetFile, "w");
        for (i = 0; i < index; i++)
        {
            token = strtok(tab[i], delimit);
            fprintf(out, "%s", token);
            while ((token = strtok(NULL, delimit)))
            {
                if (*token == '\n')
                    fprintf(out, "%s", token);
                else
                    fprintf(out, "%s", token);
            }
        }
        fclose(out);
        out = NULL;
        printf("\nFile Conversion Completed...\n\n");
        printf("\nInsert 'Convert...' for another Conversion\n'Quit' to Quit Program\n\n");
    }
    else if (!strcmp(extend, "tr5"))
    {
        FILE *out = fopen(targetFile, "w");
        for (i = 0; i < index; i++)
        {
            token = strtok(tab[i], delimit);
            fprintf(out, "%-5.5s", token);
            while ((token = strtok(NULL, delimit)))
            {
                if (*token == '\n')
                    fprintf(out, "%s", token);
                else
                    fprintf(out, "%s", token);
            }
        }
        fclose(out);
        out = NULL;
        printf("\nFile Conversion Completed...\n\n");
        printf("\nInsert 'Convert...' for another Conversion\n'Quit' to Quit Program\n\n");
    }
    else
    {
        printf("\nThe file does not work for this application.\n\n");
        return;
    }

}

char getCommandWord(char command[], int length)
{
    int i = 0;
    char com;
    for (i = 0; i < length && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++)
        ;
    com = command[i];
    command[i] = '\0';
    return com;
}

void csvConv(char *sourceFile, char *targetFile, char *extend)
{
    int i = 0;
    char *line[1000];
    char *token = (char*)malloc(1001);
    char info[1000];
    char delimit[] = " ,\n";
    int index = 0;
    FILE *in = fopen(sourceFile, "r");

    if (in == NULL)
    {
        printf("The (IN)File Does Not Exist.\n");
    }

    for (; fgets(info, 1000, in) != NULL; i++)
    {
        line[index++] = (char *)malloc(strlen(info) + 1);
        strcpy(line[index - 1], info);
    }

    fclose(in);
    in = NULL;

    if (!strcmp(extend, "tl5"))
    { 
      FILE *out = fopen(targetFile, "w");
        for (i = 0; i < index; i++)
        { token = strtok(line[i], delimit);
            fprintf(out, "%-5.5s", token);
            while ((token = strtok(NULL, delimit)))
                fprintf(out, "|%-5.5s", token);
            fprintf(out, "\n"); }
        fclose(out);
    }
    else if (!strcmp(extend, "csv")){

        FILE *out = fopen(targetFile, "w");
        for (i = 0; i < index; i++)
        {
            token = line[i];
            for (; *token != '\n';)
            {
                if (*token != ' ' && *token != '\n')
                {
                    fprintf(out, "%c", *token);
                }
              token++;
            }
            fprintf(out, "\n");
        }
        fclose(out);
    }
    else
    {
        printf("File Extension Not Recognized...\n");
        return;
    }
    printf("\nFile Converstion Completed...\n\n");
    printf("\nInsert 'Convert...' for another Conversion\n'Quit' to Quit Program\n\n");
}

void converting()
{
    int i = 0;
    char sourceFile[1000];
    char sourceTarget[1000];
    char command;
    char *exten = NULL;
    char *exten2 = NULL;
    command = getCommandWord(sourceFile, 1000);

    if (command == '\n')
    {
        printf("Invalid number of Arguments; Not Enough.\n");
        return;
    }

    command = getCommandWord(sourceTarget, 1000);

    if (command != '\n')
    {
        printf("Error: Too Many Arguments...\n");
        while (getCommandWord(sourceTarget, 1000) != '\n')
            ;
        return;
    }

    if((exten = strstr(sourceFile, ".")) != NULL){
        exten++;

    }else{
        printf("Unidentified Extension for the Source...\n");
        return;
    }
    if((exten2 = strstr(sourceTarget, ".")) != NULL){
        exten2++;
    }else{
        printf("Unidentified Extension for the Target File...\n");
        return;
    }
    if (!strcmp(exten, "csv"))
    {
        
        csvConv(sourceFile, sourceTarget, exten2);
    }
    else if (!strcmp(exten, "tl5"))
    {
        tl5Conv(sourceFile, sourceTarget, exten2);
    }
    else
    {
        printf("Extension not Recognized...\n");
        return;
    }
}