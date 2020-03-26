# Ćwiczenia 1

* 302052
* Dawid Dieu

## Zadanie 1
Dla każdego z podanych poniżej adresów IP w notacji CIDR określ, czy jest to adres sieci, adres rozgłoszeniowy czy też adres komputera. W każdym przypadku wyznacz odpowiadający mu adres sieci, rozgłoszeniowy i jakiś adres IP innego komputera w tej samej sieci.

1. `10.1.2.3/8` -> ADRES KOMPUTERA
    - Adres sieci: 10.0.0.0/8
    - Adres rozgłoszneiowy: 10.255.255.255/8
    - Przykładowy adres IP komputera: 10.42.42.42/8
2. `156.17.0.0/16` -> ADRES SIECI
    - Adres sieci: 156.17.0.0/16
    - Adres rozgłoszneiowy: 156.17.255.255/16
    - Przykładowy adres IP komputera: 156.17.42.42/16
3. `99.99.99.99/27` -> ADRES KOMPUTERA
    - Adres sieci: 99.99.99.96/27
    - Adres rozgłoszneiowy: 99.99.99.127/27
    - Przykładowy adres IP komputera: 99.99.99.113/27
4. `156.17.64.4/30` -> ADRES SIECI
    - Adres sieci: 156.17.64.4/30
    - Adres rozgłoszneiowy: 156.17.64.7/30
    - Przykładowy adres IP komputera: 156.17.64.5/30
5. `123.123.123.123/32 ` -> /32 czyli musi to być pojedyńczy host, nie sieć

## Zadanie 2
Podziel sieć `10.10.0.0/16` na 5 rozłącznych podsieci, tak aby każdy z adresów IP z sieci `10.10.0.0/16` był w jednej z tych 5 podsieci. Jak zmieniła się liczba adresów IP możliwych do użycia przy adresowaniu komputerów? Jaki jest minimalny rozmiar podsieci, który możesz uzyskać w ten sposób?

Chcę dostać sieć, która będzie miała minimalny rozmiar.
Czyli dzielę całość na 2, potem uzyskane połówki na 2 i tak dalej...

1. Mamy **10.10**.0.0, dzielimy:
- **10.10.0**0000000.00000000 = 10.10.0.0/17
- **10.10.1**0000000.00000000 = 10.10.128.0/17
2. **10.10.0**0000000.00000000 dzielimy:
- **10.10.00**000000.00000000 = 10.10.0.0/18
- **10.10.01**000000.00000000 = 10.10.64.0/18
3. **10.10.00**000000.00000000 dzielimy:
- **10.10.000**00000.00000000 = 10.10.0.0/19
- **10.10.001**00000.00000000 = 10.10.32.0/19
4. **10.10.000**00000.00000000 dzielimy:
- **10.10.0000**0000.00000000 = 10.10.0.0/20
- **10.10.0001**0000.00000000 = 10.10.16.0/20

Otrzymane podsieci to:

- 10.10.0.0/20
- 10.10.16.0/20
- 10.10.32.0/19
- 10.10.64.0/18
- 10.10.128.0/17

Minimalny adres podsieci: $2^{32-20}-2=2^{12}-2$



## Zadanie 3
Tablica routingu zawiera następujące wpisy (podsieć → dokąd wysłać):

    • 0.0.0.0/0 → do routera A
    • 10.0.0.0/23 → do routera B
    • 10.0.2.0/24 → do routera B
    • 10.0.3.0/24 → do routera B
    • 10.0.1.0/24 → do routera C
    • 10.0.0.128/25 → do routera B
    • 10.0.1.8/29 → do routera B
    • 10.0.1.16/29 → do routera B
    • 10.0.1.24/29 → do routera B

**Napisz równoważną tablicę routingu zawierającą jak najmniej wpisów.**

- 0.0.0.0/0 → do routera A
- 10.0.0.0/22 → do routera B
- 10.0.1.0/24 → do routera C
- 10.0.1.0/27→ do routera B
- 10.0.1.0/29 → do routera C

## Zadanie 4
Wykonaj powyższe zadanie dla tablicy.

    • 0.0.0.0/0 → do routera A
    • 10.0.0.0/8 → do routera B
    • 10.3.0.0/24 → do routera C
    • 10.3.0.32/27 → do routera B
    • 10.3.0.64/27 → do routera B
    • 10.3.0.96/27 → do routera B

- 0.0.0.0/0 → do routera A
- 10.0.0.0/8 → do routera B
- 10.3.0.0/27 → do routera C
- 10.3.0.128/25 → do routera C

## Zadanie 5
Jak uporządkować wpisy w tablicy routingu, żeby zasada najlepszego dopasowania odpowiadała wyborowi „pierwszy pasujący” (tj. przeglądaniu tablicy od początku do końca aż do momentu napotkania dowolnej pasującej reguły)? Odpowiedź uzasadnij formalnie.

>Ogólnie dopasowujemy po najdłuższym pasującym prefixie.
Zatem wystarczy posortować po prefixie od tych najdłuższych.

## Zadanie 6
W podanej niżej sieci tablice routingu budowane są za pomocą algorytmu wektora odległości. Pokaż (krok po kroku), jak będzie się to odbywać. W ilu krokach zostanie osiągnięty stan stabilny?

