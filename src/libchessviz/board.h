#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdlib.h>

#define BoardSideSize 8

typedef struct ChessBoard {
    char board[BoardSideSize][BoardSideSize + 1];
} ChessBoard;


ChessBoard *new_board();

#endif