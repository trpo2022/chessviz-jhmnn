#ifndef __BOARD_H__
#define __BOARD_H__

#define CELLS_IN_ROW 8
#define MAX_MOVES 218
#define MOVES_IN_ONE 2
#define MAX_MOVE_LENGTH 15

#define WHITE_MOVE 0
#define BLACK_MOVE 1

#define FALSE 0
#define TRUE 1

typedef struct ChessBoard {
    char cells[CELLS_IN_ROW][CELLS_IN_ROW + 1];
} ChessBoard;

typedef struct MoveRec {
    char moves[MAX_MOVES][MOVES_IN_ONE][MAX_MOVE_LENGTH];
    int numberOfMoves;
} MoveRec;

ChessBoard *new_board();
MoveRec *read_move_term();
void print_board(ChessBoard *cboard);

#endif
