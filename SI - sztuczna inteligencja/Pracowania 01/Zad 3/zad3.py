import random
card_val = {
    2: 2,
    3: 3,
    4: 4,
    5: 5,
    6: 6,
    7: 7,
    8: 8,
    9: 9,
    10: 10,
    'J': 11,
    'Q': 12,
    'K': 13,
    'A': 14
}

# --------------------------------------------------------------
# Hand ranking categories


def straight_flush(hand):
    suits = hand[1]
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    for i in range(1, len(cards)):
        if cards[i] != cards[i - 1] + 1:
            return False

        if suits[i] != suits[i - 1]:
            return False

    return sum(cards)


def four_of_a_kind(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    first_4 = cards[0] == cards[1] == cards[2] == cards[3]
    last_4 = cards[1] == cards[2] == cards[3] == cards[4]
    if first_4:
        return (cards[0], cards[3])

    if last_4:
        return (cards[4], cards[4])

    return False


def full_house(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    first_3 = cards[0] == cards[1] == cards[2]
    last_2 = cards[3] == cards[4]

    first_2 = cards[0] == cards[1]
    last_3 = cards[2] == cards[3] == cards[4]

    if first_3 and last_2:
        return (cards[0], cards[4])

    if first_2 and last_3:
        return (cards[4], cards[0])

    return False


def flush(hand):
    suits = hand[1]
    cards = [card_val[card] for card in hand[0]]
    cards.sort(reverse=True)

    for i in range(1, len(cards)):
        if suits[i] != suits[i - 1]:
            return False

    return cards


def straight(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    for i in range(1, len(cards)):
        if cards[i] != cards[i - 1] + 1:
            return False

    return sum(cards)


def three_of_a_kind(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    first_3 = cards[0] == cards[1] == cards[2]
    middle_3 = cards[1] == cards[2] == cards[3]
    last_3 = cards[2] == cards[3] == cards[4]

    if first_3:
        return (cards[0], cards[4], cards[3])

    if middle_3:
        return (cards[1], cards[4], cards[0])

    if last_3:
        return (cards[2], cards[1], cards[0])

    return False


def two_pairs(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    pair_first = cards[0] == cards[1]
    pair_mid_l = cards[1] == cards[2]
    pair_mid_r = cards[2] == cards[3]
    pair_last = cards[3] == cards[4]

    if pair_first and pair_mid_r:
        return (cards[2], cards[0], cards[4])

    if pair_first and pair_last:
        return (cards[4], cards[0], cards[2])

    if pair_mid_l and pair_last:
        return (cards[4], cards[1], cards[0])

    return False


def one_pair(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    pair_1 = cards[0] == cards[1]
    pair_2 = cards[1] == cards[2]
    pair_3 = cards[2] == cards[3]
    pair_4 = cards[3] == cards[4]

    if pair_1:
        return (cards[0], cards[4], cards[3], cards[2])

    if pair_2:
        return (cards[1], cards[4], cards[3], cards[0])

    if pair_3:
        return (cards[2], cards[4], cards[1], cards[0])

    if pair_4:
        return (cards[3], cards[2], cards[1], cards[0])

    return False


def high_card(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort(reverse=True)

    return cards


# --------------------------------------------------------------
# hand is a pair: (cards, suits)

all_suits = ['D', 'S', 'H', 'C']
Figurant = ['A', 'K', 'Q', 'J']
Blotkarz = [2, 3, 4, 5, 6, 7, 8, 9, 10]


def gen_Figurants_hand():
    cards = []
    suits = []
    for _ in range(5):
        cards.append(random.randint(0, 3))
        suits.append(random.randint(0, 3))

    for i in range(5):
        cards[i] = Figurant[cards[i]]
        suits[i] = all_suits[suits[i]]

    return (cards, suits)


def gen_Blotkarz_hand():
    cards = []
    suits = []
    for _ in range(5):
        cards.append(random.randint(0, len(Blotkarz) - 1))
        suits.append(random.randint(0, 3))

    for i in range(5):
        cards[i] = Blotkarz[cards[i]]
        suits[i] = all_suits[suits[i]]

    return (cards, suits)

# --------------------------------------------------------------


def lets_play_a_game():
    # returns (0,0) if draw, (1,0) if Figurant won or (0,1) if Blotkarz won
    Figurant_hand = gen_Figurants_hand()
    Blotkarz_hand = gen_Blotkarz_hand()

    hand_rankings = [straight_flush, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pairs, one_pair, high_card]

    for ranking in hand_rankings:
        fig = ranking(Figurant_hand)
        blt = ranking(Blotkarz_hand)

        if fig is False and blt is not False:
            return (0, 1)

        if fig is not False and blt is False:
            return (1, 0)

        if fig is not False and blt is not False:
            return (1, 0)


# test_hand = ([2, 3, 4, 5, 6], ['D', 'D', 'D', 'D', 'D'])
# print('straight_flush test: ', straight_flush(test_hand))
# print('Karty figuranta: ', gen_Figurants_hand())
# print('Karty Blotkarza: ', gen_Blotkarz_hand())


number_of_games = 10000
figur, blotk = 0, 0
for _ in range(number_of_games):
    result = lets_play_a_game()
    figur += result[0]
    blotk += result[1]

print(f'After {number_of_games} games, \nFigurant won: {figur} games, Blotkarz: {blotk}\n')
print(f'Probability of Blotkarz winning is {blotk / number_of_games * 100}%\n')
