#include "PA4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void handleAdd() 
{
  char token[MAX_TOKEN_LENGTH];
  Vertex *vertices = (Vertex*)malloc(sizeof(Vertex)*100); 
  Polygon *poly_P = (Polygon*)malloc(sizeof(Polygon)); 
  int x,y,i;
  int j = 0;

  if (getCommandWord(token, MAX_TOKEN_LENGTH) != '\n') 
  {
    printf("\nToo many arguments to add\n");
    while (getCommandWord(token, MAX_TOKEN_LENGTH) != '\n');
    {
      return;
    }
  }
  int size_of_token = 0;
  for (int i = 0; i < MAX_TOKEN_LENGTH && token[i] != '\0'; i++) 
  {
    if(!(token[i] == ' ' && token[i+1] == ' '))
    {
      ++size_of_token;
    }
  }

  if ((size_of_token % 2) != 0) 
  {
    printf("'\nError: there must be an even input to add arguments.\n");
    return;
  }
  for(int i = 0, j = 0; i < size_of_token; i += 2, j++) 
  {
    x = token[i];
    y = token[i + 1];
    Vertex v = createVertices(x, y);
    vertices[j] = v;
  }
  poly_P -> numberOfVertices = size_of_token/2;
  poly_P -> vertexList = vertices;


  printf("\nPolygon added");
  printf("\n\tVertices count: %d\n", poly_P -> numberOfVertices);
  for (int i = 0; i < poly_P -> numberOfVertices; i++) 
  {
    printf("\tVertices #%d: (%d, %d)\n", i + 1, (poly_P -> vertexList[i].x - '0'), (poly_P -> vertexList[i].y - '0'));
  }

  for (int i = 0; i < MAX_NUM_POLYGONS; i++) 
  {
    if (polygons[i].numberOfVertices == 0) 
    {
      polygons[i] = *poly_P;
      break;
    }
  }
}

void handleSummary() 
{
  int i = 0;
  int j = 0;

  if (polygons[0].numberOfVertices == 0) 
  {
    printf("\n**The list of polygons is empty**\n");
    return;
  }
  
  for (i = 0; i < MAX_NUM_POLYGONS && polygons[i].numberOfVertices != 0; i++) 
  {
    int av_x = 0;
    int av_y = 0;
    int numberOfVertex = polygons[i].numberOfVertices;

    printf("\nPolygon #%d has %d vertices. ", i + 1, numberOfVertex);
    for (j = 0; j < polygons[i].numberOfVertices; j++) 
    {
      int x = polygons[i].vertexList[j].x - '0';
      av_x += x;

      int y = polygons[i].vertexList[j].y - '0';
      av_y += y;
    }
    printf("Its centroid is at (%.1f, %.1f).\n\n",(double)av_x/numberOfVertex,(double)av_y/numberOfVertex);
  }
}

void handleTurn() 
{
  char token1[MAX_TOKEN_LENGTH];
  char token2[MAX_TOKEN_LENGTH];
  int index;  
  char direction[512]; 

  if (getCommandWord(token1, MAX_TOKEN_LENGTH) == '\n') 
  {
    printf("\nToo few arguments to turn\n");
    return;
  }
  if (getCommandWord(token2, MAX_TOKEN_LENGTH) != '\n') 
  {
    printf("\nToo many arguments to turn\n");
    while (getCommandWord(token2, MAX_TOKEN_LENGTH) != '\n');
    return;
  }

  index = atoi(token1) - 1;

  if (index < 0) 
  {
    printf("\nPolygon does not exist. Recommend starting from 1\n");
    return;
  }

  for (int i = 0; i < (sizeof(token2) / sizeof(token2[0])); i++) 
  {
    direction[i] = token2[i];
  }

  if (polygons[index].numberOfVertices == 0) 
  {
    printf("\nPolygon not found\n");
    return;
  }

  if (!strcmp(direction,"up")) 
  {
    printf("\nPolygon direction %d changed to up\n", index + 1);
    polygons[index].shiftDirection = UP;
  }
  else if (!strcmp(direction,"down")) 
  {
    printf("\nPolygon direction %d changed to down\n", index + 1);
    polygons[index].shiftDirection = DOWN;
  }
  else if (!strcmp(direction,"right")) 
  {
    printf("\nPolygon direction %d changed to right\n", index + 1);
    polygons[index].shiftDirection = RIGHT;
  }
  else if (!strcmp(direction,"left")) 
  {
    printf("\nPolygon direction %d changed to left\n", index + 1);
    polygons[index].shiftDirection = LEFT;
  }
  else if ((!strcmp(direction,"right-up") || !strcmp(direction, "up-right"))) 
  {
    printf("\nPolygon direction %d changed to up-right/right-up\n", index + 1);
    polygons[index].shiftDirection = UP | RIGHT;
  }
  else if ((!strcmp(direction,"right-down") || !strcmp(direction, "down-right"))) 
  {
    printf("\nPolygon direction %d changed to right-down/down-right\n", index + 1);
    polygons[index].shiftDirection = RIGHT | DOWN;
  }
    else if ((!strcmp(direction, "left-up") || !strcmp(direction, "up-left"))) 
  {
    printf("\nPolygon direction %d changed to left-up/up-left\n", index + 1);
    polygons[index].shiftDirection = LEFT | UP;
  }
  else if ((!strcmp(direction,"left-down") || !strcmp(direction, "down-left"))) 
  {
    printf("\nPolygon direction %d changed to left-down/down-left\n", index + 1);
    polygons[index].shiftDirection = LEFT | DOWN;
  }
  else 
  {
    printf("\nInvalid move input\n");
    printf("The direction of the polygon remains unchanged\n");
  }
}
