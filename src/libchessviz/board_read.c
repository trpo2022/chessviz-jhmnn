#include "libchessviz/board_read.h"
#include "libchessviz/board.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ismoveletter(char symbol)
{
    int lettersNum = 8;
    char letters[] = "abcdefgh";

    for (int k = 0; k < lettersNum; k++) {
        if (symbol == letters[k]) {
            return 1;
        }
    }

    return 0;
}

static int ismovedigit(char symbol)
{
    int numbersNum = 8;
    char numbers[] = "12345678";

    for (int k = 0; k < numbersNum; k++) {
        if (symbol == numbers[k]) {
            return 1;
        }
    }

    return 0;
}

static int ispiecesletter(char symbol)
{
    int piecesNum = 5;
    char pieces[] = "RNBQK";

    for (int i = 0; i < piecesNum; i++) {
        if (symbol == pieces[i]) {
            return 1;
        }
    }

    return 0;
}

static int check_end_of_input(char* string)
{
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '#') {
            return 1;
        }
    }

    return 0;
}

static int check_input_correctness(char* moves)
{
    int currentSymbolNum = 0;

    if (ispiecesletter(moves[currentSymbolNum]))
        currentSymbolNum++;
    if (!ismoveletter(moves[currentSymbolNum]))
        return 0;
    currentSymbolNum++;
    if (!ismovedigit(moves[currentSymbolNum]))
        return 0;
    currentSymbolNum++;
    if (moves[currentSymbolNum] != '-' && moves[currentSymbolNum] != 'x')
        return 0;
    currentSymbolNum++;
    if (!ismoveletter(moves[currentSymbolNum]))
        return 0;
    currentSymbolNum++;
    if (!ismovedigit(moves[currentSymbolNum]))
        return 0;
    currentSymbolNum++;
    if (strlen(moves) > currentSymbolNum && moves[currentSymbolNum] != '#'
        && moves[currentSymbolNum] != '+')
        return 0;
    currentSymbolNum++;
    if (strlen(moves) > currentSymbolNum)
        return 0;

    return 1;
}

MoveRec* read_move_term()
{
    MoveRec* moveRec = malloc(sizeof(MoveRec));
    if (moveRec == NULL)
        return NULL;

    char* moveNum = malloc(5 * sizeof(char));
    if (moveNum == NULL)
        return NULL;

    char* whiteMove = malloc(MAX_MOVE_LENGTH * sizeof(char));
    if (whiteMove == NULL)
        return NULL;

    char* blackMove = malloc(MAX_MOVE_LENGTH * sizeof(char));
    if (blackMove == NULL)
        return NULL;

    moveRec->numberOfMoves = 0;

    while (1) {
        moveRec->numberOfMoves++;

        scanf("%s %s", moveNum, whiteMove);
        if (strtoul(moveNum, NULL, 10) != moveRec->numberOfMoves)
            return NULL;
        if (!check_input_correctness(whiteMove))
            return NULL;

        strcpy(moveRec->moves[moveRec->numberOfMoves - 1][WHITE_MOVE],
               whiteMove);

        if (check_end_of_input(whiteMove)) {
            return moveRec;
        }

        scanf("%s", blackMove);
        if (strtoul(moveNum, NULL, 10) != moveRec->numberOfMoves)
            return NULL;
        if (!check_input_correctness(blackMove))
            return NULL;

        strcpy(moveRec->moves[strtoul(moveNum, NULL, 10) - 1][BLACK_MOVE],
               blackMove);

        if (check_end_of_input(blackMove)) {
            return moveRec;
        }
    }
}
