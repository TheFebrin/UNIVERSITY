from collections import deque

WORDS = set()
open('answer.txt', 'w').close()  # clearing answer file
longest_word = 0

# opening file with all words and creating big set of words
with open('words.txt') as f:
    for line in f:
        WORDS.add(line.replace('\n', ''))
        longest_word = max(longest_word, len(line))

# reading input file
INPUT = []
with open('in.txt') as f:
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
    valid_seq_arr = [False for _ in range(len(text) + 42)]
    word_beg_candidate = [[] for _ in range(len(text) + 42)]

    for k in range(1, len(text) + 1):
        if text[:k] in WORDS:
            valid_seq_arr[k - 1] = True
            word_beg_candidate[k - 1].append(0)
            continue

        for j in range(k):
            if valid_seq_arr[j] and text[j + 1:k] in WORDS:
                # print(k, text[:j + 1], text[j + 1:k])
                valid_seq_arr[k - 1] = True
                word_beg_candidate[k - 1].append(j + 1)

    for i in range(len(text)):
        print(i, text[i], valid_seq_arr[i], word_beg_candidate[i])

    Q = deque()
    Q.append((len(text) - 1, ''))

    while len(Q) > 0:
        first = Q.popleft()

        next_beg = []
        for x in word_beg_candidate[first[0]]:
            word = text[x: first[0] + 1]
            if x > 0:
                Q.append((x - 1, first[1] + ' ' + word))
            else:
                print (first[1] + ' ' + word)

    # ANSWERS.append(' '.join(list(reversed(answer))))
    # print(*list(reversed(answer)))


def choose_best_sentence(text):
    ANSWERS.clear()
    find_sentences(text)

    words_sq = 0
    for a in ANSWERS:
        sq = [len(x) ** 2 for x in a.split(' ')]
        words_sq = max(words_sq, sum(sq))

    f = open('answer.txt', 'a')
    for a in ANSWERS:
        sq = [len(x) ** 2 for x in a.split(' ')]
        if sum(sq) == words_sq:
            f.write(a + '\n')
            print(a)


def solve():
    for line in INPUT:
        # choose_best_sentence(line)
        find_sentences(line)


find_sentences(INPUT[0])
# solve()
