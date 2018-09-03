from pickle import dump
from random import choice

from card import Card

MAX_WINNING_SCORE = 21


class Deck:
    number_card_per_type = [4, 4, 4, 4, 4, 4, 4, 4, 16, 4]

    def __init__(self):
        self.cards = []

        # Create initial deck
        for i, c in enumerate(Card.card_types):
            for _ in range(0, Deck.number_card_per_type[i]):
                self.cards.append(Card(c))

        # Add auxiliary information
        self.total_cards = len(self.cards)

    def deal_random_card(self):
        # Get random card
        card = choice(self.cards)
        # Decrement total cards
        self.total_cards -= 1
        # Pop card from deck
        return self.cards.pop(self.cards.index(card))

    def deal_specific_card(self, card: Card):
        # Decrement total cards
        self.total_cards -= 1

        for c in self.cards:
            if card == c:
                return self.cards.pop(self.cards.index(c))
        # Pop card from deck

    def all_cards_that_wont_bust(self, current_score: int=0):
        if current_score >= MAX_WINNING_SCORE:
            return None

        diff = MAX_WINNING_SCORE - current_score
        all_cards_that_wont_bust = []
        for card in self.cards:
            if min(card.get_value()) <= diff and card not in all_cards_that_wont_bust:
                all_cards_that_wont_bust.append(card)

        return all_cards_that_wont_bust

    def __getitem__(self, item):
        return self.cards[item]


def generate_all_possible_hands():
    d = Deck()
    import itertools
    counter = 0

    all_first_hand_combinations = set()
    all_possible_combinations = set()

    # First generate all combinations of 2 cards
    for subset in itertools.combinations(d.cards, 2):
        all_first_hand_combinations.update((subset,))
        all_possible_combinations.update((subset,))
        counter += 1

    # Then build the remaining combinations that start with the two cards before
    for comb in all_first_hand_combinations:
        print("Processing starting hand: %s, combinations found: %s" % (comb, len(all_possible_combinations)))
        recursive_deal(comb, all_possible_combinations)

    # Finally, let's remove all combinations that sum 21.
    all_possible_combinations_under_21 = []
    for comb in all_possible_combinations:
        if Card.sum_cards(comb) < MAX_WINNING_SCORE:
            all_possible_combinations_under_21.append(comb)

    dump(all_possible_combinations_under_21, open('results/all_possible_hands_1_deck.pck', 'wb'))
    print("counter: %s" % counter)


def recursive_deal(comb, all_possible_combinations):
    # deal new cards
    new_deck = Deck()
    [new_deck.deal_specific_card(c) for c in comb]

    all_possible_combinations.update((comb, ))

    all_crds_that_wont_bust = new_deck.all_cards_that_wont_bust(current_score=Card.sum_cards(comb))
    if all_crds_that_wont_bust is None:
        return None

    for crd in all_crds_that_wont_bust:
        recursive_deal(comb + (crd, ), all_possible_combinations)


if __name__ == '__main__':
    generate_all_possible_hands()
