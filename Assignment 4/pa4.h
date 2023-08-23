#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUM_POLYGONS 1000
#define MAX_TOKEN_LENGTH 1000

typedef enum 
{
  NONE = 0,
  UP = 1,
  DOWN = 2,
  LEFT = 4,
  RIGHT = 8
}Direction;

typedef struct 
{
  int x, y;
}Vertex;

typedef struct 
{
  int numberOfVertices;
  Direction shiftDirection;
  Vertex* vertexList;
}Polygon;
static Polygon polygons[MAX_NUM_POLYGONS]; 
char getCommandWord(char command[], int maxLength);
Vertex createVertices(int x, int y);;
void handleAdd();
void handleSummary();
void handleTurn();