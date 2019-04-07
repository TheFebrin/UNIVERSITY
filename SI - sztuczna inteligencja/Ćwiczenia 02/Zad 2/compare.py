# run both programs
# import zad2
import rand_sent

RANDOM = []
VALID = []

with open('random_output.txt') as f:
    for line in f:
        RANDOM.append(line.strip())

with open('valid_output.txt') as f:
    for line in f:
        VALID.append(line.strip())


all_lines = len(RANDOM)
diff = 0
for i in range(all_lines):
    if RANDOM[i] != VALID[i]:
        diff += 1


print((all_lines - diff) / all_lines * 100, ' % match.')
