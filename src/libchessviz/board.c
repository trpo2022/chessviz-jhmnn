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
    cboard->cells = malloc(CELLS_IN_ROW * (CELLS_IN_ROW + 1) * sizeof(char));
    if (cboard->cells == NULL) return NULL;

    cboard->cells[0] = "RNBQKBNR";
    cboard->cells[1] = "PPPPPPPP";
    cboard->cells[2] = "        ";
    cboard->cells[3] = "        ";
    cboard->cells[4] = "        ";
    cboard->cells[5] = "        ";
    cboard->cells[6] = "pppppppp";
    cboard->cells[7] = "rnbqkbnr";

    return cboard;
}

MoveRec *read_move_term()
{
    MoveRec *moveRec = calloc(1, sizeof(MoveRec));
    if (moveRec == NULL) return NULL;
    char *moveNum = malloc(5 * sizeof(char));
    if (moveNum == NULL) return NULL;
    char *whiteMove = malloc(11 * sizeof(char));
    if (whiteMove == NULL) return NULL;
    char *blackMove = malloc(11 * sizeof(char));
    if (blackMove == NULL) return NULL;

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