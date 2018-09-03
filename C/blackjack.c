#include <printf.h>
#include "card.h"
#include "deck.h"
#include "blackjack.h"


int MAX_WINNING_SCORE = 21;
int DEALER_STOPS_AT = 17;


int sum_cards(char *cards, int number_of_cards) {
    int temp_score = 0;
    for (int i=0; i<number_of_cards; i++){
        if (cards[i] == 'A')
            continue;
        temp_score += get_value(cards[i])[0];
    }
    for (int i=0; i<number_of_cards; i++){
        if (cards[i] == 'A') {
            if (temp_score + get_value(cards[i])[1] <= MAX_WINNING_SCORE) {
                temp_score += get_value(cards[i])[1];
            }
            else {
                temp_score += get_value(cards[i])[0];
            }
        }
    }
    return temp_score;
}

void calculate_score(player_dealer *p){
    // Update score
    p->score = sum_cards(p->cards, p->total_cards);
}

void deal_random_card_and_update_scores(player_dealer *p, Deck *d){
    char random_card = deal_random_card(d);
    p->cards[p->total_cards] = random_card;
    p->total_cards++;
    calculate_score(p);
}

int deal_specific_card_and_update_scores(player_dealer *p, Deck *d, char card_type){
    int deal_specific_card_results = deal_specific_card(d, card_type);
    // if the card couldn't be found in deck
    if (deal_specific_card_results < 0)
        return -1;

    char new_card;
    new_card = card_type;
    p->cards[p->total_cards] = new_card;
    p->total_cards++;
    calculate_score(p);

    return deal_specific_card_results;
}

void play_as_dealer(player_dealer *dealer, Deck *deck) {
    while (dealer->score < DEALER_STOPS_AT){
        deal_random_card_and_update_scores(dealer, deck);
    }
}

char return_winner(player_dealer *dealer, player_dealer *player){
    if (player->score > MAX_WINNING_SCORE)
        return 'd';
    else if (dealer->score > MAX_WINNING_SCORE)
        return 'p';
    else if (player->score > dealer->score)
        return 'p';
    else if (player->score < dealer->score)
        return 'd';
    else
        return 'x';
}