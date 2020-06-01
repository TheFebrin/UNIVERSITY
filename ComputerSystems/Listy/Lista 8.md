# Syk, lista 8

![](https://i.imgur.com/4RktVhw.png)
![](https://i.imgur.com/uj8ajak.png)

### Zadanie 1
#### Mamy system z pamięcią operacyjną adresowaną bajtowo. Szerokość szyny adresowej wynosi 12. Pamięć podręczna ma organizację sekcyjno-skojarzeniową o dwuelementowych zbiorach, a blok ma 4 bajty. Dla podanego niżej stanu pamięci podręcznej wyznacz, które bity adresu wyznaczają: offset, indeks, znacznik (ang. tag). Wszystkie wartości numeryczne podano w systemie szesnastkowym.

|Indeks| Znacznik| Valid| B0| B1| B2| B3|
|-|-|-|-|-|-|-|
|0|00|1|40|41|42|43|
|0|83|1|FE|97|CC|D0|
|1|00|1|44|45|46|47|
|1|83|0|-|-|-|-|
|2|00|1|48|49|4A|4B|
|2|40|0|-|-|-|-|
|3|FF|1|9A|C0|03|FF|
|3|00|0|-|-|-|-|

Szyna wygląda następująco:
| Tag | Index  | Offset |
| --- | ------ | ------ |
| 8   | 2      | 2      |


Określ, które z poniższych operacji odczytu wygenerują trafienie i ew. jakie wartości wczytają:
|Adres|Adres w dwójkowym|Index|Offset|Znacznik|Trafienie?|Wartość|
|-|-|-|-|-|-|-|
|832|`10000011 00 10`|0| 2      |83|Tak|CC|
|835|`10000011 01 01`|1| 1      |83|Nie|...|
|FFD|`11111111 11 01` |3| 1      |FF|Tak|Bierzemy B1 = C0|

Pierwsze 8 bitów to znacznik, kolejne 2 bity to indeks, ostatnie 2 bity to offset w bloku.

### Zadanie 2. 
#### Rozważmy pamięć podręczną z mapowaniem bezpośrednim adresowaną bajtowo. Używamy adresów 32-bitowych o następującym formacie: (tag, index, offset) = (addr31...10, addr9...5, addr4...0).
1. Jaki jest rozmiar bloku w 32-bitowych słowach?
2. Ile wierszy ma nasza pamięć podręczna?
3. Jaki jest stosunek liczby bitów składujących dane do liczby bitów składujących metadane?

<details><summary><b>Mapowanie bezpośrednie</b></summary>
(direct mapping) - każdy blok w pamięci głównej jest odwzorowywany na tylko jeden możliwy wiersz pamięci (tj. jeśli blok jest w cache'u to jest tylko w ściśle określonym miejscu)
</details>
<br>

Odp:
1. 5 bitów na offset więc $2^5 = 32$, skoro offset max to 32, to mamy 32 bajty w bloku
2. mapowanie bezpośrednie - 1 znacznik dla indeksu, więc $2^{5}=32$
3. $\frac{32\ wierszy * 32\ bloczki * 8}{32\ wiersze * (5\ index + 22\ znacznik + 1\ valid)} \approx 9.14$

    

### Zadanie 3. 
#### Rozważmy pamięć podręczną z poprzedniego zadania. Mamy następującą sekwencję odwołań do słów pamięci (liczby w systemie dziesiętnym):

<center>
04 16 132 232 160 1024 28 140 3100 180 2180
</center>

#### Załóż, że na początku pamięć podręczna jest pusta. Jak wiele bloków zostało zastąpionych? Jaka jest efektywność pamięci podręcznej (liczba trafień procentowo)? Podaj zawartość pamięci podręcznej po wykonaniu powyższych odwołań – każdy ważny wpis wypisz jako krotkę (tag, index, . . . ). Dla każdego chybienia wskaż, czy jest ono przymusowe (ang. compulsory miss) czy też kolizji na danym adresie (ang. conflict miss).


**Definicje:**
<details><summary><b>Blok zastąpiony</b></summary>
w przypadku chybienia w cache, procesor musi odczytać zawartość potrzebnej komórki z pamięci głównej. Może się jednak zdarzyć, że wszystkie linijki z sekcji pamięci cache, do której blok powinien być skopiowany są już w tym momencie zapełnione ważnymi danymi. Trzeba wtedy określić, zawartość której linijki jest najmniej potrzebna i można zastąpić ją nowym blokiem danych z pamięci głównej
</details>


<details><summary><b>Trafienie</b></summary>
Jeżeli w systemie komputerowym występuje pamięć podręczna, to przy każdym dostępie do adresu w pamięci operacyjnej w celu pobrania rozkazu lub danej, sprzęt procesora przesyła adres najpierw do pamięci podręcznej. W tej pamięci następuje sprawdzenie czy potrzebna informacja jest zapisana w pamięci podręcznej. Jeśli - tak, to mamy do czynienia z tzw. "trafieniem" i potrzebna informacja jest pobierana z pamięci podręcznej.
</details>

![](https://i.imgur.com/QclVjto.png)


<details><summary><b>Chybienie</b></summary>
Jeśli żądanej informacji nie ma w pamięci podręcznej, to mamy do czynienia z tzw. "chybieniem" i potrzebna informacja jest pobierana z pamięci operacyjnej z jednoczesnym wprowadzenie jej kopii do pamięci podręcznej. Informacja do pamięci podręcznej nie jest kopiowana w postaci pojedyńczych słów a w postaci bloków słów o ustalonej wielkości. Razem z blokiem informacji, do pamięci podręcznej jest zawsze wpisywana pewna część adresu, która dotyczy początku bloku. Ta część adresu jest później wykorzystywana przy identyfikacji właściwego bloku przy odczycie informacji.
</details>

![](https://i.imgur.com/HYzM6AV.png)

<details><summary><b>Compulosory miss</b></summary>
Następuje, gdy blok jest wprowadzany po raz pierwszy do pamięci podręcznej.
</details>

<details><summary><b>Conflict miss</b></summary>
Wszystkie tagi są załadowane, żeby załadować do cache musimy coś zastąpić.
</details>


|Adres dziesiętny|(tag, index, offset)|hit or miss(I guess they never miss huh)|
|-|-|-|-|-|
|0|`00 00000 00000`|Compulsory miss|||
|4|`00 00000 00100`|Hit|||
|16|`00 ‭00000 10000`‬|Hit|||
|132|`0‭0 00100 00100‬`|Compulsory miss|||
|232|`0‭0 00111 01000`‬|Compulsory miss|||
|160|`00 00101 00000‬`|Compulsory miss|||
|1024|‭`01 00000 00000`‬|Conflict miss, bo w cachu 0 jest cos z tagiem 0|||
|28|`00 00‭000 11100`‬|Conflict miss, bo przed chwilą tag 0 zastąpiliśmy tagiem 1|||
|140|‭`00 00100 01100`‬|Hit bo załadowaliśmy jak było zapytanie z adresem 132|||
|3100|‭`11 00000 11100`‬|Conflict miss|||
|180|`‭00 00101 10100‬`|Hit, bo załadowane w 160|||
|2180|`‭‭10 00100 00100`‬|Conflict miss, bo w 140 zaladowaliśmy tag 0|||

<br>
Pamięc podręczna po wykonaniu odwołań:

|Index|Tag|
|-|-|
|00000|11|
|00100|10|
|00101|00|
|00111|00|


**Efektywność: $\frac{4}{12} = \frac{1}{3} = 33\%$**



### Zadanie 4. 
#### Powtórz poprzednie zadanie dla następujących organizacji pamięci podręcznej:
1. sekcyjno-skojarzeniowa 3-drożna, bloki długości dwóch słów, liczba bloków 24, polityka wymiany LRU,
2. w pełni asocjacyjna (tag i off), bloki długości słowa, liczba bloków 8, polityka wymiany LRU.


- sekcyjno-skojarzeniowa [...]
    24 bloki / 3-drożna -> 8 sekcji -> 3 bity na index
    3-drożna -> liczba bitów na tag: minimum 2 (ale adres 3100 wymaga 3 bitów)
    bloki długości 2 słów -> więc 64 bajty -> 6 bitów na zapis

    | Tag | Index | Offset |
    | --- | ----- | ------ |
    | 3   | 3     | 6      |

    | Address | Tag | Index | Offset | Result     | Notes                                |
    | ------- | --- | ----- | ------ | ---------- | ------------------------------------ |
    | 0       | 000 | 000   | 000000 | compulsory |
    | 4       | 000 | 000   | 000100 | hit        | (z wpisu 0)                          |
    | 16      | 000 | 000   | 010000 | hit        | (z wpisu 0)                          |
    | 132     | 000 | 010   | 000100 | compulsory |
    | 232     | 000 | 011   | 101000 | compulsory |
    | 160     | 000 | 010   | 100000 | hit        | (z wpisu 132)
    | 1024    | 100 | 000   | 000000 | compulsory | (bo w i=0 dostępne jeszcze 2 tagi)   |
    | 28      | 000 | 000   | 011100 | hit        | (z wpisu 0)                          |
    | 140     | 000 | 010   | 001100 | hit        | (z wpisu 132)                        |
    | 3100    | 110 | 000   | 011100 | compulsory | (bo w i=0 dostępny jeszcze 1 tag)    |
    | 180     | 000 | 010   | 110100 | hit        | (z wpisu 132)                        |
    | 2180    | 100 | 010   | 000100 | compulsory | (bo w i=010 dostępne jeszcze 2 tagi) |

    Efektywność: 6/12
    Zawartość pamięci:

    | Index | Tag_0 | Tag_1 | Tag_2 |
    | ----- | ----- | ----- | ----- |
    | 000   | 000   | 100   | 110   |
    | 010   | 000   | 100   | -     |
    | 011   | 000   | -     | -     |

- w pełni asocjacyjna [...]
    asocjacyjna -> brak indeksów
    bloki długości słowa -> 5 bitów
    najdłuższy adres ma 12 bitów -> tag ma 7 bitów
    Nie znamy rozmiaru pamięci, więc niewiadomo kiedy nadpisywać wpisy
    
    | Tag | Index | Offset |
    | --- | ----- | ------ |
    | 7   | 0     | 5      |
    
    | Address | Tag     | Offset | Result     | Most Recent -> Oldest          |
    | ------- | ------- | ------ | ---------- |-------------------------- |
    | 0       | 0000000 | 00000  | compulsory | t0
    | 4       | 0000000 | 00100  | hit        | t0
    | 16      | 0000000 | 10000  | hit        | t0 
    | 132     | 0000100 | 00100  | compulsory | t100, t0
    | 232     | 0000111 | 01000  | compulsory | t111, t100, t0
    | 160     | 0000101 | 00000  | compulsory | t101, t111, t100, t0
    | 1024    | 0100000 | 00000  | compulsory | t100000, t101, t111, t100, t0
    | 28      | 0000000 | 11100  | hit        | t0, t100000, t101, t111, t100
    | 140     | 0000100 | 01100  | hit        | t100, t0, t100000, t101, t111
    | 3100    | 1100000 | 11100  | compulsory | t1100000, t100, t0, t100000, t101, t111
    | 180     | 0000101 | 10100  | hit        | t101, t1100000, t100, t0, t100000, t111
    | 2180    | 1000100 | 00100  | compulsory | t10000100, t101, t1100000, t100, t0, t100000, t111
    
    Efektywność: 5/12
    
    Zawartość pamięci:

    | Tag      |
    | -------- |
    | 10000100 |
    | 00000101 |
    | 01100000 |
    | 00000100 |
    | 00000000 |
    | 00100000 |
    | 00000111 |

### Zadanie 5. 
#### Rozważamy system z dwupoziomową pamięcią podręczną z polityką zapisu write-back z write- allocate. Dodatkowo zakładamy, że blok o określonym adresie może znajdować się tylko na jednym poziomie pamięci podręcznej (ang. exclusive caches). Przy pomocy drzewa decyzyjnego przedstaw jakie kroki należy wykonać, by obsłużyć chybienie przy zapisie do L1? Nie zapomnij o bicie dirty i o tym, że pamięć podręczna może być całkowicie wypełniona! Zakładamy, że pamięć podręczna pierwszego poziomu nie może komunikować się bezpośrednio z pamięcią operacyjną.


![](https://i.imgur.com/WZ8PvhT.png)

![](https://i.imgur.com/M6fgQJd.png)

![](https://i.imgur.com/DKSZk7f.png)

![](https://i.imgur.com/pMoxUIb.png)

![](https://i.imgur.com/NpplATb.png)


dwupoziomowa pamięć podręczna: L1 i L2
write miss: chcemy napisać na adres, którego nie ma w L1
Korzystamy z write-allocate.
Ładujemy odpowiadający blok z niższego poziomu i aktualizujemy L1.
Korzystamy z write back, będziemy nadpisywać wszystkie poziomy, dopiero gdy wpis będzie usuwany z L1.

Zapisujemy na adres A.
1) Adres A jest w L1:
    aktualizujemy A w L1 i ustawiamy dirty bit na 1
2) Adresu A nie ma w L1:
    - wczytujemy blok z niższego poziomu
    Czy pamięć podręczna jest całkowicie wypełniona?
    Tak: (TODO)
    należy wybrać jakiś blok do napisania (np. zgodnie z polityką LRU),
    następnie jeśli jego dirty bit jest ustawiony, to należy przekazać go do niższych poziomów, aby zaauktualizowały one swoje dane,
    następnie nadpisujemy usunięty blok
    Nie:
    znajdujemy wolny blok i wpisujemy tam zawartość A, ustawiamy dirty bit na 1, usuwamy A z L2


* Jak wygląda obsługa trafień w przypadku write-back? Informacje są zapisywane tylko do bloku w pamięci podręcznej. Zmodyfikowany blok jest zapisywany w pamięci głównej tylko po jego zastąpieniu. Aby zmniejszyć częstotliowść zapisywania bloków po zamianie, stosuje się bit "dirty". Ten bit stanu wskazuje, czy blok jest "zabrudzony" (zmodyfikowany w pamięci podręcznej), czy czysty (niezmodyfikowany). Jeśli jest czysty, blok nie jest zapisywany przy spudłowaniu.




### Zadanie 6. 
#### Wiemy, że im większa pamięć podręczna tym dłuższy czas dostępu do niej. Załóżmy, że dostęp do pamięci głównej trwa 70ns, a dostępy do pamięci stanowią 36% wszystkich instrukcji. Rozważmy system z pamięcią podręczną o następującej strukturze:
#### L1 – 2 KiB, współczynnik chybień 8.0%, czas dostępu 0.66ns (1 cykl procesora);
#### L2 – 1 MiB, współczynnik chybień 0.5%, czas dostępu 5.62ns.
#### Odpowiedz na pytania:

![](https://i.imgur.com/2GLQOlR.png)

1. Jaki jest średni czas dostępu do pamięci dla procesora tylko z cache L1, a jaki dla procesora z L1 i L2?
2. Zakładając, że procesor charakteryzuje się współczynnikiem CPI (ang. cycles per instruction) równym 1.0 (bez wykonywania dostępów do pamięci), oblicz CPI dla procesora tylko z cache L1 i dla procesora z L1 i L2.

Odpowiedzi: (c czyli cykl)
1. * tylko L1:
    0.66ns + 8/100 * 70ns = 6.26ns
    * L1 i L2:
    0.66ns + 8/100 * (5.62ns + 5/1000 * 70ns) = 1.138ns
2. * tylko L1:
    64/100(?) * 1c + 36/100 * 6.26ns * c / (0.66ns) = 4.41c * 64/100(?) 
    * L1 i L2:
    64/100(?) * 1c + 36/100 * 1.138ns * c / (0.66ns) = 1.62c * 64/100(?) 

### Zadanie 7. 
#### Dla czterodrożnej sekcyjno-skojarzeniowej pamięci podręcznej chcemy zaimplementować politykę wymiany LRU. Masz do dyspozycji dodatkowe $log_2(4!)$ bitów na zbiór. Nie można modyfikować zawartości linii w zbiorze, ani zamieniać elementów kolejnością. Jak wyznaczyć kandydata do usunięcia ze zbioru? Jak aktualizować informacje zawarte w dodatkowych bitach przy wykonywaniu dostępów do elementów zbioru?

4-way z LRU, czyli musimy pamiętać z czego najdawniej korzystaliśmy. Mamy na to 5 bitów. Są 4 linie, więc są numerowane 0,1,2,3, więc na zapis 1 lini potrzebujemy 2 bity.

Będziemy to zapisywać na 5 bitach w następujący sposób:
| Najdawniej używny | Prawie najdawniej używany | foo |
| - | - | - |
| 2 bity | 2 bity | 0, jesli pozostałe są w kolejności leksykograficznej, 1 wpp. |

Bloki: 0️⃣ 1️⃣ 2️⃣ 3️⃣
Najdawniej uzywany: 3️⃣
Prawie najdawniej: 0️⃣
jeśli foo = 0: 1, 2
else: 2, 1


0 - najdawniej
1 - prawie najdawniej
2 - przedostatnio
3 - ostatnio

(☞ﾟヮﾟ)☞ ______   ☜(ﾟヮﾟ☜)

1. Najdawniej, czyli 0
0️⃣ 1️⃣ 2️⃣ 3️⃣ ---> 2️⃣ 3️⃣ 1️⃣ 0️⃣
^

2. Prawie najdawniej, czyli 1
0️⃣ 1️⃣ 2️⃣ 3️⃣ ---> 0️⃣ 2️⃣ 3️⃣ 1️⃣
🍆^

3. Przedostatnio, czyli 2
0️⃣ 1️⃣ 2️⃣ 3️⃣ ---> 0️⃣ 1️⃣ 3️⃣ 2️⃣ 
🍆🍆^
foo ^= 1

4. Ostatnio, czyli 3
0️⃣ 1️⃣ 2️⃣ 3️⃣ ---> 0️⃣ 1️⃣ 2️⃣ 3️⃣,
🍆😩🍆^
utopia wyjebongo




Szkic:
Oblicz jakie linie były niedawno używane. 
1) jeśli użyta została wartość ostatnio używana:
    pass
2) jeśli użyta została wartość przedostatnio używana:
    xor ostatniego bitu(czyli foo) i 1
3) jeśli użyta została wartość prawie najdłużej nieużywana:
    - pod tą wartość przypisujemy wartość przedostatnio używaną
    - pod ostatni bit ustawiamy wartość logiczną teraz_użyta < ostatnio_używana
4) jeśli użyta zostawa wartość najdłużej nieużywana:
    - pod tą wartość przypisujemy prawie najdłużej nieużywaną
    - pod wartość prawie najdłużej nieużywaną przypisujemy wartość przedostatnio używaną
    - pod ostatni bit ustawiamy wartość logiczną teraz_użyta < ostatnio_używana



### Zadanie 8. 
#### Dany jest następujący kod oraz założenia co do sposobu jego wykonania.

```cpp=
int x[2][128];
int i;
int sum = 0;

for (i = 0; i < 128; i++) {
    sum += x[0][i] * x[1][i];
}
```
- sizeof(int) = 4
- Tablica x znajduje się w pamięci pod adresem 0x0
- Pamięc podręczna jest początkowo pusta
- Dostępy do pamięci dotyczą jedynie elementów tablicy x. Wszystkie pozostałe zmienne kompilator umieścił w rejestrach. Pamięć podręczna nie przechowuje instrukcji.
#### Oblicz współczynniki chybień przy wykonaniu tego kodu dla każdego z poniższych wariantów
- pamięć podręczna ma 512 bajtów, mapowanie bezpośrednie (jeden blok na wiersz), rozmiar bloku 16 bajtów
- jak powyżej, z tym że rozmiar pamięci podręcznej to 1024 bajtów
- pamięć podręczna ma 512 bajtów, jest dwudrożna, sekcyjno-skojarzeniowa, używa polityki zastępowania LRU, rozmiar bloku to 16 bajtów
W tym ostatnim przypadku, czy zwiększenie rozmiaru pamięci podręcznej pomoże zredukować współczynnik chybień? A zwiększenie rozmiaru bloku?

Odpowiedzi:
- A:
    rozmiar cache: $2^9B$
    offset: $log_2(rozmiar\ bloku) = log_2(16) = 4$
    liczba bloków: $log_2(rozmiar\ cache / rozmiar\ bloku) = log_2(2^9 / 2^4) = 5$
    tag: reszta
    
    | Tag | Index | Offset |
    |-|-|-|
    |długość słowa - 8 | 5 bitów | 4 bity |
    
    | Var | Address | Tag | Index | Offset | Result | Notes |
    | - | -| -| -| -| - | - |
    | x[0][0] | 0   | 0..00 | 00000 | 0000 | compulsory miss |
    | x[1][0] | 512 | 0..01 | 00000 | 0000 | conflict miss | nadpisuje x[0][0] |
    | x[0][1] | 4   | 0..00 | 00000 | 0100 | conflict miss | nadpisuje x[1][0] |
    | x[1][1] | 516 | 0..01 | 00000 | 0100 | conflict miss | nadpisuje x[0][1] |
    |...|...|...|...|...|...|...|
    
    
    Widać zatem, że każde kolejne wywołanie w pętli będzie powodowało chybienie, więc mamy współczynnik chybień = 100%

- B:
    rozmiar cache: 2^10B
    offset: $log_2(rozmiar\ bloku) = log_2(16) = 4$
    liczba bloków: $log_2(2^{10} / 2^4) = 6$
    tag: reszta
    | Tag | Index | Offset |
    |-|-|-|
    | 0 bitów | 6 bitów | 4 bity |
    
    | Var | Address | Index | Offset | Result | Notes |
    | - | -| -| -| - | - |
    | x[0][0] | 0   | 000000 | 0000 | compulsory miss |
    | x[1][0] | 512 | 100000 | 0000 | compulsory miss |
    | x[0][1] | 4   | 000000 | 0100 | hit | wpis x[0][0] |
    | x[1][1] | 516 | 100000 | 0100 | hit | wpis x[1][0] |
    | x[0][2] | 8   | 000000 | 1000 | hit | wpis x[0][0] |
    | x[1][2] | 520 | 100000 | 1000 | hit | wpis x[1][0] |
    | x[0][3] | 12  | 000000 | 1100 | hit | wpis x[0][0] |
    | x[1][2] | 524 | 100000 | 1100 | hit | wpis x[1][0] |
    | x[0][4] | 16  | 000001 | 0000 | compulsory miss |
    | x[1][4] | 528 | 100001 | 0000 | compulsory miss |
    
    Widać, że wpisy x[i][$\frac{j}{4}$] powodują compulsory miss, a następne 3 (x[i][j + {1,2,3}]) to same hity. Zatem współczynnik chybień = 25%
    
- C:
    rozmiar cache: 2^9B
    offset: 4
    liczba bloków: log2(rozmiar cache / (rozmiar bloku * liczba bloków na sekcje )) = log2(2^9 / (2^4 * 2)) = log(2^4) = 4
    tag: reszta
    
    | Tag | Index | Offset |
    |-|-|-|
    | długość słowa - 8 | 4 bity | 4 bity |
    
    | Var | Address | Tag | Index | Offset | Result | Notes |
    | - | -| -| -| -| - | - |
    | x[0][0] | 0   | 0..000 | 0000 | 0000 | compulsory |
    | x[1][0] | 512 | 0..010 | 0000 | 0000 | compulsory | i=0 ma jeszcze jeden wolny tag |
    | x[0][1] | 4   | 0..000 | 0000 | 0100 | hit | wpis x[0][0] |
    | x[1][1] | 516 | 0..010 | 0000 | 0100 | hit | wpis x[1][0] |
    | x[0][2] | 8   | 0..000 | 0000 | 1000 | hit | wpis x[0][0] |
    | x[1][2] | 520 | 0..010 | 0000 | 1000 | hit | wpis x[1][0] |
    | x[0][3] | 12  | 0..000 | 0000 | 1100 | hit | wpis x[0][0] |
    | x[1][3] | 520 | 0..010 | 0000 | 1100 | hit | wpis x[1][0] |
    | x[0][4] | 16  | 0..000 | 0001 | 0000 | compulsory |
    | x[1][4] | 524 | 0..010 | 0001 | 0000 | compulsory | i=1 ma jeszcze jeden wolny tag |
    
    Analogiczna sytuacja jak w B. Współczynnik chybień = 25%. Jeśli zwiększymy rozmiar bloku (offset) to zmiejszy się liczba chybień


{%youtube 8AwVRlXsxlA %}


### Zadanie 9
#### Pracujesz  nad  programem  wyświetlającym  animacje  na  ekranie  o  rozmiarze  640x480  pikseli. Komputer dysponuje 32KB pamięci podręcznej z mapowaniem bezpośrednim, o rozmiarze bloku 8 bajtów. Używasz następujących struktur danych.
```cpp=
struct pixel {
    char r;
    char g;
    char b;
    char a;
};

struct pixel buffer[480][640];
int i, j;
char *cptr;
int *iptr;
```

#### Zakładamy, że sizeof(char) = 1, sizeof(int) = 4, tablica buffer znajduje się w pamięci pod adresem 0x0,  pamięć  podręczna  jest  początkowo  pusta.  Ponadto,  dostępy  do  pamięci  dotyczą  jedynie  elementów tablicy buffer. Wszystkie pozostałe zmienne kompilator umieścił w rejestrach. Pamięć podręczna działa w trybie write-back write-allocate.

#### Jaki jest współczynnik trafień przy wykonaniu poniższego kodu?
```cpp=
for (j = 639; j >= 0; j--) {
    for (i = 479; i >= 0; i--) {
        buffer[i][j].r = 0;
        buffer[i][j].g = 0;
        buffer[i][j].b = 0;
        buffer[i][j].a = 0;
    }
}
```

Rozmiar cache: $2^5 * 2^{10} = 2^{15}B$.
Z treści wiemy, że rozmiar to 32kB, czyli $2^{15}$
Offset: log2(rozmiar\ bloku) = $log_2(8) = 3$
Liczba bloków: $log_2(rozmiar\ cache / rozmiar\ bloku) = log_2 (2^{15} / 2^3) = 12$
Tag: 32 - 3 - 12 = 17
| Tag | Index | Offset |
| --- | ----- | ------ |
| 17  | 12    | 3      |


**Wersja na zajebisty chłopski rozum bez tabelek:**
- bierzesz sobie jakieś b[i][x].r i załóżmy, że nie masz tego w cache -> to sobie ładujesz a jako że offset ma 8 bajtów to możemy załadować tam 8 charów, czyli (b[i][j].r, b[i][j].g, b[i][j].b, b[i][j].a, b[i][j+1].r, b[i][j+1].g, b[i][j+1].b, b[i][j+1].a)
- potem robisz coś z b[i][j].g, b[i][j].b, b[i][j].a ale masz to już w pamięci, więc git i jest `hit`
- robisz j-- a nie masz w cache b[i][nowe j] a tego nigdy nie ładowaliśmy więc miss i robisz to co wyżej
- w 1 kroku nie mamy nic w cache więc jest miss
- widać że zawsze najpierw jest 1 miss a potem 3 hity -> współczynnik chybień = 25%



| Var | Address | Tag | Index | Offset | Result |
| --- | ------- | --- | ----- | ------ | ------ |
| b[479][639].r | 1 228 796‬ | 100101 | 011111111111 | 100 | compulsory
| b[479][639].g | 1 228 797 | 100101 | 011111111111 | 101 | hit
| b[479][639].b | 1 228 798 | 100101 | 011111111111 | 110 | hit 
| b[479][639].a | 1 228 799 | 100101 | 011111111111 | 111 | hit
| b[478][639].r | 1 226 236 | 100101 | 011010111111 | 100 | compulsory
| b[478][639].g | 1 226 237 | 100101 | 011010111111 | 101 | hit
| b[478][639].b | 1 226 238 | 100101 | 011010111111 | 110 | hit 
| b[478][639].a | 1 226 239 | 100101 | 011010111111 | 111 | hit

Skaczemy co 640*4 bitów, czyli adres nie zmieni się na 6 najmniej znaczących  bitach indexu oraz ostatnim bicie offsetu (pierwsze 2 bity offsetu odpowiadają za .r, .g, .b, .a).
Patrząc jedynie na ostatnie 6 bitów indexu mamy tam liczby:
31,26,21,...,1, <- 7 dostępów
60,55,50,...,0, <- 13 dostępów
59,54,49,...,4, <- 13 dostępów
63,58,53,...,3, <- 13 dostępów
62,57,52,...,2, <- 13 dostępów
61,56,51,...,31 <- 6 dostępów po czym się powtarzamy

| Var | Address | Tag | Index | Offset | Result |
| --- | ------- | --- | ----- | ------ | ------ |
| b[415][639].r | 1 064 956 | 100000 | 011111111111 | 100 | conflict
| b[415][639].g | 1 064 956 | 100000 | 011111111111 | 101 | hit
| b[415][639].b | 1 064 956 | 100000 | 011111111111 | 110 | hit 
| b[415][639].a | 1 064 956 | 100000 | 011111111111 | 111 | hit
| b[414][639].r | 1 062 396 | 100000 | 011010111111 | 100 | conflict
| b[414][639].g | 1 062 396 | 100000 | 011010111111 | 101 | hit
| b[414][639].b | 1 062 396 | 100000 | 011010111111 | 110 | hit 
| b[414][639].a | 1 062 396 | 100000 | 011010111111 | 111 | hit

Więc widzimy, że zanim wykorzystamy np. b[479][638].* to nadpiszemy te informacje, stąd współczynnik chybień = 25%


### Zadanie 10
#### Kod  z  poprzedniego  zadania  został  zoptymalizowany  przez  dwóch  programistów.  Wynik  ich pracy znajduje się odpowiednio w lewej i prawej kolumnie poniżej.

```cpp=
char *cptr = (char *) buffer;
while (cptr < (((char *) buffer) + 640 * 480 * 4)) {
    *cptr = 0;
    cptr++;
}
```
```cpp=
int *iptr = (int *)buffer;
while (iptr < ((int *)buffer + 640*480)) {
    *iptr = 0;
    iptr++;
}
```

Czy któryś z tych programów jest wyraźnie lepszy, jeśli idzie o wykorzystanie pamięci podręcznej? Odpowiedź uzasadnij wyliczając odpowiednie współczynniki trafień.

Pierwsza wersja robi 640 * 480 * 4 operacji dostępu do pamięci, z czego 1/8 to missy (w bloku mieści się 8 charów, więc 1/8 to minimalna liczba missów), czyli mamy 153600 missów z 1228800 dostępów.

Druga wersja robi 640 * 480 operacji dostępu do pamięci, z czego 1/2 to liczba missów, czyli mamy 153600 missów z 307200.

W obu wersjach mamy tyle samo dostępów do pamięci głównej a druga wersja wykonuje mniej operacji dzięki czemu powinna działac szybciej.