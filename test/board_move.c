#include <ctest.h>

#include "libchessviz/board.c"
#include "libchessviz/board_move.c"


CTEST(check, check_move_pawn_white) {
    ChessBoard *board = new_board();
    char *move1 = "c2-c4";
    char *move2 = "c2-c5";

    ASSERT_EQUAL(1, check_move_pawn_white(board, move1));
    ASSERT_EQUAL(0, check_move_pawn_white(NULL, move1));
    ASSERT_EQUAL(0, check_move_pawn_white(board, NULL));
    ASSERT_EQUAL(0, check_move_pawn_white(NULL, NULL));
    ASSERT_EQUAL(0, check_move_pawn_white(board, move2));
}

CTEST(check, check_move_pawn_black) {
    ChessBoard *board = new_board();
    char *move1 = "c7-c5";
    char *move2 = "c2-c5";

    ASSERT_EQUAL(1, check_move_pawn_black(board, move1));
    ASSERT_EQUAL(0, check_move_pawn_black(NULL, move1));
    ASSERT_EQUAL(0, check_move_pawn_black(board, NULL));
    ASSERT_EQUAL(0, check_move_pawn_black(NULL, NULL));
    ASSERT_EQUAL(0, check_move_pawn_black(board, move2));
}

CTEST(check, check_move_bishop) {
    ChessBoard *board = new_board();
    move(board, "e2-e4");
    char *move1 = "Bf1-d3";
    char *move2 = "c2-c5";

    ASSERT_EQUAL(1, check_move_bishop(board, move1));
    ASSERT_EQUAL(0, check_move_bishop(NULL, move1));
    ASSERT_EQUAL(0, check_move_bishop(board, NULL));
    ASSERT_EQUAL(0, check_move_bishop(NULL, NULL));
    ASSERT_EQUAL(0, check_move_bishop(board, move2));
}

CTEST(check, check_move_knight) {
    ChessBoard *board = new_board();
    char *move1 = "Ng1-h3";
    char *move2 = "c2-c5";

    ASSERT_EQUAL(1, check_move_knight(board, move1));
    ASSERT_EQUAL(0, check_move_knight(NULL, move1));
    ASSERT_EQUAL(0, check_move_knight(board, NULL));
    ASSERT_EQUAL(0, check_move_knight(NULL, NULL));
    ASSERT_EQUAL(0, check_move_knight(board, move2));
}

CTEST(check, check_move_rook) {
    ChessBoard *board = new_board();
    move(board, "h2-h4");
    char *move1 = "Rh1-h3";
    char *move2 = "c2-c5";

    ASSERT_EQUAL(1, check_move_rook(board, move1));
    ASSERT_EQUAL(0, check_move_rook(NULL, move1));
    ASSERT_EQUAL(0, check_move_rook(board, NULL));
    ASSERT_EQUAL(0, check_move_rook(NULL, NULL));
    ASSERT_EQUAL(0, check_move_rook(board, move2));
}

CTEST(check, check_move_queen) {
    ChessBoard *board = new_board();
    move(board, "e2-e4");
    char *move1 = "Qd1-g4";
    char *move2 = "c2-c5";

    ASSERT_EQUAL(1, check_move_queen(board, move1));
    ASSERT_EQUAL(0, check_move_queen(NULL, move1));
    ASSERT_EQUAL(0, check_move_queen(board, NULL));
    ASSERT_EQUAL(0, check_move_queen(NULL, NULL));
    ASSERT_EQUAL(0, check_move_queen(board, move2));
}

CTEST(check, check_move_king) {
    ChessBoard *board = new_board();
    move(board, "e2-e4");
    char *move1 = "Ke1-e2";
    char *move2 = "e1-e3";

    ASSERT_EQUAL(1, check_move_king(board, move1));
    ASSERT_EQUAL(0, check_move_king(NULL, move1));
    ASSERT_EQUAL(0, check_move_king(board, NULL));
    ASSERT_EQUAL(0, check_move_king(NULL, NULL));
    ASSERT_EQUAL(0, check_move_king(board, move2));
}

CTEST(check, check_move) {
    ChessBoard *board = new_board();
    char *move1 = "c2-c4";
    char *move2 = "c2-c5";

    ASSERT_EQUAL(1, check_move(board, move1));
    ASSERT_EQUAL(0, check_move(NULL, move1));
    ASSERT_EQUAL(0, check_move(board, NULL));
    ASSERT_EQUAL(0, check_move(NULL, NULL));
    ASSERT_EQUAL(0, check_move(board, move2));
}

CTEST(check, check_all_moves) {
    ChessBoard *board = new_board();
    MoveRec *rec = malloc(sizeof(MoveRec));

    char *move1 = "e2-e4", *move2 = "e7-e5", *move3 = "c2-c4", *move4 = "c7-c5#";

    strcpy(rec->moves[0][0], move1);
    strcpy(rec->moves[0][1], move2);
    strcpy(rec->moves[1][0], move3);
    strcpy(rec->moves[1][1], move4);

    rec->numberOfMoves = 2;

    ASSERT_EQUAL(1, check_all_moves(*board, rec));
    ASSERT_EQUAL(0, check_all_moves(*board, NULL));
}

CTEST(check, is_white) {
    ChessBoard *board = new_board();

    ASSERT_EQUAL(1, is_white(board->cells[0][0]));
    ASSERT_EQUAL(0, is_white(board->cells[7][0]));
}

CTEST(check, is_black) {
    ChessBoard *board = new_board();

    ASSERT_EQUAL(1, is_black(board->cells[7][0]));
    ASSERT_EQUAL(0, is_black(board->cells[0][0]));
}

CTEST(check, letter_to_number) {
    ASSERT_EQUAL(1, letter_to_number('a'));
    ASSERT_EQUAL(0, letter_to_number('j'));
}
