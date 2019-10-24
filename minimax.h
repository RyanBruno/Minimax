/* Ryan Bruno */
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

const char PLAYER_ONE = 'X';
const char PLAYER_TWO = 'O';

struct minimax_move {
    int index;
    int value;
};

enum board_state {
    Winner,
    Loser,
    Tie,
    In_Progress,
};

struct minimax_move
minimax_r(char board[9], char player, char mm_player);

enum board_state
check_board_state(const char board[9], char symbol);

int pick_random_index(const char board[9]);
void print_board(const char board[9]);
