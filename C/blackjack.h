//
// Created by Fernando San Martin Jorquera on 7/13/18.
//

#ifndef BLACKJACK_SIMULATION_C_BLACKJACK_H
#define BLACKJACK_SIMULATION_C_BLACKJACK_H

#include <stdbool.h>
#include "card.h"
#include "deck.h"

typedef struct {
    int total_cards;
    int score;
    bool is_player;
    char cards[52];
} player_dealer;

void calculate_score(player_dealer *p);
void deal_random_card_and_update_scores(player_dealer *p, Deck *d);
int deal_specific_card_and_update_scores(player_dealer *p, Deck *d, char card_type);
void play_as_dealer(player_dealer *dealer, Deck *deck);
char return_winner(player_dealer *dealer, player_dealer *player);
#endif //BLACKJACK_SIMULATION_C_BLACKJACK_H
