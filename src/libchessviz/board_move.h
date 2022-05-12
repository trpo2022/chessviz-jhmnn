#include "libchessviz/board.h"


#ifndef BOARD_MOVE_H
#define BOARD_MOVE_H

#define PAWN_MAX_MOVE_LEN_DIGIT 2
#define PAWN_MAX_MOVE_LEN_CHAR 1

int check_move_pawn_white(ChessBoard *board, char *move);
int check_move_pawn_black(ChessBoard *board, char *move);
int check_move_rook(ChessBoard *board, char *move);
int check_move_knight(ChessBoard *board, char *move);
int check_move_bishop(ChessBoard *board, char *move);
int check_move(ChessBoard *board, char *move);
int check_all_moves(ChessBoard board, MoveRec *moves);
void move(ChessBoard *board, char *move);

#endif
