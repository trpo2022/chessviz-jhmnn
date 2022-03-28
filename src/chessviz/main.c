#include "libchessviz/board.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    ChessBoard *cboard = new_board();
    if (cboard == NULL) return 0;

    printf("\n");
    print_board(cboard);
    printf("\n\n");
    printf("Введите ходы в следующем формате:\n");
    printf("1. e2-e4 e7-e5\n2. Qh5xf7#\n\n");

    MoveRec *moveRec = read_move_term();
    if (moveRec == NULL) {
        printf("Введены некорректные данные.\n");
        return 0;
    }

    printf("\n");
    for (int i = 0; i < moveRec->numberOfMoves; i++) {
        printf("%d. %s %s\n", i + 1, moveRec->moves[i][WHITE_MOVE], moveRec->moves[i][BLACK_MOVE]);
    }

    free(cboard);
    free(moveRec);

    return 0;
}