> Stan stabilny to taki, w którym kolejne wysłania wektorów nie powodują aktualizacji.

 ![](https://i.imgur.com/WSBp2GH.png)


 1. Tablica sąsiedztwa.

 |  - |  A  |  B  |  C  |  D  |  E  |  F  |  S  |
 |  - |  -  |  -  |  -  |  -  |  -  |  -  |  -  |
 |do A|  -  |  1  |     |     |     |     |  1  |
 |do B|  1  |  -  |  1  |     |     |     |     |
 |do C|     |  1  |  -  |     |  1  |  1  |  1  |
 |do D|     |     |     |  -  |  1  |     |     |
 |do E|     |     |  1  |  1  |  -  |  1  |     |
 |do F|     |     |  1  |     |  1  |  -  |     |
 |do S|  1  |  1  |     |     |     |     |  -  |

 2. Znajdujemy takie drogi X->Y że znamy X->Z i Z->Y.

 |  - |   A   |   B   |   C   |   D   |   E   |   F   |   S   |
 |  - |   -   |   -   |   -   |   -   |   -   |   -   |   -   |
 |do A|   -   |   1   |2 via B|       |       |       |   1   |
 |do B|   1   |   -   |   1   |       |2 via C|2 via C|2 via A|
 |do C|2 via B|   1   |   -   |2 via E|   1   |   1   |   1   |
 |do D|       |       |2 via E|   -   |   1   |2 via E|       |
 |do E|       |2 via C|   1   |   1   |   -   |   1   |2 via C|
 |do F|       |2 via C|   1   |2 via E|   1   |   -   |2 via C|
 |do S|   1   |   1   |2 via B|       |       |       |   -   |

3. ...

|  - |   A   |   B   |   C   |   D   |   E   |   F   |   S   |
|  - |   -   |   -   |   -   |   -   |   -   |   -   |   -   |
|do A|   -   |   1   |2 via B|       |3 via C|3 via C|   1   |
|do B|   1   |   -   |   1   |3 via E|2 via C|2 via C|2 via A|
|do C|2 via B|   1   |   -   |2 via E|   1   |   1   |   1   |
|do D|       |3 via C|2 via E|   -   |   1   |2 via E|3 via E|
|do E|3 via B|2 via C|   1   |   1   |   -   |   1   |2 via C|
|do F|3 via B|2 via C|   1   |2 via E|   1   |   -   |2 via C|
|do S|   1   |   1   |2 via B|       |3 via C|3 via C|   -   |

4. Stan stabilny

|  - |   A   |   B   |   C   |   D   |   E   |   F   |   S   |
|  - |   -   |   -   |   -   |   -   |   -   |   -   |   -   |
|do A|   -   |   1   |2 via B|4 via E|3 via C|3 via C|   1   |
|do B|   1   |   -   |   1   |3 via E|2 via C|2 via C|2 via A|
|do C|2 via B|   1   |   -   |2 via E|   1   |   1   |   1   |
|do D|4 via B|3 via C|2 via E|   -   |   1   |2 via E|3 via E|
|do E|3 via B|2 via C|   1   |   1   |   -   |   1   |2 via C|
|do F|3 via B|2 via C|   1   |2 via E|   1   |   -   |2 via C|
|do S|   1   |   1   |2 via B|4 via C|3 via C|3 via C|   -   |

<div style="page-break-after: always;"></div>

## Zadanie 7
Załóżmy, że w powyższej sieci tablice routingu zostały już zbudowane. Co będzie się działo, jeśli zostanie dodane połączenie między routerami A i D?

> W macierzy sąsiedztwa dodajemy 1 w (A, do D) i (D, do A).

1.

|  - |    A    |    B    |    C    |    D    |    E    |    F    |    S    |
|  - |    -    |    -    |    -    |    -    |    -    |    -    |    -    |
|do A|    -    |    1    | 2 via B |  **1**  | 3 via C | 3 via C |    1    |
|do B|    1    |    -    |    1    | 3 via E | 2 via C | 2 via C | 2 via A |
|do C| 2 via B |    1    |    -    | 2 via E |    1    |    1    |    1    |
|do D|  **1**  | 3 via C | 2 via E |    -    |    1    | 2 via E | 3 via E |
|do E| 3 via B | 2 via C |    1    |    1    |    -    |    1    | 2 via C |
|do F| 3 via B | 2 via C |    1    | 2 via E |    1    |    -    | 2 via C |
|do S|    1    |    1    | 2 via B | 4 via C | 3 via C | 3 via C |    -    |

2. Stan stabilny


|  - |      A     |      B     |      C      |     D      |      E      |      F      |      S    |
|  - |      -     |      -     |      -      |     -      |      -      |      -      |      -    |
|do A|      -     |      1     |   2 via B   |     1      |   3 via C   |   3 via C   |      1    |
|do B|      1     |      -     |      1      |**2 via A**|   2 via C   |   2 via C   |   2 via A |
|do C|   2 via B  |      1     |      -      |  2 via E   |      1      |      1      |      1    |
|do D|      1     |   3 via C  |   2 via E   |     -      |      1      |   2 via E   |   3 via E |
|do E|**2 via D**|   2 via C  |      1      |     1      |      -      |      1      |   2 via C |
|do F| 3 via B |   2 via C  |      1      |  2 via E   |      1      |      -      |   2 via C |
|do S|      1     |      1     |   2 via B   |**2 via A**|   3 via C   |   3 via C   |      -    |
