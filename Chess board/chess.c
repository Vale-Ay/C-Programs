#include "chess.h"
#include <string.h>
#include <stdbool.h>
#include <time.h>

square board[8][8];
int turn;
static void resetBoard() {
    turn = WHITE;//WHITE moves first
    int i, j;
    for (i = 2; i < 6;i++)
        for (j = 0;j < 8;j++)
            board[i][j] = EMPTY;
    for (j = 0;j < 8;j++) {
        board[1][j] = BLACK * PAWN;
        board[6][j] = WHITE * PAWN;
    }
    board[0][0] = board[0][7] = BLACK * ROOK;
    board[7][0] = board[7][7] = WHITE * ROOK;
    board[0][1] = board[0][6] = BLACK * KNIGHT;
    board[7][1] = board[7][6] = WHITE * KNIGHT;
    board[0][2] = board[0][5] = BLACK * BISHOP;
    board[7][2] = board[7][5] = WHITE * BISHOP;
    board[0][3] = BLACK * QUEEN;
    board[7][3] = WHITE * QUEEN;
    board[0][4] = BLACK * KING;
    board[7][4] = WHITE * KING;
}
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;//either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
    if (lastCharacter == '\n') {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}
main(int argc, char** argv) {
    /*
    * You can access all the command-line arguments here
    * argv[1], argv[2], ...
    * Example of import option: -i d2d4,d7d5,e2e4,d5xe4,Ng1h3,Ke8d7,Qd1d3
    * which is equivalent to a new game started this way:
    * mv d2 d4
    * mv d7 d5
    * mv e2 e4
    * cp d5 e4
    * mv g1 h3
    * mv e8 d7
    * mv d1 d3
    */

   time_t whiteStart;
   time_t blackStart;
   whiteLimit = 100;
   blackLimit = 100;
   whiteStart = time(NULL);
   blackStart = time(NULL);
   initTime = 1;
   blackStartCounter = blackStart;
   whiteStartCounter = whiteStart;


   int black = 0;
   int blackVal = 0;
   int white = 0;
   int whiteVal = 0;

   int rotatedVal = 0;
   int import = 0;
   int importedArg = 0;
   int timer = 0;

   if(argc > 1)
   {
        for (int k = 0; k < argc; k++)
        {
            if (strcmp (argv[k],"-w") == 0)
            { 
                printf("Player White: %s\n" ,argv[k+1]);
                white = 1;
                whiteVal = k+1;
                break;
            }
        }
        for (int p = 0; p < argc; p++)
        {
             if (strcmp (argv[p],"-b") == 0)
             {
                printf("Player Black: %s\n" ,argv[p+1]);
                black = 1;
                blackVal = p+1;
                break;
            }
        }
        for (int i = 0; i < argc; i++)
        {
            if (strcmp (argv[i],"-r") == 0)
            {
                printf("The chess board has been rotated\n");
                rotatedVal = 1;
                break;
            }
        }
        for (int j = 0; j < argc; j++)
        {
            if (strcmp (argv[j],"-i") == 0)
            {
                printf("The Chess game has been imported\n");
                import = 1;
                importedArg = j+1;
                break;
            }
        }
        for (int n = 0; n < argc; n++)
        {
            if (strcmp (argv[n],"-t") == 0)
            {
                printf("The timer has been implemented\n");
                timer = 1;
                break;
            }
        }
    }
        resetBoard();
    
    if (import == 1)
    {
        char source[3], target[3];
        char * chessGame = argv[importedArg];
        char* tok; 
        int time1 = 1;

        while(1)
        {
            if (time1)
            {
                time1 = 0;
                tok = strtok(chessGame, ",");
            }
            else
            {
                tok = strtok(NULL, ",");
            }
            if (!tok)
            {
                break;
            }
            if (isupper(*tok))
            {
                tok++;
            }
            if (tok[2] == 'x')
            {
                strncpy(source, tok, 2); 
                strncpy(target, tok + 3, 2);
            }
            else 
            {
                strncpy(source, tok, 2); 
                strncpy(target, tok + 2, 2);
            }
        }
    }

    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    resetBoard();
    printf("Start the game using a mv command! Valid commands are quit, show, mv and cp.\n");
    while (1) {//infinite while loop...
        printf(">>");
        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        if (strcmp(command, "quit") == 0)//if command === "quit"
            break;
        else if (!strcmp(command, "mv"))//if command == "mv"
        {
            if (lastCharacter == '\n')//mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else{
                if(time == 0){
                    handleMove();
                }else{
                    handleMoveTimer();
                }
                
            }
                
        }
        else if (!strcmp(command, "cp"))//if command == "cp"
        {
            if (lastCharacter == '\n')//cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else{
                if(timer == 0){
                    handleCapture();
                }else{
                    CaptureTimer();
                }
            }
                
        }
        else if (!strcmp(command, "show"))//if command == "show"
        {
            if (lastCharacter != '\n') {//show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the ramainder of the invalid show command...	
            }
            else
            {
                if(rotatedVal == 0)
                {
                    if(white == 1)
                    {
                        printf("White Player: %s\n", argv[whiteVal]);
                    }
                    handleShow();
                    
                    if(black == 1){
                        printf("Black Player: %s\n", argv[blackVal]);
                     }
                }else if(rotatedVal == 1)
                {
                    if(white == 1)
                    {
                        printf("White Player: %s\n", argv[whiteVal]);
                    }
                    SecondhandleShow();
                    
                    if(black == 1)
                    {
                        printf("Black Player: %s\n", argv[blackVal]);
                    }
                }
            }
        }
        
        else 
        {
            printf("invalid command! Your command must start either with quit, show, mv or cp.\n");
            while (lastCharacter != '\n')//skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}