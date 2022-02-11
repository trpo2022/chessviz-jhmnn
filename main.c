#include <stdio.h>

#define BoardSize 8

void print_board(char board[][BoardSize])
{
    for (int i = BoardSize; i > 0; i--) {
        printf("%d ", i);

        for (int j = 0; j < BoardSize; j++) {
            printf("%c ", board[i - 1][j]);
        }

        printf("\n");
    }

    printf("  ");

    for (int i = 97; i < 97 + BoardSize; i++) {
        printf("%c ", i);
    }

    printf("\n");
}

int main()
{
    char board[][BoardSize] = {"RNBQKBNR", "PPPPPPPP", "        ", "        ", "        ", "        ", "pppppppp", "rnbqkbnr"};

    print_board(board);
    return 0;
}