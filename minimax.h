#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum min_or_max  {
    Minimax_Min,
    Minimax_Max,
};
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

