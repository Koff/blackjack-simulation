#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include "card.h"
#include "deck.h"


void create_initial_deck(Deck *deck){
    /*
     * This method initializes a deck of cards for blackjack
     * Pass it a a deck pointer, and it will do the rest
    */
    deck->number_of_cards = 0;
    int number_of_regular_cards = 4;
    int number_of_aces = 4;
    int number_of_kings = 16;

    // Initialize deck values
    // First common cards
    for (int i=0; i<8; i++){
        deck->number_card_per_type[i] = number_of_regular_cards;
        deck->number_of_cards += number_of_regular_cards;
        for (int j=0; j<number_of_regular_cards; j++){
            deck->cards[i*number_of_regular_cards+j] = (char) (i+2 + '0');
        }
    }
    // Then K's, there are 16 of them: 10, J, Q, K (4 for each)
    deck->number_card_per_type[8] = number_of_kings;
    for (int i=deck->number_of_cards; i<deck->number_of_cards+number_of_kings; i++){
        deck->cards[i] = 'K';
    }
    deck->number_of_cards += number_of_kings;

    // Finally add Aces to deck
    deck->number_card_per_type[9] = number_of_aces;

    for (int i=deck->number_of_cards; i<deck->number_of_cards+number_of_aces; i++){
        deck->cards[i] = 'A';
    }
    deck->number_of_cards += number_of_aces;
}

void remove_card_from_deck_at_index_position(Deck *deck, int position){
    /*
     * Remove card from deck at position
     * Shifts the card positions in a deck, and decrements the number of cards
     */
    memmove(&deck->cards[position], &deck->cards[position+1], (deck->number_of_cards - position -1)*sizeof(char));
    deck->number_of_cards--;

}

int find_card_in_deck(Deck *deck, char card_type){
    /*
     * Loops over all cards in deck to find one like the specified in card_type
     * Returns the index of the corresponding card in deck, or -1 if not found
     */
    for (int i=0; i<deck->number_of_cards; i++) {
        if (card_type == deck->cards[i]) {
            return i;
        }
    }
    return -1;
}

char deal_random_card(Deck *deck){
    int random_card_index = rand() % deck->number_of_cards;
    char random_card = deck->cards[random_card_index];
    remove_card_from_deck_at_index_position(deck, random_card_index);
    return random_card;
}

int deal_specific_card(Deck *deck, char card_type){
    // Find if card is in deck
    int card_index = find_card_in_deck(deck, card_type);
    if (card_index >= 0)
    {
        remove_card_from_deck_at_index_position(deck, card_index);
        return card_index;
    }
    return -1;
}
