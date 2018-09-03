#include <stdlib.h>
#include "card.h"


char card_types[10] = {'2', '3', '4', '5', '6', '7', '8', '9', 'K', 'A'};
int card_values[10][2] = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {1, 11}};


int* get_value(char card){
    if (card == 'K')
        return card_values[8];
    else if (card == 'A')
        return card_values[9];
    else {
        int x = card - '0';
        return card_values[x - 2];
    }
}
