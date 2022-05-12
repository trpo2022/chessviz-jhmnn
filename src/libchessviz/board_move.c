#include "libchessviz/board_move.h"
#include "libchessviz/board.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>


static int schr(char *s, char c)
{
    while (*s) {
        if (c == *s++) return 1;
    }

    return 0;
}

static int letter_to_number(char c)
{
    switch (c)
    {
        case 'a':
            return 1;
        case 'b':
            return 2;
        case 'c':
            return 3;
        case 'd':
            return 4;
        case 'e':
            return 5;
        case 'f':
            return 6;
        case 'g':
            return 7;
        case 'h':
            return 8;
        default:
            return 0;
    }
}

static int is_white(char c)
{
    char *pieces = "RNBQKP";

    return schr(pieces, c);
}

static int is_black(char c)
{
    char *pieces = "rnbqkp";

    return schr(pieces, c);
}

static int check_vertical_move(ChessBoard *board, int start_digit, int target_digit, int start_char)
{
    int i = start_digit - 1;

    target_digit = target_digit < start_digit ? target_digit + 1 : target_digit - 1;
    if (target_digit == start_digit) return 1;

    i = target_digit < start_digit ? i - 1 : i + 1;

    while (i != target_digit - 1) {
        if (board->cells[i][start_char - 1] != ' ') return 0; 
        i = target_digit < start_digit ? i - 1 : i + 1;
    }

    return 1;
}

static int check_horizontal_move(ChessBoard *board, int start_char, int target_char, int start_digit)
{
    int i = start_char - 1;

    target_char = target_char < start_char ? target_char + 1 : target_char - 1;
    if (target_char == start_char) return 1;

    i = target_char < start_char ? i - 1 : i + 1;

    while (i != target_char - 1) {
        if (board->cells[start_digit - 1][i] != ' ') return 0; 
        i = target_char < start_char ? i - 1 : i + 1;
    }

    return 1;
}

static int check_diagonal_move(ChessBoard *board, int start_digit, int target_digit, int start_char, int target_char)
{
    int i = start_digit - 1;
    int j = start_char - 1;

    target_digit = target_digit < start_digit ? target_digit + 1 : target_digit - 1;
    target_char = target_char < start_char ? target_char + 1 : target_char - 1;
    if (target_digit == start_digit && target_char == start_char) return 1;
    
    i = target_digit < start_digit ? i - 1 : i + 1;
    j = target_char < start_char ? j - 1 : j + 1;

    while (i != target_digit - 1) {
        if (board->cells[i][j] != ' ') return 0;
        i = target_digit < start_digit ? i - 1 : i + 1;
        j = target_char < start_char ? j - 1 : j + 1;
    }

    return 1;
}

int check_move_pawn_white(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    int start_digit, target_digit, start_char, target_char;
    char move_type;

    start_digit = move[1] - 48;
    start_char = letter_to_number(move[0]);

    target_digit = move[4] - 48;
    target_char = letter_to_number(move[3]);
    move_type = move[2];

    if (board->cells[start_digit - 1][start_char - 1] != 'P') return 0;
    if (target_digit <= start_digit) return 0;
    if (target_digit - start_digit > PAWN_MAX_MOVE_LEN_DIGIT) return 0;

    if (move_type == '-') {
        if (board->cells[target_digit - 1][target_char - 1] != ' ') return 0;
        if (target_digit - start_digit == 2 && board->cells[start_digit - 1 + 1][start_char - 1] != ' ') return 0;
    } else if (move_type == 'x') {
        if (board->cells[target_digit - 1][target_char - 1] == ' ') return 0;
        if ((start_digit + 1 != target_digit || (start_char + 1 != target_char && start_char - 1 != target_char))) return 0;
        if (is_white(board->cells[target_char - 1][target_char - 1])) return 0;
    }

    return 1;
}

int check_move_pawn_black(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    int start_digit, target_digit, start_char, target_char;
    char move_type;

    start_digit = move[1] - 48;
    start_char = letter_to_number(move[0]);

    target_digit = move[4] - 48;
    target_char = letter_to_number(move[3]);
    move_type = move[2];

    if (board->cells[start_digit - 1][start_char - 1] != 'p') return 0;
    if (target_digit >= start_digit) return 0;
    if (start_digit - target_digit > PAWN_MAX_MOVE_LEN_DIGIT) return 0;

    if (move_type == '-') {
        if (board->cells[target_digit - 1][target_char - 1] != ' ') return 0;
        if (start_digit - target_digit == 2 && board->cells[start_digit - 1 - 1][start_char - 1] != ' ') return 0;
    } else if (move_type == 'x') {
        if (board->cells[target_digit - 1][target_char - 1] == ' ') return 0;
        if ((start_digit - 1 != target_digit || (start_char + 1 != target_char && start_char - 1 != target_char))) return 0;
        if (is_black(board->cells[target_char - 1][target_char - 1])) return 0;
    }

    return 1;
}

