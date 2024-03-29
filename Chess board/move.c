#include "chess.h"
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static int isLegalMove(int srcI, int srcJ, int trgI, int trgJ) {
    int i;
    int piece = board[srcI][srcJ];//moved piece...
    int pieceType = abs(piece);
    int pieceColor = piece > 0 ? WHITE : BLACK;
    switch (pieceType) {
    case ROOK:
        if (srcI != trgI && srcJ != trgJ)
            return 0;
        if (srcI == trgI) {//move along a rank
            for (i = 1; i < abs(srcJ - trgJ); i++)//check middle squares
                if (srcJ<trgJ && board[srcI][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI][srcJ - i] != EMPTY)
                    return 0;
        }
        else//move along a file
            for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                if (srcI<trgI && board[srcI + i][srcJ] != EMPTY
                    || srcI > trgI && board[srcI - i][srcJ] != EMPTY)
                    return 0;
        break;
    case PAWN:
        if (srcJ != trgJ)
            return 0;
        if (pieceColor == BLACK) {
            if (srcI == 1)//starting position
                return trgI == 2 || trgI == 3;
            else
                return trgI == srcI + 1;
        }
        else {
            if (srcI == 6)//starting position
                return trgI == 5 || trgI == 4;
            else
                return trgI == srcI - 1;
        }
        break;
    case KNIGHT://L shape
        return abs((srcI - trgI) * (srcJ - trgJ)) == 2;
    case BISHOP:
        if (abs(srcI - trgI) != abs(srcJ - trgJ))
            return 0;//not a diagonal move... return false...
        if (srcI < trgI) {//moving down the board
            for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                if (srcJ < trgJ && board[srcI + i][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI + i][srcJ - i] != EMPTY)
                    return 0;
        }
        else//moving up the board
            for (i = 1; i < abs(srcI - trgI);i++)//check middle squares
                if (srcJ < trgJ && board[srcI - i][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI - i][srcJ - i] != EMPTY)
                    return 0;
        break;
    case QUEEN:
        if (srcI == trgI || srcJ == trgJ) {//move like a rook
            if (srcI == trgI) {//move along a rank
                for (i = 1; i < abs(srcJ - trgJ); i++)//check middle squares
                    if (srcJ<trgJ && board[srcI][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI][srcJ - i] != EMPTY)
                        return 0;
            }
            else//move along a file
                for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                    if (srcI<trgI && board[srcI + i][srcJ] != EMPTY
                        || srcI > trgI && board[srcI - i][srcJ] != EMPTY)
                        return 0;
        }
        else if (abs(srcI - trgI) == abs(srcJ - trgJ)) {//move like a bishop
            if (srcI < trgI) {//moving down the board
                for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                    if (srcJ < trgJ && board[srcI + i][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI + i][srcJ - i] != EMPTY)
                        return 0;
            }
            else//moving up the board
                for (i = 1; i < abs(srcI - trgI);i++)//check middle squares
                    if (srcJ < trgJ && board[srcI - i][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI - i][srcJ - i] != EMPTY)
                        return 0;
        }
        else
            return 0;
        break;
    case KING:
        return abs(srcI - trgI) + abs(srcJ - trgJ) == 1 
            || abs(srcI - trgI) * abs(srcJ - trgJ) == 1;
    }
    return 1;//legal move
}
handleMove() {
    char source[MAX_COMMAND_TOKEN_LENGTH];//placeholder for argument 1 (initial square)
    char target[MAX_COMMAND_TOKEN_LENGTH];//placeholder for argument 2 (final square)
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    //source SQUARE: board[sourceI][sourceJ]
    //target SQUARE: board[targetI][targetJ]
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for mv command! It must be in the form of mv ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the rest of illegal command..
        return;
    }
}

void move(char* source, char* target){
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;

    sourceFile = source[0];//source = "a5", sourceFile = 'a'
    targetFile = target[0];
    sourceRank = source[1] - '0';//source = "a5", sourceRank = 5
    targetRank = target[1] - '0';
    //board[sourceI][sourceJ]: source square...
    //board[targetI][targetJ]: target square...
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("Invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if ((int)(board[sourceI][sourceJ] * turn) < 0) {
        printf("Turn violation, it's %s to move\n", turn == WHITE ? "white" : "black");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] != EMPTY) {
        printf("Invalid move: either source square is empty or target square is not empty\n");
        return;
    }
    if (!isLegalMove(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess move\n");
        return;
    }
    //end of error checking....

    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = EMPTY;
    turn *= -1;//WHITE --> BLACK and BLACK --> WHITE
}

handleMoveTimer() {

    char source[MAX_COMMAND_TOKEN_LENGTH];//placeholder for argument 1 (initial square)
    char target[MAX_COMMAND_TOKEN_LENGTH];//placeholder for argument 2 (final square)
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;

    //source SQUARE: board[sourceI][sourceJ]
    //target SQUARE: board[targetI][targetJ]
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);

    if (lastCharacter != '\n') {
        printf("Too many arguments for mv command! It must be in the form of mv ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the rest of illegal command..
        return;
    }
    sourceFile = source[0];//source = "a5", sourceFile = 'a'
    targetFile = target[0];
    sourceRank = source[1] - '0';//source = "a5", sourceRank = 5
    targetRank = target[1] - '0';
    
    //board[sourceI][sourceJ]: source square...
    //board[targetI][targetJ]: target square...
    
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("Invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if ((int)(board[sourceI][sourceJ] * turn) < 0) {
        printf("Turn violation, it's %s to move\n", turn == WHITE ? "white" : "black");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] != EMPTY) {
        printf("Invalid move: either source square is empty or target square is not empty\n");
        return;
    }
    if (!isLegalMove(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess move\n");
        return;
    }
    //end of error checking....

    board[targetI][targetJ] = board[sourceI][sourceJ];

    board[sourceI][sourceJ] = EMPTY;

    if(initTime == 1){
        time_t blackStart;
        blackStart = time(NULL);
        blackStartCounter = blackStart;
        blackLimit = 100;
        printf("Starting time for Black: %d minutes\n", blackLimit);
        initTime = -1;
        turn *= -1;
        return;
    }

    if(initTime == 1){
        time_t whiteStart;
        whiteStart = time(NULL);
        whiteStartCounter = whiteStart;
        whiteLimit = 100;
        printf("Starting time for White: %d minutes\n", whiteLimit);
        initTime = -1;
        turn *= -1;
        return;
    }

    if(turn == -1){
        time_t whiteEndTime;
        whiteEndTime = time(NULL);
        whiteLimit = whiteLimit - ((whiteEndTime - whiteStartCounter) / 60);
        if(whiteLimit <= 0){
            printf("Looks like your time is up! Quit the game and try again!");
            return;
        }
        printf("White time left: %d minutes\n", whiteLimit);
        whiteStart = time(NULL);
        whiteStartCounter = whiteStart;
    }

    if(turn == 1){
        time_t blackEndTime;
        blackEndTime = time(NULL);
        blackLimit = blackLimit - ((blackEndTime - blackStartCounter) / 60);
        if(blackLimit <= 0){
            printf("Looks like your time is up! Quit the game and try again!");
            return;
        }
        printf("Black time left: %d minutes\n", blackLimit);
        blackStart = time(NULL);
        blackStartCounter = blackStart;
    }
    turn *= -1;
}



    

    
