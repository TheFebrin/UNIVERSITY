# run both programs
# import zad2
# import rand_sent

RANDOM = []
VALID = []
TADEK = []

with open('panTadeuszPoprawny_out.txt') as f:
    for line in f:
        TADEK.append(line.strip())

with open('random_output.txt') as f:
    for line in f:
        RANDOM.append(line.strip())

with open('valid_output.txt') as f:
    for line in f:
        VALID.append(line.strip())


all_lines = len(RANDOM)
diff = 0
for i in range(all_lines):
    if RANDOM[i] != TADEK[i]:
        diff += 1

print('Random with original')
print((all_lines - diff) / all_lines * 100, ' % match.\n')

diff = 0
for i in range(all_lines):
    if VALID[i] != TADEK[i]:
        diff += 1

print('Max squares with original')
print((all_lines - diff) / all_lines * 100, ' % match.\n')


diff = 0
for i in range(all_lines):
    if VALID[i] != RANDOM[i]:
        diff += 1

print('Random with max squares')
print((all_lines - diff) / all_lines * 100, ' % match.\n')