int check_move_rook(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    int start_digit, target_digit, start_char, target_char;
    char move_type;

    start_digit = move[2] - 48;
    start_char = letter_to_number(move[1]);

    target_digit = move[5] - 48;
    target_char = letter_to_number(move[4]);
    move_type = move[3];

    if (board->cells[start_digit - 1][start_char - 1] != 'R' && board->cells[start_digit - 1][start_char - 1] != 'r') return 0;
    if (start_digit == target_digit && start_char == target_char) return 0;
    if (start_digit != target_digit && start_char != target_char) return 0;

    if (start_digit != target_digit) {
        if (!check_vertical_move(board, start_digit, target_digit, start_char)) return 0;
    }

    if (start_char != target_char) {
        if (!check_horizontal_move(board, start_char, target_char, start_digit)) return 0;
    }

    if (move_type == '-' && board->cells[target_digit - 1][target_char - 1] != ' ') return 0;
    else if (move_type == 'x') {
        if (board->cells[target_digit - 1][target_char - 1] == ' ') return 0;
        if (is_white(board->cells[start_digit - 1][start_char - 1]) && is_white(board->cells[target_digit - 1][target_char - 1])) return 0;
        if (is_black(board->cells[start_digit - 1][start_char - 1]) && is_black(board->cells[target_digit - 1][target_char - 1])) return 0;
    }

    return 1;
}

int check_move_knight(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    int start_digit, target_digit, start_char, target_char;
    char move_type;

    start_digit = move[2] - 48;
    start_char = letter_to_number(move[1]);

    target_digit = move[5] - 48;
    target_char = letter_to_number(move[4]);
    move_type = move[3];

    int move_digit = target_digit - start_digit;
    move_digit = move_digit < 0 ? move_digit * -1 : move_digit;

    int move_char = target_char - start_char;
    move_char = move_char < 0 ? move_char * -1 : move_char;

    if (board->cells[start_digit - 1][start_char - 1] != 'N' && board->cells[start_digit - 1][start_char - 1] != 'n') return 0;
    if (move_digit == 0 || move_char == 0) return 0;
    if (move_digit > 2 || move_digit == 0 || move_char > 2 || move_char == 0) return 0;
    if (move_digit == 2 && move_char != 1) return 0;
    if (move_digit == 1 && move_char != 2) return 0;

    if (move_type == '-' && board->cells[target_digit - 1][target_char - 1] != ' ') return 0;
    else if (move_type == 'x') {
        if (board->cells[target_digit - 1][target_char - 1] == ' ') return 0;
        if (is_white(board->cells[start_digit - 1][start_char - 1]) && is_white(board->cells[target_digit - 1][target_char - 1])) return 0;
        if (is_black(board->cells[start_digit - 1][start_char - 1]) && is_black(board->cells[target_digit - 1][target_char - 1])) return 0;
    }

    return 1;
}

int check_move_bishop(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    int start_digit, target_digit, start_char, target_char;
    char move_type;

    start_digit = move[2] - 48;
    start_char = letter_to_number(move[1]);

    target_digit = move[5] - 48;
    target_char = letter_to_number(move[4]);
    move_type = move[3];

    int move_digit = target_digit - start_digit;
    move_digit = move_digit < 0 ? move_digit * -1 : move_digit;

    int move_char = target_char - start_char;
    move_char = move_char < 0 ? move_char * -1 : move_char;

    if (board->cells[start_digit - 1][start_char - 1] != 'B' && board->cells[start_digit - 1][start_char - 1] != 'b') return 0;
    if (move_digit == 0 || move_char == 0) return 0;
    if (move_digit != move_char) return 0;

    if (!check_diagonal_move(board, start_digit, target_digit, start_char, target_char)) return 0;

    if (move_type == '-' && board->cells[target_digit - 1][target_char - 1] != ' ') return 0;
    else if (move_type == 'x') {
        if (board->cells[target_digit - 1][target_char - 1] == ' ') return 0;
        if (is_white(board->cells[start_digit - 1][start_char - 1]) && is_white(board->cells[target_digit - 1][target_char - 1])) return 0;
        if (is_black(board->cells[start_digit - 1][start_char - 1]) && is_black(board->cells[target_digit - 1][target_char - 1])) return 0;
    }

    return 1;
}

