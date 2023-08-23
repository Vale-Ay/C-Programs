#include"calendar.h"
/* This program gets two commands:
	1. print MM/YYYY: prints the days of a month in a table
	2. count MM/DD/YYYY mm/dd/yyyy: counts the number of days between two given dates.
*/
int main(void) {
	char command[MAX_COMMAND_TOKEN_LENGTH];//placeholder for a command...
	char lastCharacter;
	while (1) {//main infinite while loop...
		printf("Please enter a new command...\n");
		lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
		if (command[0] == 'q'&& command[1] == 'u'&& command[2] == 'i'&& command[3] == 't'&& command[4] == '\0')//(!strcmp(command, "quit"))
			break;
		else if (!strcmp(command, "print"))
		{
			if (lastCharacter == '\n')
				printf("Too few arguments for print command! It must be in the form of print MM/YYYY.\n");
			else
				handlePrint();
		}
		else if (!strcmp(command, "count"))
		{
			if (lastCharacter == '\n')
				printf("Too few arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n");
			else
				handleCount();
		}
		else {
			printf("invalid command! Your command must start either with quit, or print, or count.\n");
			while (lastCharacter != '\n')
				lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
		}
	}
	return 0;
}
char getCommandWord(char command[], int maxLength) {
	char lastCharacter;
	int i;
	for (i = 0; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
	lastCharacter = command[i];
	command[i] = '\0';//end of string sign
	return lastCharacter;
}