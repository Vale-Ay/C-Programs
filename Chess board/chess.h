#include<stdio.h>
#include<math.h>
#define MAX_COMMAND_TOKEN_LENGTH 6
#define WHITE 1
#define BLACK -1
typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
}square;

typedef enum {
    NONE = 0,
    WHITE_SHORT = 1,
    WHITE_LONG = 2,
    BLACK_SHORT = 4,
    BLACK_LONG = 8
}castle;
extern square board[8][8];
extern int turn;
char getCommandWord(char command[], int maxLength);
int initTime;
int whiteStart;
int whiteStartCounter;
int whiteLimit;
int whiteEnd;
int blackStart;
int blackStartCounter;
int blackLimit;
int blackEnd;
handleShow();
SecondhandleShow();
handleCapture();
CaptureTimer();
handleMove();
handleMoveTimer();
