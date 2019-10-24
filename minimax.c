#include "minimax.h"

enum board_state
check_board_state(const char board[9], char symbol) {
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

/* Board must be in In_Progress state */
struct minimax_move
minimax(const char board[9], char player, char opponent, enum min_or_max mm)
{
    int move_index = -1;
    int max = INT_MIN;
    int min = INT_MAX;
    struct minimax_move m;

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
        new_board[i] = (mm == Minimax_Max) ? player : opponent;

        /* Get the board status */
        s = check_board_state(new_board, player);

        /* Check for base cases */
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
        /* If still in progress recurse */
        case In_Progress:
            m = minimax(new_board, player, opponent,
                    (mm == Minimax_Max) ? Minimax_Min : Minimax_Max);
            score = m.value;
            break;
        }

        /* Update the min and max values if necessary */
        if (score >= max) {
            max = score;
            move_index = i;
        }

        if (score <= min) {
            min = score;
        }
    }

    /* Set the return values */
    if (mm == Minimax_Max) {
        m.index = move_index;
        m.value = max;
    } else {
        m.index = -1;
        m.value = min;
    }

    return m;
}

int pick_random_index(const char board[9]) {
    int r;

    while (1) {
        r = rand() % 9;
        if (board[r] == '-')
            return r;
    }
}

void print_board(const char board[9])
{
    /* Prints new board */
    for (int i = 0; i < 9; i+= 3) {
        printf("%c | %c | %c\n", board[i], board[i + 1], board[i + 2]);
        if (i < 6) printf("--+---+---\n");
    }
    printf("\n\n");
}

int main()
{
    int selection = 0;
    char board[9] = "---------";
    char player_one = 'X';
    float player_one_probability = RAND_MAX;
    char player_two = 'O';
    float player_two_probability = RAND_MAX;

    /* Prompt and selection */
    printf("[1] Both players use minimax\n");
    printf("[2] Player one (X) uses minimax and player two (O) has a 50%% chance of using minimax\n");
    printf("[3] Player one (X) has a 50%% chance of using minimax and player two (O) uses minimax\n");
    while (selection < 1 || selection > 3) {
        printf("Make a section [1, 2, 3]: ");
        scanf("%d", &selection);
    }

    /* Based on selection half the probability of selected player */
    switch (selection) {
        case 2:
            player_two_probability = RAND_MAX / 2;
            break;
        case 3:
            player_one_probability = RAND_MAX / 2;
            break;
    }

    /* The main board loop */
    while(check_board_state(board, 'X') == In_Progress) {
        struct minimax_move m;

        /* Runs the minimax */
        m = minimax(board, player_one, player_two, Minimax_Max);

        /* Chose index randomly if applicable */
        if (rand() > player_one_probability)
            m.index = pick_random_index(board);

        /* Updates board and prints */
        printf("Moved player (%c) to index %d with score %d\n", player_one, m.index, m.value);
        board[m.index] = player_one;
        print_board(board);

        /* Chose index randomly if applicable */
        if (check_board_state(board, 'X') != In_Progress)
            break;

        m = minimax(board, player_two, player_one, Minimax_Max);

        if (rand() > player_two_probability)
            m.index = pick_random_index(board);

        /* Updates board and prints */
        printf("Moved player (%c) to index %d with score %d\n", player_two, m.index, m.value);
        board[m.index] = player_two;
        print_board(board);
    }

    switch (check_board_state(board, 'X')) {
        case Winner:
            printf("Player one (X) has Won!\n");
            break;
        case Loser:
            printf("Player two (O) has Won!\n");
            break;
        case Tie:
            printf("Tie Game!\n");
            break;
        case In_Progress:
            printf("A strange error has occurred!\n");
            // Error
            break;
    };

}
