#include "libchessviz/board.h"

ChessBoard *new_board()
{
    ChessBoard *cboard = malloc(sizeof(ChessBoard));

    cboard->board[0][0] = "rnbqkbnr";
    cboard->board[1][0] = "pppppppp";
    cboard->board[2][0] = "        ";
    cboard->board[3][0] = "        ";
    cboard->board[4][0] = "        ";
    cboard->board[5][0] = "        ";
    cboard->board[6][0] = "pppppppp";
    cboard->board[7][0] = "rnbqkbnr";

    return cboard;
}