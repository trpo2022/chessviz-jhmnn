#include "libchessviz/board.h"
#include "libchessviz/board_read.h"
#include "libchessviz/board_move.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    ChessBoard* board = new_board();
    if (!board) return 0;

    putchar('\n');
    print_board(board, 0);
    printf("Введите ходы в следующем формате:\n");
    printf("1. e2-e4 e7-e5\n2. Bf1-c4 Nb8-c6\n3. Qd1-h5 Ng8-f6\n4. Qh5xf7#\n\n");

    MoveRec* moves = read_move_term();

    putchar('\n');

    if (!moves || !check_all_moves(*board, moves)) printf("Введены некорректные данные.\n");
    else print_game(board, moves);

    free(board);
    free(moves);

    return 0;
}
