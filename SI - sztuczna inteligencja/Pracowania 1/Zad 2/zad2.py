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


def find_sentences(text, ptr_beg, ptr_end, act_sentence, act_len):
    while ptr_end <= len(text):
        if ptr_end - ptr_beg >= longest_word:
            return

        act_word = text[ptr_beg: ptr_end]
        if act_word in WORDS:
            find_sentences(text, ptr_end, ptr_end + 1, act_sentence + ' ' + act_word, act_len + len(act_word))

        ptr_end += 1

    if act_len == len(text):
        ANSWERS.append(act_sentence[1:])


def choose_best_sentence(text):
    ANSWERS.clear()
    find_sentences(text, 0, 1, '', 0)

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
        choose_best_sentence(line)


solve()
print('FINISHED')
