import random
import numpy as np

def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    ans = []
    for x in tekst.split():
        if len(x) <= dl_slowa:
            ans.append(x)

    if len(ans) > liczba_slow:
        x = np.random.permutation(len(ans))
        for i in range(len(ans) - liczba_slow):
            ans[x[i]] = ''
            
    ans = list(filter(None, ans))
    return ans

def pierwiastek(n):
    s, i = 0, 1
    while s < n:
        s += 2 * i - 1
        i += 1
    return i - 1


def kompresja(tekst):
    ans = ''
    no = 1
    for i in range(len(tekst) - 1):
        if tekst[i + 1] == tekst[i] and i < len(tekst) - 2:
            no += 1
        else:
            if no > 1:
                ans += str(no) + tekst[i]
            else:
                ans += tekst[i]
            no = 1

    return ans

def dekompresja(tekst):
    ans = ''
    no = ''
    for i in range(len(tekst)):
        if tekst[i].isdigit():
            no += tekst[i]
        else:
            if no:
                ans += tekst[i] * int(no)
            else:
                ans += tekst[i]
            no = ''

    return ans

if __name__ == "__main__":
    tekst = "Podział peryklinalny inicjałów wrzecionowatych \
    kambium charakteryzuje się ścianą podziałową inicjowaną \
    w płaszczyźnie maksymalnej."
    print(uprosc_zdanie(tekst,10, 5))


    print(pierwiastek(10000))


    tekst = 'aaaabbgeeee'
    print(f'{tekst} -> {kompresja(tekst)}')
    print(f'{kompresja(tekst)} -> {dekompresja(kompresja(tekst))}')