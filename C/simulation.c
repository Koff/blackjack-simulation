#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "blackjack.h"

int SIMULATION_SIZE = 50000;
int MAX_WINNING_HAND = 21;


int split_hand_by_comma(char *hand, char *results){
    int string_pointer = 0;
    int results_pointer = 0;

    while (hand[string_pointer] != '\0') {
        if (hand[string_pointer] == ','){
            string_pointer++;
            continue;
        }
        if (hand[string_pointer] == '\n') {
            string_pointer++;
            continue;
        }
        results[results_pointer] = hand[string_pointer];
        results_pointer++;
        string_pointer++;
    }
    return results_pointer;
}


int main(){
    // Open results file
    FILE *f_results = fopen("results_one_deck.csv", "w");
    if (f_results == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // Open all possible hands
    FILE* fp;
    char buffer[255];
    fp = fopen("/Users/fsanmartin/Documents/Code/blackjack-simulation-C/results/all_possible_hands_1_deck", "r");

    char dealers_up_card[10] = {'2', '3', '4', '5', '6', '7', '8', '9', 'K', 'A'};
    int progress = 0;

    player_dealer player;
    player_dealer dealer;
    Deck *deck = malloc(sizeof(Deck));

    player.is_player = true;
    dealer.is_player = false;

    int number_of_games = 0;
    int number_of_games_won_by_player = 0;
    int number_of_games_pushed = 0;
    int number_of_games_won_by_dealer = 0;
    char player_starting_hand[45];

    // Read file line by line
    while(fgets(buffer, 255, fp)) {  // Loop over all starting hands
        if (progress % 200 == 0)
            printf("Progress: %3.2f%%\n", 100 * progress/67737.0);
        progress += 1;
        // Deal specific cards to player
        memset(player_starting_hand, 0, 45 * sizeof(char));
        int cards_to_deal_to_player = split_hand_by_comma(buffer, player_starting_hand);

        for (int strategy=0; strategy<2; strategy++) {
            for (int i=0; i<10; i++) {  // Loop over all possible dealers face's up
                // Re-initialize stats
                number_of_games = 0;
                number_of_games_won_by_player = 0;
                number_of_games_pushed = 0;
                number_of_games_won_by_dealer = 0;
                for (int k = 0; k < SIMULATION_SIZE; k++) {  // Loop over simulation size
                    // Create Deck
                    create_initial_deck(deck);

                    // Initialize player
                    player.total_cards = 0;
                    player.score = 0;

                    // Initialize dealer
                    dealer.total_cards = 0;
                    dealer.score = 0;

                    for (int player_hand_index = 0; player_hand_index < cards_to_deal_to_player; player_hand_index++) {
                        deal_specific_card_and_update_scores(&player, deck, player_starting_hand[player_hand_index]);
                    }

                    // If player score is MAX, then no point in simulating
                    if (player.score >= MAX_WINNING_HAND) {
                        break;
                    }

                    // Deal specific card to dealer
                    // If card not in deck, then break
                    if (deal_specific_card_and_update_scores(&dealer, deck, dealers_up_card[i]) < 0)
                        break;

                    // If strategy is hit, then hit!
                    if (strategy > 0)
                        deal_random_card_and_update_scores(&player, deck);

                    // Play as dealer
                    play_as_dealer(&dealer, deck);

                    // Return winner
                    char winner = return_winner(&dealer, &player);

                    // Print results for auditing purposes
//                    char* dealer_hand_str = malloc((size_t) dealer.total_cards);
//                    char* player_hand_str = malloc((size_t) player.total_cards);
//                    strncpy(dealer_hand_str, dealer.cards, dealer.total_cards);
//                    strncpy(player_hand_str, player.cards, player.total_cards);
//                    dealer_hand_str[dealer.total_cards] = '\0';
//                    player_hand_str[player.total_cards] = '\0';
//
//                    printf("[%s] (%d)  --  [%s] (%d)\t||\t%c\n", player_hand_str, player.score, dealer_hand_str, dealer.score, winner);

                    // Assign stats
                    number_of_games++;
                    if (winner == 'd')
                        number_of_games_won_by_dealer++;
                    else if (winner == 'p')
                        number_of_games_won_by_player++;
                    else
                        number_of_games_pushed++;
                }
                // Create string with starting hand for player
                if (number_of_games>0) {
                    fprintf(f_results, "%s,%c,%d,%d,%d,%d,%d\n", player_starting_hand, dealers_up_card[i], strategy, number_of_games, number_of_games_won_by_player, number_of_games_pushed, number_of_games_won_by_dealer);
                }

            }
        }
    }
    fclose(fp);
    fclose(f_results);
    free(deck);
    return 0;
}
