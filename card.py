MAX_WINNING_SCORE = 21


class Card:
    card_types = ['2', '3', '4', '5', '6', '7', '8', '9', 'K', 'A']  # 10, J, Q and K are equivalent
    card_values = {'2': [2], '3': [3], '4': [4], '5': [5], '6': [6], '7': [7], '8': [8], '9': [9], 'K': [10], 'A': [1, 11]}

    def __init__(self, card_type: str):
        assert card_type in Card.card_types
        self.card = card_type

    def get_type(self):
        return self.card

    def get_value(self):
        return Card.card_values[self.card]

    def __str__(self):
        return "%s" % self.card

    def __repr__(self):
        return "%s" % self.card

    def __unicode__(self):
        return "%s" % self.card

    def __hash__(self):
        return min(self.get_value())

    def __eq__(self, other):
        return True if self.get_type() == other.get_type() else False

    def __le__(self, other):
        return True if self.get_value() <= other.get_value() else False

    def __lt__(self, other):
        return True if self.get_value() < other.get_value() else False

    def __ge__(self, other):
        return True if self.get_value() >= other.get_value() else False

    def __gt__(self, other):
        return True if self.get_value() > other.get_value() else False

    @classmethod
    def sum_cards(cls, cards_to_sum: ()) -> int:
        total_sum = 0
        # Sum all cards except aces
        for card in cards_to_sum:
            if card == Card('A'):
                continue
            total_sum += card.get_value()[0]

            # Then, continue with Aces
        for card in cards_to_sum:
            if card == Card('A'):
                if total_sum + max(card.get_value()) <= MAX_WINNING_SCORE:
                    total_sum += max(card.get_value())
                else:
                    total_sum += min(card.get_value())
        return total_sum
