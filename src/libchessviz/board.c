#include "libchessviz/board.h"
#include "libchessviz/board_move.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ChessBoard* new_board()
{
    ChessBoard* board = malloc(sizeof(ChessBoard));
    if (!board) return NULL;

    strcpy(board->cells[7], "rnbqkbnr");
    strcpy(board->cells[6], "pppppppp");
    strcpy(board->cells[5], "        ");
    strcpy(board->cells[4], "        ");
    strcpy(board->cells[3], "        ");
    strcpy(board->cells[2], "        ");
    strcpy(board->cells[1], "PPPPPPPP");
    strcpy(board->cells[0], "RNBQKBNR");

    return board;
}

char* char_to_pieces(char character)
{
    switch (character) {
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

void print_board(ChessBoard* board, int board_num)
{
    int offset_x = board_num == 0 ? -1 : board_num * 25;
    int offset_y = board_num * 10;

    printf("\e[%dA", offset_y);

    for (int i = CELLS_IN_ROW - 1; i >= 0; i--) {
        printf("\e[%dC", offset_x);
        printf("\e[1;37m%d\e[0m ", (i % CELLS_IN_ROW - 1) + 2);

        for (int j = 0; j < CELLS_IN_ROW; j++) {
            if (((i % CELLS_IN_ROW - 1) + j) % 2 == 0) {
                printf("\e[42m%s \e[0m", char_to_pieces(board->cells[i][j]));
            } else {
                printf("\e[40m%s \e[0m", char_to_pieces(board->cells[i][j]));
            }
        }

        printf("\n");
    }

    printf("\e[%dC", offset_x);
    printf("  \e[1;37ma b c d e f g h\e[0m");
    printf("\n\n");
}

void print_game(ChessBoard* board, MoveRec *moves)
{
    printf("-------------------------------------------\n");

    for (int i = 0; i < moves->numberOfMoves; i++) {
        printf("\t      %d. %s %s\n\n", i + 1, moves->moves[i][0], moves->moves[i][1]);
        
        putchar('\n');

        move(board, moves->moves[i][0]);
        print_board(board, 0);
        move(board, moves->moves[i][1]);
        print_board(board, 1);
        printf("\e[1A");
        printf("-------------------------------------------\n");
    }    
}
