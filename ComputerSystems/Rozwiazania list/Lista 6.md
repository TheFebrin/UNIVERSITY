
# Lista zadań nr 6



### Zadanie 1
Poniżej podano zawartość pliku main.c:
```c=
1 #include "stdio.h"
2
3 static int global = 15210;
4
5 static void set_global(int val) {
6     global = val;
7 }

10 int main(void) {
11     printf("before: %d\n", global);
12     set_global(15213);
13     printf("after: %d\n", global);
14     return 0;
15 }
```
Polecenie gcc main.c -o main jest równoważne ciągowi poleceń:
cpp -o main_p.c main.c; 
gcc -S main_p.c; 
as -o main.o main_p.s; 
gcc -o main main.o.


- Jaka jest rola poszczególnych poleceń w tym ciągu?
cpp -o preprocessor pliku wejściowego
gcc -S zamienia plik otrzymanego z preprocessora w plik assemblerowy
as -o kompiluje plik assemblerowy do pliku binarnego
gcc -o tworzy plik wykonywalny

- Skąd pochodzi kod, który znalazł się w pliku main_p.c?
Jest to kod wygenerowany przez C preprocessor (cpp), preprocessor odpowiada <span>m.</span>in. za rozwiajanie makr, i obsługę dyrektyw.
(Makro to zestaw instrukcji umieszczanych w kodzie są jednak interpretowane nie przez kompilator ale przez preprocesor. Dyrektywa- zaczyna się #. Preprocesor jest „pomocnikiem” kompilatora, zajmuje się on np. wstawianiem treści plików nagłówkowych do plików z kodem za pomocą instrukcji #include.)

- Co zawiera plik main_p.s. Zauważ etykiety odpowiadające zmiennej global i obydwu funkcjom. W jaki sposób przyporządkować etykiecie jej typ?
main_p.s zawiera 'zassemblerowany' kod pliku main.c. Typ etykiety znajduje się tuż nad nią:
![](https://i.imgur.com/hiyQOkH.png)



- Poleceniem objdump -t wyświetl tablicę symboli pliku main.o. Jakie położenie wg. tej tablicy mają symbole global i set_global?
![](https://i.imgur.com/cqcJelr.png)

- Poleceniem objdump -h wyświetl informacje o sekcjach w pliku main.o. Dlaczego adres sekcji .text i .data to 0? Jakie są adresy tych sekcji w pliku wykonywalnym main?
VMA - Virtual Memory Address
LMA - Load Memory Address

![](https://i.imgur.com/EMZJhBl.png)

W main.exe:
![](https://i.imgur.com/db15JnQ.png)


Wytłumaczenie:
![](https://i.imgur.com/YuS32iD.png)

### Zadanie 2

Używamy polecenia readelf -t -s swap.o wyświetlajac tablice symboli:

Name | Address | Bind | Size | Section Index | Section Name
--- | --- | --- | --- | --- | ---
bufp1  |     0   |  LOCAL |  8 |  4  | bss
bufp0   |    0   |  GLOBAL | 8  | 5  | data.rel
intvalue  |  0   |  GLOBAL | 4  | 3  | data
count.1798 | 0x8   |  LOCAL  | 4  | 4  | bss
incr       | 0   |  LOCAL |  22 | 1  | text
swap      |  0x16 | GLOBAL | 77 | 1  | text

**.strtab** - tablica stringów, przechowuje nazwy symboli, ma tyle elementów ile tablica symboli
**.shstrtab** - tablica stringów, przechowuje nazwy sekcji, każda sekcja ma swój nagłówek zwierający index tablicy shstrtabx

### Zadanie 3

#### Rozważmy program skompilowany z opcją -Og składający się z dwóch plików źródłowych:
```c=
/* foo.c */
void p2(void);

int main() {
    p2();
    return 0;
}
```
```c=
/* bar.c */
#include <stdio.h>

char main;

void p2() {
    printf("0x%x\n", main);
}
```
#### Po uruchomieniu program drukuje pewien ciąg znaków i kończy działanie bez zgłoszenia błędu. Czemu tak się dzieje? Skąd pochodzi wydrukowana wartość? Zauważ, że zmienna main w pliku bar.c jest niezainicjowana. Co by się stało, gdybyśmy w funkcji p2 przypisali wartość pod zmienną main? Co by się zmieniło gdybyśmy w pliku bar.c zainicjowali zmienną main w miejscu jej definicji? Odpowiedzi uzasadnij posługując się narzędziem objdump.

Wynik objdump:
![](https://media.discordapp.net/attachments/689526193849892867/700667661843169300/unknown.png)

Program nie zgłasza błędów, ponieważ zarówno `p2`, jak i `main` ma jedną silną oraz jedną słabą deklarację, więc wybierane są silne z nich.
Program wypisuje `0x55`. Ta wartość to pierwszy bajt `main` z foo. 
Jak inicjujemy `main` to się nie kompiluje, bo 'multiple definition of main'. 
Jak w `p2` wpiszemy np. `main = 'a'`, to program skompiluje się, jednak próba wykonania spowoduje naruszenie ochrony pamięci.


### Zadanie 4

Które wiersze w kodzie z zadania drugiego będą wymagać dodania wpisu do tablicy relokacji?

*Wskazówka: Zastanów się jakie dodatkowe informacje należy umieścić w plikach relokowalnych, by umieć powiązać miejsca wywołania procedur z położeniem procedury w skonsolidowanym pliku wykonywalnym. Mogą przydać się opcje -d oraz -d -r narzędzia objdump.*

![](https://media.discordapp.net/attachments/689526193849892867/701131660028018808/unknown.png?width=806&height=671)

![](https://cdn.discordapp.com/attachments/689526193849892867/701139463086014564/unknown.png)

Musimy widzieć, gdzie w pamięci znajduje się buf, bufp0, aby można się było do nich odnosić wewnątrz funkcji swap. Dodatkowo musimy wiedzieć gdzie znajduje się static int count, żeby móc go inkrementować 

```cpp=
extern int buf[];

int *bufp0 = &buf[0];       // <-
static int *bufp1;
int intvalue = 0x77;

static void incr() {
    static int count = 0;
    count++;                // <- 
}

void swap() {
    int temp;
    incr();                 // <-
    bufp1 = &buf[1];        // <-
    temp = *bufp0;          // <-
    *bufp0 = *bufp1;        // <-
    *bufp1 = temp;
}
```

### Zadanie 5

Wpis w tablicy symboli dla zmiennej`buf`w pliku`swap.o`wskazuje, że zmienna ta znajduje sięw sekcji`UNDEF`. Zmodyfikuj deklarację zmiennej`buf`w pliku`swap.c`tak, by wpis w tablicy symboli dla`buf`wskazywał na`COMMON`. Jaka jest rola tych wpisów w procesie tworzenia pliku wykonywalnego przez linker?

```c=1
int buf[1];
```
`COMMON` - Niezainicjalizowane dane, które nie są jeszcze zaalokowane.
`UNDEF` - Zmienne typu `extern`


### Zadanie 6
```c
/* bar.c */       | /* foo.c */
int bar = 42;     | long foo = 19;
short dead[15];   | char code[17];
```
```
objdump -h foo.o
> .data: size = 0x8       (bo jest jeden long)
> .bss:  size = 0x11 = 17 (bo jest 17*sizeof(char))

objdump -h bar.o
> .data: size = 0x4       (bo jest jeden int)
> .bss:  size = 0x1e = 30 (bo jest 15*sizeof(short)) 

Pozycje symboli względem początków odpowiednich sekcji: wszędzie 0.
W każdej sekcji jest jeden symbol - czyli idzie na początek.
```

-fno-common: niezainicjalizowane zmienne umieszczane są w sekcji .bss a nie oznaczane jako COMMON


**Mapa konsolidacji:**  
Zawiera informacje o tym jak konsolidować.
- gdzie pliki obiektowe i symbole są w pamięci
- jak alokować symbole COMMON
- info z różnych #include'ów

Generowanie:  
ld -Map output.map -r bar.o foo.o  


**Częściowa konsolidacja (partial linking):**  
Generuje wyjście, które może być wejściem dla linkera do kolejnej iteracji.  
Linker bez opcji -r wypisze warning, że nie ma symbolu \_start.
Linkuje się pliki po kolei, pamiętając informacje i mapę konsolidacji.  
Dzięki temu można rozwiązywać problemy takie, że w jednym pliku jest tylko deklaracja funkcji,  
a w drugim jej definicja.  



**Czym się różnią pliki merge-1.o od merge-2.o?**  
Tym, że w jednym najpierw bierzemy plik foo.o, a potem bar.o, a w drugim na odwrót.  
Różni się to więc kolejnością symboli (a więc i offsetami) w pliku wynikowym w odpowiednich sekcjach.

MERGE-MAP-1
```

.data           0x0000000000000000        0xc
 *(.data)
 .data          0x0000000000000000        0x8 foo.o
                0x0000000000000000                foo
 .data          0x0000000000000008        0x4 bar.o
                0x0000000000000008                bar

.data1
 *(.data1)

.bss            0x0000000000000000       0x3e
 *(.bss)
 .bss           0x0000000000000000       0x11 foo.o
                0x0000000000000000                code
 *fill*         0x0000000000000011        0xf 
 .bss           0x0000000000000020       0x1e bar.o
                0x0000000000000020                dead
 *(COMMON)
```
MERGE-MAP-2
```
.data           0x0000000000000000       0x10
 *(.data)
 .data          0x0000000000000000        0x4 bar.o
                0x0000000000000000                bar
 *fill*         0x0000000000000004        0x4 
 .data          0x0000000000000008        0x8 foo.o
                0x0000000000000008                foo

.data1
 *(.data1)

.bss            0x0000000000000000       0x31
 *(.bss)
 .bss           0x0000000000000000       0x1e bar.o
                0x0000000000000000                dead
 *fill*         0x000000000000001e        0x2 
 .bss           0x0000000000000020       0x11 foo.o
                0x0000000000000020                code
 *(COMMON)
```


### Zadanie 7

:C

### Zadanie 8

1.
```
ar -t /usr/lib/x86_64-linux-gnu/libc.a | wc -l
1690
ar -t /usr/lib/x86_64-linux-gnu/libm.a | wc -l
ar: /usr/lib/x86_64-linux-gnu/libm.a: Nieznany format pliku (dlaczego?)
```
2.
flaga -g sprawia, że plik wykonywalny zawiera dodatkowe symbole dla debuggera

3.

```readelf -d /usr/bin/python```

```
Dynamic section at offset 0x301370 contains 32 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libpthread.so.0]
 0x0000000000000001 (NEEDED)             Shared library: [libdl.so.2]
 0x0000000000000001 (NEEDED)             Shared library: [libutil.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libz.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]

```