#include "libchessviz/board.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static int ismoveletter(char symbol)
{
    int lettersNum = 8;
    char letters[] = "abcdefgh";

    for (int k = 0; k < lettersNum; k++) {
        if (symbol == letters[k]) {
            return TRUE;
        }
    }

    return FALSE;
}

static int ismovedigit(char symbol)
{
    int numbersNum = 8;
    char numbers[] = "12345678";

    for (int k = 0; k < numbersNum; k++) {
        if (symbol == numbers[k]) {
            return TRUE;
        }
    }

    return FALSE;
}

static int ispiecesletter(char symbol) 
{
    int piecesNum = 5;
    char pieces[] = "RNBQK";

    for (int i = 0; i < piecesNum; i++) {
        if (symbol == pieces[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

static int check_end_of_input(char *string) 
{
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '#') {
            return TRUE;
        }
    }

    return FALSE;
}

static int check_input_correctness(char *moves) 
{
    int currentSymbolNum = 0;

    if (ispiecesletter(moves[currentSymbolNum])) currentSymbolNum++;
    if (!ismoveletter(moves[currentSymbolNum])) return FALSE;
    currentSymbolNum++;
    if (!ismovedigit(moves[currentSymbolNum])) return FALSE;
    currentSymbolNum++;
    if (moves[currentSymbolNum] != '-' && moves[currentSymbolNum] != 'x') return FALSE;
    currentSymbolNum++;
    if (!ismoveletter(moves[currentSymbolNum])) return FALSE;
    currentSymbolNum++;
    if (!ismovedigit(moves[currentSymbolNum])) return FALSE;
    currentSymbolNum++;
    if (strlen(moves) > currentSymbolNum && moves[currentSymbolNum] != '#' && moves[currentSymbolNum] != '+') return FALSE;
    currentSymbolNum++;
    if (strlen(moves) > currentSymbolNum) return FALSE;

    return TRUE;
}

ChessBoard *new_board()
{
    ChessBoard *cboard = malloc(sizeof(ChessBoard));
    if (cboard == NULL) return NULL;

    strcpy(cboard->cells[0], "RNBQKBNR");
    strcpy(cboard->cells[1], "PPPPPPPP");
    strcpy(cboard->cells[2], "        ");
    strcpy(cboard->cells[3], "        ");
    strcpy(cboard->cells[4], "        ");
    strcpy(cboard->cells[5], "        ");
    strcpy(cboard->cells[6], "pppppppp");
    strcpy(cboard->cells[7], "rnbqkbnr");

    return cboard;
}

MoveRec *read_move_term()
{
    MoveRec *moveRec = malloc(sizeof(MoveRec));
    if (moveRec == NULL) return NULL;
    char *moveNum = malloc(5 * sizeof(char));
    if (moveNum == NULL) return NULL;
    char *whiteMove = malloc(MAX_MOVE_LENGTH * sizeof(char));
    if (whiteMove == NULL) return NULL;
    char *blackMove = malloc(MAX_MOVE_LENGTH * sizeof(char));
    if (blackMove == NULL) return NULL;

    moveRec->numberOfMoves = 0;

    while (1) {
        moveRec->numberOfMoves++;

        scanf("%s %s", moveNum, whiteMove);
        if (strtoul(moveNum, NULL, 10) != moveRec->numberOfMoves) return NULL;
        if (!check_input_correctness(whiteMove)) return NULL;

        strcpy(moveRec->moves[moveRec->numberOfMoves - 1][WHITE_MOVE], whiteMove);

        if (check_end_of_input(whiteMove)) {
            return moveRec;
        }

        scanf("%s", blackMove);
        if (strtoul(moveNum, NULL, 10) != moveRec->numberOfMoves) return NULL;
        if (!check_input_correctness(blackMove)) return NULL;

        strcpy(moveRec->moves[strtoul(moveNum, NULL, 10) - 1][BLACK_MOVE], blackMove);

        if (check_end_of_input(blackMove)) {
            return moveRec;
        }
    }
}

char *char_to_pieces(char character)
{
    switch (character)
    {
    case 'R':
        return "\e[1;37m♜";
    case 'N':
        return "\e[1;37m♞";
    case 'B':
        return "\e[1;37m♝";
    case 'Q':
        return "\e[1;37m♛";
    case 'K':
        return "\e[1;37m♚";
    case 'P':
        return "\e[1;37m♟";
    case 'r':
        return "\e[1;90m♜";
    case 'n':
        return "\e[1;90m♞";
    case 'b':
        return "\e[1;90m♝";
    case 'q':
        return "\e[1;90m♛";
    case 'k':
        return "\e[1;90m♚";
    case 'p':
        return "\e[1;90m♟";
    }

    return " ";
}

void print_board(ChessBoard *cboard)
{
    for (int i = CELLS_IN_ROW - 1; i >= 0; i--) {
        printf("\e[1;37m%d\e[0m ", (i % CELLS_IN_ROW - 1) + 2);

        for (int j = 0; j < CELLS_IN_ROW; j++) {
            if (((i % CELLS_IN_ROW - 1) + j) % 2 == 0) {
                printf("\e[42m%s \e[0m", char_to_pieces(cboard->cells[i][j]));
            } else {
                printf("\e[40m%s \e[0m", char_to_pieces(cboard->cells[i][j]));
            }
        }

        printf("\n");
    }

    printf("  \e[1;37ma b c d e f g h\e[0m");
}
