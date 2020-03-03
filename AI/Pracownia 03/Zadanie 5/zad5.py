output = open('zad_output.txt', 'w')
INPUT = open('zad_input.txt').readlines()


def B(i, j):
    return 'B_%d_%d' % (i, j)


def domains(bs):
    return [q + ' in 0..1' for q in bs]


def writeln(s):
    output.write(s + '\n')


def storms(raws, cols, triples):
    writeln(':- use_module(library(clpfd)).')

    R = len(raws)
    C = len(cols)

    bs = [B(i, j) for i in range(R) for j in range(C)]

    writeln('solve([' + ', '.join(bs) + ']) :- ')

    # domain in 0..1
    writeln('[' + ', '.join(bs) + '] ins 0..1,')

    # sum in row has to be equal...
    for i, r in enumerate(raws):
        rs = [B(i, j) for j in range(C)]
        writeln('sum([' + ', '.join(rs) + '], #=, ' + str(r) + '), ')

    # sum in column has to be equal...
    for j, c in enumerate(cols):
        cs = [B(i, j) for i in range(R)]
        writeln('sum([' + ', '.join(cs) + '], #=, ' + str(c) + '), ')

    # fill rectangles (and corners) (B + c == 2 <==> A + D == 2)
    for i in range(R - 1):
        for j in range(C - 1):
            a = B(i, j)
            b = B(i, j + 1)
            c = B(i + 1, j)
            d = B(i + 1, j + 1)
            writeln(b + ' + ' + c + ' #= 2 #<==> ' + a + ' + ' + d + ' #= 2, ')

    # (B = 1 => A + C => 1) for column
    for j in range(C):
        for i in range(R - 2):
            a = B(i, j)
            b = B(i + 1, j)
            c = B(i + 2, j)
            writeln(b + ' #= 1 #==> ' + a + ' + ' + c + ' #>= 1, ')

    # (B = 1 => A + C => 1) for row
    for i in range(R):
        for j in range(C - 2):
            a = B(i, j)
            b = B(i, j + 1)
            c = B(i, j + 2)
            writeln(b + ' #= 1 #==> ' + a + ' + ' + c + ' #>= 1, ')

    # assigments
    for x, y, val in triples:
        output.write('%s #= %d, ' % (B(x, y), val))

    writeln('')

    writeln('    labeling([ff], [' + ', '.join(bs) + ']).')
    writeln('')
    writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")


def solve():

    raws = list(map(int, INPUT[0].split()))
    cols = list(map(int, INPUT[1].split()))
    triples = []

    for i in range(2, len(INPUT)):
        if INPUT[i].strip():
            triples.append(list(map(int, INPUT[i].split())))

    storms(raws, cols, triples)


solve()
