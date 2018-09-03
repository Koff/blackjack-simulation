//
// Created by Fernando San Martin Jorquera on 7/13/18.
//

#ifndef BLACKJACK_SIMULATION_C_DECK_H
#define BLACKJACK_SIMULATION_C_DECK_H


typedef struct {
    int number_card_per_type[10];
    int number_of_cards;
    char cards[52];
} Deck;

void create_initial_deck(Deck *deck);
void remove_card_from_deck_at_index_position(Deck *deck, int position);
int find_card_in_deck(Deck *deck, char card_type);
char deal_random_card(Deck *deck);
int deal_specific_card(Deck *deck, char card_type);

#endif //BLACKJACK_SIMULATION_C_DECK_H
