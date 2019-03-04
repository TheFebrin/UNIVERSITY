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
    if first_4 or last_4:
        return True

    return False


def full_house(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    first_3 = cards[0] == cards[1] == cards[2]
    last_2 = cards[3] == cards[4]

    first_2 = cards[0] == cards[1]
    last_3 = cards[2] == cards[3] == cards[4]

    if first_3 and last_2 or first_2 and last_3:
        return True

    return False


def flush(hand):
    suits = hand[1]
    cards = [card_val[card] for card in hand[0]]
    cards.sort(reverse=True)

    for i in range(1, len(cards)):
        if suits[i] != suits[i - 1]:
            return False

    return True


def straight(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    for i in range(1, len(cards)):
        if cards[i] != cards[i - 1] + 1:
            return False

    return True


def three_of_a_kind(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    first_3 = cards[0] == cards[1] == cards[2]
    middle_3 = cards[1] == cards[2] == cards[3]
    last_3 = cards[2] == cards[3] == cards[4]

    if first_3 or middle_3 or last_3:
        return True

    return False


def two_pairs(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    pair_first = cards[0] == cards[1]
    pair_mid_l = cards[1] == cards[2]
    pair_mid_r = cards[2] == cards[3]
    pair_last = cards[3] == cards[4]

    if pair_first and pair_mid_r or pair_first and pair_last or pair_mid_l and pair_last:
        return True

    return False


def one_pair(hand):
    cards = [card_val[card] for card in hand[0]]
    cards.sort()

    pair_1 = cards[0] == cards[1]
    pair_2 = cards[1] == cards[2]
    pair_3 = cards[2] == cards[3]
    pair_4 = cards[3] == cards[4]

    if pair_1 or pair_2 or pair_3 or pair_4:
        return True

    return False

# --------------------------------------------------------------
# hand is a pair: (cards, suits)


all_suits = {
    'D': 4,
    'S': 4,
    'H': 4,
    'C': 4
}

Figurant = {
    'A': 4,
    'K': 4,
    'Q': 4,
    'J': 4
}

Blotkarz = {
    2: 4,
    3: 4,
    4: 4,
    5: 4,
    6: 4,
    7: 4,
    8: 4,
    9: 4,
    10: 4
}


def gen_Figurants_hand(n):
    cards = []
    suits = []

    while n > 0:
        cards.append(random.choice(list(Figurant)))
        suits.append(random.choice(list(all_suits)))
        n -= 1

    return (cards, suits)


def gen_Blotkarz_hand(n):
    cards = []
    suits = []

    while n > 0:
        cards.append(random.choice(list(Blotkarz)))
        suits.append(random.choice(list(all_suits)))
        n -= 1

    return (cards, suits)

# --------------------------------------------------------------


def lets_play_a_game(hand_size):
    # returns (0,0) if draw, (1,0) if Figurant won or (0,1) if Blotkarz won
    Figurant_hand = gen_Figurants_hand(hand_size)
    Blotkarz_hand = gen_Blotkarz_hand(hand_size)

    hand_rankings = [straight_flush, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pairs, one_pair]

    for ranking in hand_rankings:
        fig = ranking(Figurant_hand)
        blt = ranking(Blotkarz_hand)

        if fig is False and blt:
            return (0, 1)

        if fig and blt is False:
            return (1, 0)

        if fig and blt:
            return (1, 0)


number_of_games = 10000
figur, blotk = 0, 0
hand_size = 5

for _ in range(number_of_games):
    result = lets_play_a_game(hand_size)
    figur += result[0]
    blotk += result[1]

print(f'After {number_of_games} games, \nFigurant won: {figur} games, Blotkarz: {blotk}\n')
print(f'Probability of Blotkarz winning is {blotk / number_of_games * 100}% \n')
