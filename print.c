#include"calendar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int printDays(int day, int month, int year);

void print(int MM, int YYYY)
{
	int current = printDays(1, MM, YYYY); 
	int daysInMonth = monthDays(MM, YYYY);
  int i;

	printf(" Sun   Mon  Tue  Wed  Thu  Fri  Sat\n");
  for (i = 0; i < current; i++)
    {
      printf("     ");
    }

  for (int x = 1; x <= daysInMonth; x++)
  {
    if (isLeapYear(YYYY) && MM == 2 )
    {
      daysInMonth = 29; 
    }
    printf("%5d", x);

      if (++i > 6)
      {
          i = 0;
          printf("\n");
      }
  }
  printf("\n");
    }


void handlePrint(void) 
{
	char token[MAX_COMMAND_TOKEN_LENGTH];
	if (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n')
	{
    printf("Invalid: Please enter in form MM/YYYY\n");
	  while (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n');
	  return;
	}
	
  char month[10];
	int year;
	int x = 0;

	for (int i = 0; token[i] != '/'; i++)
	{
		month[i] = token[i];
		x = i;
	}
  month[x + 1] = 0; 
	char n[5];
	int y = 0;
	
  for (int i = x + 2; token[i] != '\0'; i++)
	{
		n[y++] = token[i];
	}
	
  n[x + 1] = '\0';
	year = atoi(n);
	int newNum = atoi(month);
 
 	printf("\nCalendar for:  %s\n\n", token);

  print(newNum, year); 
}

int printDays(int day, int month, int year)
{
  int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  year -= month < 3;
  return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

