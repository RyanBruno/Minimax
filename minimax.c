#include <string.h>
#include <limits.h>
#include <stdio.h>

enum board_state {
    Winner,
    Loser,
    Tie,
    In_Progress,
};

enum board_state
check_for_finished(char board[9], char symbol) {
    /* Horizontal Cases */
    if (board[0] != '-' && board[0] == board[1] && board[0] == board[2]) {
        if (board[0] == symbol)
            return Winner;
        return Loser;
    }
    if (board[3] != '-' && board[3] == board[4] && board[3] == board[5]) {
        if (board[3] == symbol)
            return Winner;
        return Loser;
    }
    if (board[6] != '-' && board[6] == board[7] && board[6] == board[8]) {
        if (board[6] == symbol)
            return Winner;
        return Loser;
    }
    /* Vertical Cases */
    if (board[0] != '-' && board[0] == board[3] && board[0] == board[6]) {
        if (board[0] == symbol)
            return Winner;
        return Loser;
    }
    if (board[1] != '-' && board[1] == board[4] && board[1] == board[7]) {
        if (board[1] == symbol)
            return Winner;
        return Loser;
    }
    if (board[2] != '-' && board[2] == board[5] && board[2] == board[8]) {
        if (board[2] == symbol)
            return Winner;
        return Loser;
    }

    /* Diagonal Case */
    if (board[0] != '-' && board[0] == board[4] && board[0] == board[8]) {
        if (board[0] == symbol)
            return Winner;
        return Loser;
    }
    if (board[2] != '-' && board[2] == board[4] && board[2] == board[6]) {
        if (board[2] == symbol)
            return Winner;
        return Loser;
    }

    for (int i = 0; i < 9; i++) {
        if (board[i] == '-')
            return In_Progress;
    }

    return Tie;
}

struct move {
    int index;
    int value;
};
/* Board must be in In_Progress state */
struct move
minimax(const char board[9], char symbol, char second_symbol, int min_b)
{
    int move_index = -1;
    int max = INT_MIN;
    int min = INT_MAX;
    struct move m;

    /* Loop through every slot */
    for (int i = 0; i < 9; i++) {
        enum board_state s;
        char new_board[9];
        int score;

        /* If not empty continue & score -1*/
        if (board[i] != '-') {
            continue;
        } 
        
        /* Create new board with symbol in slot */
        memcpy(new_board, board, 9);
        new_board[i] = symbol;


        /* Get the board status */
        s = check_for_finished(new_board, symbol);

        switch (s) {
        case Winner:
            score = 1;
            break;
        case Loser:
            score = -1;
            break;
        case Tie:
            score = 0;
            break;
        case In_Progress:
            m = minimax(new_board, second_symbol,
                    symbol, (min_b == 1) ? 0 : 1);
            score = m.value;
            break;
        }

        if (score > max) {
            max = score;
            move_index = i;
        }

        if (score < min) {
            min = score;
        }
    }

    if (min_b == 1) {
        m.index = move_index;
        m.value = max;
    } else {
        m.index = -1;
        m.value = min;
    }

    return m;
}

int main()
{
    int selection;

    printf("[1] Both players use minimax\n");
    printf("[2] Player one uses minimax and player two has a 50%% chance of using minimax\n");
    printf("[3] Player one has a 50%% chance of using minimax and player two uses minimax\n");
    printf("Make a section [1, 2, 3]: ");

    scanf("%d", &selection);


    char board[9] = "---------";
    int status;
    char curr_player = 'X';
    char second_player = 'O';

    while(check_for_finished(board, 'X') == In_Progress) {
        struct move m;

        m = minimax(board, curr_player, second_player, 1);

        printf("Moved player (%c) to index %d with score %d\n", curr_player, m.index, m.value);
        board[m.index] = curr_player;

        for (int i = 0; i < 9; i+= 3) {
            printf("%c | %c | %c\n", board[i], board[i + 1], board[i + 2]);
            if (i < 6) printf("--+---+---\n");
        }
         printf("\n\n");

        {
            char temp = curr_player;

            curr_player = second_player;
            second_player = temp;
        }
    }

    switch (check_for_finished(board, 'X')) {
        case Winner:
            printf("Player (X) has Won!");
            break;
        case Loser:
            printf("Player (O) has Won!");
            break;
        case Tie:
            printf("Tie Game!");
            break;
    };

}
/*
 *
        printf("%c\n", curr_player);
        for (int i = 0; i < 3; i++) {
            printf("%d | %d | %d\n", value[i], value[i + 1], value[i + 2]);
            if (i < 2) printf("--+---+---\n");
        }
        */
