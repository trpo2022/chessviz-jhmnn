#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BoardSize 8

int check_symbol_in_array(char symbol, char array[])
{
    for (int i = 0; i < strlen(array); i++) {
        if (symbol == array[i]) {
            return 0;
        }
    }

    return 1;
}

int check_input_correctness(char symbol)
{
    char chessPieces[] = "RNBQKBNRPrnbqkbnrpabcdefgh12345678-+x# ";

    for (int i = 0; i < strlen(chessPieces); i++) {
        if (symbol == chessPieces[i]) {
            return 0;
        }
    }

    return 1;
}

void read_moves_console()
{
    int movesCount = 0;
    int numAddedMoves = 10;
    int maxSymbolsInMove = 17;
    char currentSymbol = ' ';
    char **moves = malloc(numAddedMoves * maxSymbolsInMove * sizeof(char));

    if (moves == NULL) {
        return;
    } 

    for (int i = 0;; i++) {
        movesCount += 1;
        printf("%d. ", i + 1);
        
        for (int j = 0; j < maxSymbolsInMove && currentSymbol != '\n' &&currentSymbol != '#'; j++) {
            currentSymbol = getchar();

            if (!check_input_correctness(currentSymbol)) {
                return;
            }

            moves[i][j] = currentSymbol;
        }

        if (currentSymbol == '#') {
            break;
        }
    }
}

char **new_board()
{
    char **board = malloc(BoardSize * (BoardSize + BoardSize) * sizeof(char));

    if (board == NULL) {
        return 0;
    }

    board[7] = "♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖";
    board[6] = "♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙";
    board[5] = "☐ ☐ ☐ ☐ ☐ ☐ ☐ ☐";
    board[4] = "☐ ☐ ☐ ☐ ☐ ☐ ☐ ☐";
    board[3] = "☐ ☐ ☐ ☐ ☐ ☐ ☐ ☐";
    board[2] = "☐ ☐ ☐ ☐ ☐ ☐ ☐ ☐";
    board[1] = "♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟";
    board[0] = "♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜";   

    return board;
}

void print_board(char **board)
{
    for (int i = BoardSize; i > 0; i--) {
        printf("\e[1;36m%d\033[0m ", i);
        printf("\e[1;37m%s\033[0m\n", board[i - 1]);
    }

    printf("  ");

    for (int i = 97; i < 97 + BoardSize; i++) {
        printf("\e[1;36m%c\033[0m ", i);
    }

    printf("\n");
}

int main()
{
    char **board = new_board();

    print_board(board);
    printf("\n%ld\n", strlen(board[7]));
    return 0;
}