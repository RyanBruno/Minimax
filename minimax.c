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


int main()
{
    int value[9];

    minimax("---------", &value, 'X', 'O', 1);

    for (int i = 0; i < 9; i++) {
        printf("%d ", value[i]);
    }
    printf("\n");
}
