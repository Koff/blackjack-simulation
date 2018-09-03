from card import Card
from deck import Deck

MAX_WINNING_SCORE = 21
DEALER_STOPS_AT = 17


class Blackjack:
    def __init__(self):
        # Create deck
        self.deck = Deck()

        # Dealer cards
        self.dealer = {'cards': [], 'total_cards': 0, 'score': 0}

        # Player cards
        self.player = {'cards': [], 'total_cards': 0, 'score': 0}

    def calculate_score(self, of='player'):
        if of == 'player':
            temp = self.player
        else:
            temp = self.dealer

        temp['score'] = 0
        # First count all non Aces
        for card in temp['cards']:
            if card == Card('A'):
                continue
            temp['score'] += max(card.get_value())

        # Then, continue with Aces
        for card in temp['cards']:
            if card == Card('A'):
                if temp['score'] + max(card.get_value()) <= MAX_WINNING_SCORE:
                    temp['score'] += max(card.get_value())
                else:
                    temp['score'] += min(card.get_value())

    def deal_random_card_and_update_scores(self, to='player'):
        if to == 'player':
            card = self.deck.deal_random_card()
            self.player['cards'].append(card)
            self.player['total_cards'] += 1
            self.calculate_score(of=to)
        else:
            card = self.deck.deal_random_card()
            self.dealer['cards'].append(card)
            self.dealer['total_cards'] += 1
            self.calculate_score(of=to)

    def deal_specific_card_and_update_scores(self, card: Card, to='player'):
        if to == 'player':
            card = self.deck.deal_specific_card(card=card)
            self.player['cards'].append(card)
            self.player['total_cards'] += 1
            self.calculate_score(of=to)
        else:
            card = self.deck.deal_specific_card(card=card)
            self.dealer['cards'].append(card)
            self.dealer['total_cards'] += 1
            self.calculate_score(of=to)

    def play_as_dealer(self):
        while self.dealer['score'] < DEALER_STOPS_AT:
            self.deal_random_card_and_update_scores(to='dealer')

    def is_winner_player(self):
        if self.player['score'] > MAX_WINNING_SCORE:
            return False
        elif self.player['score'] <= MAX_WINNING_SCORE < self.dealer['score']:
            return True
        elif self.player['score'] < self.dealer['score']:
            return False
        elif self.player['score'] > self.dealer['score']:
            return True
        elif self.player['score'] == self.dealer['score']:
            return None
