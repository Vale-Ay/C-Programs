#include "PA4.h"
#include <stdlib.h>

Vertex createVertices(int x, int y) 
{
  Vertex vert;
  vert.x = x;
  vert.y = y;
  return vert;
}

char getCommandWord(char command[], int maxLen) 
{
    char lastChar;
    int i;
    for (i = 0; i < maxLen - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastChar = command[i];
    command[i] = '\0';

    return lastChar;
}


int main(int argc, char** argv) 
{
  char command[MAX_TOKEN_LENGTH];
  char lastChar;
  printf("\nadd\t\t\t input the vertices you wish to add without spaces\n\t\t\t Ex: 'add 2345' will add (2,3) (4,5)\n\n");
  printf("turn\t\t\t specify the polygon you wish to turn and indicate the direction:\n");
  printf("\t\t\t up, down, left, right, up-right/right-up,\n\t\t\t up-left/left-up, down-right/right-down, down-left/left-down\n\n");
  printf("summary\t\t\t creates the list of polygons created\n\n");
  printf("quit\t\t\t ends the program\n\n\n"); 

  while (1) 
      {
      printf("\nEnter command: ");
      lastChar = getCommandWord(command, MAX_TOKEN_LENGTH);

      if (!strcmp(command, "quit")) 
      {
          printf("\nEnding program...\n\n");
          break;
      }
      else if (!strcmp(command, "add")) 
      {
          if (lastChar == '\n') 
          {
              printf("\nERROR; try inputting again\n");
          }
          else 
          {
            handleAdd();
              
          }
      }
      else if (!strcmp(command, "summary")) 
      {
          if (lastChar != '\n') 
          {
              printf("\nERROR; try inputing again\n");
          }
          else 
          {
              handleSummary();
          }
      }
      else if (!strcmp(command, "turn")) 
      {
          if (lastChar == '\n') 
          {
              printf("\nERROR; try inputing again\n");
          }
          else 
          {
              handleTurn();
          }
      }
      else 
      {
          printf("\nInvalid Command!\n");
          while (lastChar != '\n')
          {
              lastChar = getCommandWord(command, MAX_TOKEN_LENGTH);
          }
      }
  }
}