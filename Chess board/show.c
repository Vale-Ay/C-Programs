#include"chess.h"
handleShow() {
    int i, j;
    printf("board\t");
    for (i = 0; i < 8; i++)//file labels...
        printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');
    for (i = 0; i < 8; i++)//table itself
        for (j = 0; j < 9; j++)
            printf("%d%c", j == 0 ? 8 - i : board[i][j - 1], j == 8 ? '\n' : '\t');
}

// This rotates the board using the inverse of initial handleShow() above.
SecondhandleShow()
{ 
    int i, j;
    printf("board\t");
    for(i = 0; i < 8; i++){
        printf("%c%c", 'h' - i, i == 7 ? '\n' : '\t');
    }
    for (i = 7; i >= 0; i--){
        for (j = 9; j > 0; j--)
            printf("%d%c", j == 9 ? 8 - i : board[i][j - 1], j == 1 ? '\n' : '\t');
    }
}