int check_move_king(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    int start_digit, target_digit, start_char, target_char;
    char move_type;

    start_digit = move[2] - 48;
    start_char = letter_to_number(move[1]);

    target_digit = move[5] - 48;
    target_char = letter_to_number(move[4]);
    move_type = move[3];

    int move_digit = target_digit - start_digit;
    move_digit = move_digit < 0 ? move_digit * -1 : move_digit;

    int move_char = target_char - start_char;
    move_char = move_char < 0 ? move_char * -1 : move_char;

    if (board->cells[start_digit - 1][start_char - 1] != 'K' && board->cells[start_digit - 1][start_char - 1] != 'k') return 0;
    if (move_digit == 0 && move_char == 0) return 0;
    if (move_digit > 1 || move_char > 1) return 0;

    if (move_type == '-' && board->cells[target_digit - 1][target_char - 1] != ' ') return 0;
    else if (move_type == 'x') {
        if (board->cells[target_digit - 1][target_char - 1] == ' ') return 0;
        if (is_white(board->cells[start_digit - 1][start_char - 1]) && is_white(board->cells[target_digit - 1][target_char - 1])) return 0;
        if (is_black(board->cells[start_digit - 1][start_char - 1]) && is_black(board->cells[target_digit - 1][target_char - 1])) return 0;
    }

    return 1;
}

int check_move_queen(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    int start_digit, target_digit, start_char, target_char;
    char move_type;

    start_digit = move[2] - 48;
    start_char = letter_to_number(move[1]);

    target_digit = move[5] - 48;
    target_char = letter_to_number(move[4]);
    move_type = move[3];

    int move_digit = target_digit - start_digit;
    move_digit = move_digit < 0 ? move_digit * -1 : move_digit;

    int move_char = target_char - start_char;
    move_char = move_char < 0 ? move_char * -1 : move_char;

    if (board->cells[start_digit - 1][start_char - 1] != 'Q' && board->cells[start_digit - 1][start_char - 1] != 'q') return 0;
    if (move_digit == 0 && move_char == 0) return 0;

    if (move_digit == 0) {
        if (!check_horizontal_move(board, start_char, target_char, start_digit)) return 0;
    } else if (move_char == 0) {
        if (!check_vertical_move(board, start_digit, target_digit, start_char)) return 0;
    } else if (move_digit == move_char) {
        if (!check_diagonal_move(board, start_digit, target_digit, start_char, target_char)) return 0;
    } else {
        return 0;
    }

    if (move_type == '-' && board->cells[target_digit - 1][target_char - 1] != ' ') return 0;
    else if (move_type == 'x') {
        if (board->cells[target_digit - 1][target_char - 1] == ' ') return 0;
        if (is_white(board->cells[start_digit - 1][start_char - 1]) && is_white(board->cells[target_digit - 1][target_char - 1])) return 0;
        if (is_black(board->cells[start_digit - 1][start_char - 1]) && is_black(board->cells[target_digit - 1][target_char - 1])) return 0;
    }

    return 1;
}

int check_move(ChessBoard *board, char *move)
{
    if (!board || !move) return 0;

    switch (move[0])
    {
        case 'R':
            return check_move_rook(board, move);
        case 'N':
            return check_move_knight(board, move);
        case 'B':
            return check_move_bishop(board, move);
        case 'Q':
            return check_move_queen(board, move);
        case 'K':
            return check_move_king(board, move);
        default:
            if (is_white(board->cells[move[1] - 48 - 1][letter_to_number(move[0]) - 1])) return check_move_pawn_white(board, move);
            else return check_move_pawn_black(board, move);
    }
}

int check_all_moves(ChessBoard board, MoveRec *moves)
{
    if (!moves) return 0;

    for (int i = 0; i < moves->numberOfMoves; i++) {
        if (isdigit(moves->moves[i][0][1])) {
            if (!is_white(board.cells[moves->moves[i][0][1] - 48 - 1][letter_to_number(moves->moves[i][0][0]) - 1])) return 0;
        } else {
            if (!is_white(board.cells[moves->moves[i][0][2] - 48 - 1][letter_to_number(moves->moves[i][0][1]) - 1])) return 0;
        }

        if (!check_move(&board, moves->moves[i][0])) return 0;
        move(&board, moves->moves[i][0]);
        
        if (strlen(moves->moves[i][1]) == 0) return 1;

        if (isdigit(moves->moves[i][1][1])) {
            if (!is_black(board.cells[moves->moves[i][1][1] - 48 - 1][letter_to_number(moves->moves[i][1][0]) - 1])) return 0;
        } else {
            if (!is_black(board.cells[moves->moves[i][1][2] - 48 - 1][letter_to_number(moves->moves[i][1][1]) - 1])) return 0;
        }

        if (!check_move(&board, moves->moves[i][1])) return 0;
        move(&board, moves->moves[i][1]);
    }

    return 1;
}

void move(ChessBoard *board, char *move)
{
    if (!board || !move) return;

    if (isdigit(move[1])) {
        board->cells[move[4] - 48 - 1][letter_to_number(move[3]) - 1] = board->cells[move[1] - 48 - 1][letter_to_number(move[0]) - 1];
        board->cells[move[1] - 48 - 1][letter_to_number(move[0]) - 1] = ' ';
    } else {
        board->cells[move[5] - 48 - 1][letter_to_number(move[4]) - 1] = board->cells[move[2] - 48 - 1][letter_to_number(move[1]) - 1];
        board->cells[move[2] - 48 - 1][letter_to_number(move[1]) - 1] = ' ';
    }
}
