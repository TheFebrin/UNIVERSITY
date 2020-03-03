from collections import deque

WORDS = set()
open('valid_output.txt', 'w').close()  # clearing answer file
longest_word = 0

# opening file with all words and creating big set of words
with open('words.txt') as f:
    for line in f:
        WORDS.add(line.replace('\n', ''))
        longest_word = max(longest_word, len(line))

# reading input file
INPUT = []
in_file = 'in.txt'
max_test = 'pan_tadeusz.txt'

with open(max_test) as f:
    for line in f:
        INPUT.append(line.replace('\n', ''))

# here we keep all valid sentences with added separators
ANSWERS = []


def valid_sequence(k, text):
    # True if text[1...k] is a valid sequence of words
    # False otherwise
    if text[:k] in WORDS:
        return True

    for j in reversed(range(1, k)):
        if text[:j] in WORDS and text[j:k] in WORDS:
            return True

    return False


def find_sentences(text):
    valid_seq_arr = [False for _ in range(len(text))]
    word_beg_candidate = [[] for _ in range(len(text))]
    act_length = [[] for _ in range(len(text))]

    for k in range(1, len(text) + 1):
        if text[:k] in WORDS:
            valid_seq_arr[k - 1] = True
            word_beg_candidate[k - 1].append(0)
            act_length[k - 1].append(k ** 2)

        for j in range(k):
            if valid_seq_arr[j] and text[j + 1:k] in WORDS:
                valid_seq_arr[k - 1] = True
                word_beg_candidate[k - 1].append(j)
                act_length[k - 1].append((k - j - 1) ** 2)

    # debug for dp, dp[k] is beg of word that ends on k-pos
    # for i in range(len(text)):
    #     print(i, text[i], valid_seq_arr[i], word_beg_candidate[i], act_length[i])

    # dp counting sentence with biggest sum of squares
    answer = [0 for _ in range(len(text))]
    beginning = [-1 for _ in range(len(text))]

    # dp
    for i in reversed(range(1, len(text))):
        for j in range(len(word_beg_candidate[i])):
            act_beg = word_beg_candidate[i][j]

            if act_length[i][j] + answer[i] >= answer[act_beg]:
                answer[act_beg] = act_length[i][j] + answer[i]
                beginning[act_beg] = i

    # for i in reversed(range(len(text))):
    #     print(i, answer[i], beginning[i])

    final_sentence = []
    final_sentence.append(text[:beginning[0] + 1])
    start = beginning[0]

    # going back in dp constructing sentence
    while start > 0:
        final_sentence.append(text[start + 1: beginning[start] + 1])
        start = beginning[start]

    # sometimes when first word is single letter it s joined with secon word
    if not final_sentence[0] in WORDS:
        final_sentence = [final_sentence[0][0]] + final_sentence
        final_sentence[1] = final_sentence[1][1:]

    # print(*final_sentence)
    f = open('valid_output.txt', 'a')
    f.write(' '.join(final_sentence) + '\n')
    f.close()


def solve():
    for line in INPUT:
        find_sentences(line)


# find_sentences(INPUT[3])
solve()
