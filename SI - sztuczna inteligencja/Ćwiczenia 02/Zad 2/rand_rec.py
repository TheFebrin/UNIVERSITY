import random

WORDS = set()
open('zad2_output.txt', 'w').close()  # clearing answer file
longest_word = 0

# opening file with all words and creating big set of words
with open('words.txt') as f:
    for line in f:
        WORDS.add(line.replace('\n', ''))
        longest_word = max(longest_word, len(line))

# reading input file
INPUT = []
in_file = 'in.txt'

with open(in_file) as f:
    for line in f:
        INPUT.append(line.replace('\n', ''))

# here we keep all valid sentences with added separators
ANSWERS = []


def find_sentences(text, ptr, act_sen):

    if len(text) == 0:
        ANSWERS.append(act_sen[1:])
        return

    if text[:ptr] in WORDS:
        find_sentences(text[ptr:], 0, act_sen + ' ' + text[:ptr])

    if ptr < len(text):
        find_sentences(text, ptr + 1, act_sen)
    else:
        return


def solve():
    for line in INPUT:
        find_sentences(line, 0, '')


solve()

f = open('zad2_output.txt', 'a')
for sentence in ANSWERS:
    # print(sentence)
    f.write(sentence + '\n')
f.close()


number_of_sentences = len(ANSWERS)
print(ANSWERS[random.randint(0, number_of_sentences - 1)])
