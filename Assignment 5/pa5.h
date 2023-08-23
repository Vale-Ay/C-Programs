#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START int main(void)
#define END }

char getCommandWord(char command[], int length);
void tl5Conv(char *sourceFile, char *targetFile, char *extend);
void csvConv(char *sourceFile, char *targetFile, char *extend);
void converting();