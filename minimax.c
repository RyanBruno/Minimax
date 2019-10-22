#include <string.h>
#include <stdio.h>

int check_for_finished(char board[9], char symbol) {
    /* Horizontal Cases */
    if (board[0] != '-' && board[0] == board[1] && board[0] == board[2]) {
        if (board[0] == symbol)
            return 10;
        return -10;
    }
    if (board[3] != '-' && board[3] == board[4] && board[3] == board[5]) {
        if (board[3] == symbol)
            return 10;
        return -10;
    }
    if (board[6] != '-' && board[6] == board[7] && board[6] == board[8]) {
        if (board[6] == symbol)
            return 10;
        return -10;
    }
    /* Vertical Cases */
    if (board[0] != '-' && board[0] == board[3] && board[0] == board[6]) {
        if (board[0] == symbol)
            return 10;
        return -10;
    }
    if (board[1] != '-' && board[1] == board[4] && board[1] == board[7]) {
        if (board[1] == symbol)
            return 10;
        return -10;
    }
    if (board[2] != '-' && board[2] == board[5] && board[2] == board[8]) {
        if (board[2] == symbol)
            return 10;
        return -10;
    }

    /* Diagonal Case */
    if (board[0] != '-' && board[0] == board[4] && board[0] == board[8]) {
        if (board[0] == symbol)
            return 10;
        return -10;
    }
    if (board[2] != '-' && board[2] == board[4] && board[2] == board[6]) {
        if (board[2] == symbol)
            return 10;
        return -10;
    }

    for (int i = 0; i < 9; i++) {
        if (board[i] == '-')
            return -1;
    }

    return 0;
}

void minimax(const char board[9], int scores_r[9], char symbol, char second_symbol, int min_b)
{
    /* Loop through every slot */
    for (int i = 0; i < 9; i++) {
        int status;

        /* If not empty continue & score -1*/
        if (board[i] != '-') {
            scores_r[i] = 0;
            continue;
        } 
        
        /* Create new board with symbol in slot */
        char new_board[9];
        memcpy(new_board, board, 9);
        new_board[i] = symbol;

        /* Check if someone has won or board is full */
        status = check_for_finished(new_board, symbol);

        if (status != -1) {
            scores_r[i] = status;
            continue;
        }

        {
            int mm_scores[9];
            int min = 10000; 
            int max = -10000;

            /* Recursively run minimax flipping symbols and min_b bool */
            minimax(new_board, mm_scores,
                    second_symbol, symbol, (min_b == 1) ? 0 : 1);

            /* Set slot's score to min or max */
            for (int j = 0; j < 9; j++) {
                if (mm_scores[j] == 0) continue;
                if (mm_scores[j] < min) min = mm_scores[j];
                if (mm_scores[j] > max) max = mm_scores[j];
            }

            if (min_b == 1) {
                scores_r[i] = min;
            } else {
                scores_r[i] = max;
            }
        }
    }
}

int choose_best_slot(int scores[9])
{
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

    while((status = check_for_finished(board, 'X')) == -1) {
        int value[9];

        minimax(board, &value, curr_player, second_player, 1);

        int slot;
        int slot_value = -11;
        
        for (int i = 0; i < 9; i++) {
            if (value[i] == 0 || value[i] < slot_value)
                continue;
            if (value[i] == slot_value)
                if (rand() % 2 == 0)
                    continue;
            slot = i;
            slot_value = value[i];
        }
        printf("%d\n", slot);

        board[slot] = curr_player;

        {
            char temp = curr_player;

            curr_player = second_player;
            second_player = temp;
        }
    }

    for (int i = 0; i < 3; i++) {
        printf("%c | %c | %c\n", board[i], board[i + 1], board[i + 2]);
        if (i < 2) printf("--+---+---\n");
    }

    if (status == 0) {
        printf("Game Ended in a tie\n");
    } else {
        printf("Game did not tie\n");
    }
}
