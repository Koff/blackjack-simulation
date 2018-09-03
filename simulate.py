# This attempts to find the perfect basic strategy for a 1-deck card
import pickle
import logging

import boto3

from blackjack import Blackjack
from card import Card

SIMULATION_SIZE = int(1e2)
MAX_WINNING_SCORE = 21


def main(logger):
    progress_counter = 0
    results_matrix = {}
    all_possible_hands = pickle.load(open('results/all_possible_hands_1_deck.pck', 'rb'))

    # Initialize results dictionary
    for hand in all_possible_hands:
        hands_str = "%s" % '-'.join([str(c) for c in hand])
        results_matrix[hands_str] = {}
        for card in Card.card_types:
            results_matrix[hands_str][card] = {'hit': {}, 'stay': {}}
            results_matrix[hands_str][card]['hit'] = {'totals': 0, 'wins': 0, 'losses': 0, 'pushes': 0}
            results_matrix[hands_str][card]['stay'] = {'totals': 0, 'wins': 0, 'losses': 0, 'pushes': 0}

    len_all_possible_hands = 2 * len(all_possible_hands)
    for staying_strategy in (True, False):
        for hand in all_possible_hands:
            progress_counter += 1
            # Calculate player's hand
            player_hand_str = "%s" % '-'.join([str(c) for c in hand])

            for card in Card.card_types:
                logger.info("[Game] Player: %s - vs - Dealers: %s, Completed: %s / %s " % (hand, card, progress_counter, len_all_possible_hands))
                # Results pointer, to avoid solving the dict on each access
                if staying_strategy:
                    point = results_matrix[player_hand_str][card]['stay']
                else:
                    point = results_matrix[player_hand_str][card]['hit']
                # Loop over simulation size
                for _ in range(0, SIMULATION_SIZE):
                    # Instance of blackjack
                    b = Blackjack()
                    # Deal pre determined cards to player
                    [b.deal_specific_card_and_update_scores(c, to='player') for c in hand]
                    if b.player['score'] >= MAX_WINNING_SCORE:
                        continue

                    if Card(card) not in b.deck:
                        break

                    # Specific face up card to dealer
                    b.deal_specific_card_and_update_scores(Card(card), to='dealer')

                    # If we are not staying, we get one more card.
                    if not staying_strategy:
                        b.deal_random_card_and_update_scores(to='player')

                    # Increase total cards
                    point['totals'] += 1

                    # Play hand as dealer
                    b.play_as_dealer()
                    # Return the winner
                    winner = b.is_winner_player()
                    if winner is False:
                        point['losses'] += 1
                    elif winner is True:
                        point['wins'] += 1
                    else:
                        point['pushes'] += 1
                logger.info("[Stats] Wins: %s, Losses: %s, Pushes: %s" % (point['wins'], point['losses'], point['pushes']))
    return results_matrix


if __name__ == '__main__':
    # Create logger
    logger = logging.getLogger('blackjack_simulation')
    logger.setLevel(logging.DEBUG)
    ch = logging.StreamHandler()
    ch.setLevel(logging.DEBUG)
    # create formatter
    formatter = logging.Formatter('[%(asctime)s] - %(levelname)s - %(message)s')
    # add formatter to ch
    ch.setFormatter(formatter)
    # add ch to logger
    logger.addHandler(ch)

    logger.info("Starting staying simulation with parameters")
    logger.info("\tSIMULATION_SIZE = %s" % SIMULATION_SIZE)

    results = main(logger=logger)

    logger.info("[100%] Completed! 🎉")
    pickle.dump(results, open('results/simulation_results_standing.pck', 'wb'))

    logger.info("Uploading to S3....")
    # Upload results to S3
    s3 = boto3.resource('s3',
                        aws_access_key_id='{access-key}',
                        aws_secret_access_key='access-secret')

    s3.Object('palaceodds-postgres-backups', 'blackjack-simulation.pck').\
        put(Body=open('results/simulation_results_standing.pck', 'rb'))
    logger.info("Uploaded!!")
