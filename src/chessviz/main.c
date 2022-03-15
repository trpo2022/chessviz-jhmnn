#include "libchessviz/board.h"

#include <stdio.h>
#include <string.h>

int main()
{
    ChessBoard *cboard = new_board();
    if (cboard == NULL) return 0;
    MoveRec *moveRec = read_move_term();
    if (moveRec == NULL) return 0;

    printf("\n");

    for (int i = 0; i < CELLS_IN_ROW; i++) {
        printf("%s\n", cboard->cells[i]);
    }

    printf("\n");

    for (int i = 0; i < moveRec->numberOfMoves; i++) {
        printf("%d. %s %s\n", i + 1, moveRec->moves[i][WHITE_MOVE], moveRec->moves[i][BLACK_MOVE]);
    }

    return 0;
}