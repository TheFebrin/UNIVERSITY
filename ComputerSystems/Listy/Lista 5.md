# Syk Lista 05

![](https://i.imgur.com/vy72xqe.png)


## Zadanie 1 ✅
#### Zdefiniuj pojęcie **wyrównania danych** w pamięci (ang.data alignment). Dlaczego dane typów prostych  (np.short,int,double)  powinny  być  w  pamięci  odpowiednio  wyrównane?  Jaki  związek  z  wyrównywaniem  danych  mają **wypełnienia** (ang.padding)  w  danych  typu  strukturalnego.  Odpowiadając  na powyższe pytanie podaj przykład struktury, której rozmiar w bajtach (wyliczony przez operator sizeof) jest większy niż suma rozmiaru pól składowych. Czemu służy **wypełnienie wewnętrzne** (ang.internal padding) a czemu **wypełnienie zewnętrzne** (ang.external padding)?

Dziejsze procesory wykonują operacje czytania i pisania po pamięci najbardziej efektywnie, gdy dane są 'wyrównane naturalnie', czyli gdy adres danej znajduje się na wielokrotności jej rozmiaru.

Wyrównanie danych oznacza rozmieszczenie danych w pamięci w taki sposob, aby każda z nich znajdowała się na adresie o wielokrotności jej rozmiaru.

Wypełnienie to włożenie pustych danych między elementy tak, aby każdy element był wyrównany.

Przykład struktury, która waży więcej niż jej pola:
```c=
typedef struct {  //adres musi być wielokrotnościa rozmaiur
    bool x;
    int y;
} s;

// sizeof(s) == 8
```


Wypełnienie wewnętrzne służy do wyrównania elementów wewnątrz struktury, a wypełnienie zewnętrzne do wyrównania całej struktury (wypełnienie po ostatnim elemencie) względem największego elementu wewnątrz niej. Po to, żeby np. w tablicy struktur adres każdego pola dalej był wielokrotnością odpowiedniego k. 

## Zadanie 2 ✅
#### Dana jest funkcja o sygnaturze «int16_t you(int8_t index)» i fragmencie kodu podanym poniżej. Funkcja ta została skompilowana z flagą -O0, a jej kod asemblerowy również jest podany. Nieznana jest natomiast funkcja «int16_t set_secret(void)». Jaki argument należy podać wywołując you, by odkryć wartość sekretu?

```c=
int16_t you(int8_t index) {
    struct {
        int16_t tbl[5];
        int8_t tmp;
        int16_t secret;
    } str;        // definiujesz czym jest ten struct i sobie tworzysz jedna instancje jego

    str.secret = set_secret();
    ...
    return str.tbl[index];
}
```
```c=
you: pushq %rbp
     movq %rsp, %rbp
     subq $24, %rsp
     movl %edi, %eax
     movb %al, -20(%rbp) //index -> rbp-20
     call set_secret
     movw %ax, -2(%rbp)
     ...
     movsbl -20(%rbp), %eax
     cltq
     movzwl -14(%rbp,%rax,2), %eax
     leave
     ret
```

**Rozwiązanie**: index = 6
|co|offset od tbl|
|-|-|
|tbl[0]|0|
|tbl[1]|2|
|tbl[2]|4|
|tbl[3]|6|
|tbl[4]|8|
|tmp|10| 
|padding| 11|
|secret|12|

Sekret jest zapisany pod rbp-2, stąd mamy równanie
`rbp - 14 + rax * 2 = rbp - 2`,
stąd rax=6.


## Zadanie 3 ✅
#### Przeczytaj poniższy kod w języku C i odpowiadający mu kod w asemblerze, a następnie wywnioskuj jakie są wartości stałych «A» i «B».

```c=
typedef struct {
  int32_t x[A][B]; 
  int64_t y; //184
} str1;

typedef struct {
  int8_t array[B]; //0
  int32_t t; // 8, wiemy z 1 linijki => 5<=B<8
  int16_t s[A];
  int64_t u; //32
} str2;

void set_val(str1 *p, str2 *q) {
  int64_t v1 = q->t;
  int64_t v2 = q->u;
  p->y = v1 + v2;
}
```

```c=
set_val:
    movslq 8(%rsi),%rax //q->t, B*1 + offset do int32 => 5 <= B < 8
    addq 32(%rsi),%rax //q->u, 12 + A * 2 + [0, 6] = 32 => 7 <= A <= 10
    movq %rax,184(%rdi) 
ret
```

|co|offset od początku str2|
|-|-|
|array[]|0|
|t|8|
|s[]|12| 
|u| 32|

$5 ≤ B < 8$, bo `t` leży na 8 bajcie, (dla B <= 4  t byłby na 4 bajcie)

$12 + A*2 + [0, 6] = 32 \rightarrow 7 ≤ A ≤ 10$

`s` zaczyna sie na 12
`u` jest na 32



`y` zaczyna się na 184,
`x` z paddingiem = 184

$4*A*B + [0,4] = 184 \rightarrow 180 ≤ 4*A*B ≤ 184 \rightarrow\\\rightarrow
45 ≤ A*B ≤ 46 \longrightarrow  A=9, B=5$

------------------------------
$7 ≤ A ≤ 10$
$5 ≤ B < 8$
$0 ≤ padding ≤ 4$

$A*B*4 + padding = 184$
$A*B + padding / 4 = 5$
$A=9, B=5, padding = 4$


##### Wskazówka: Deklaracja int32_t x[A][B] powoduje, że x będzie A-elementową tablicą wartości typu int32_t [B]. Pamiętaj o wyrównaniu pól w strukturach. 



## Zadanie 4 ✅
#### Przeczytaj poniższy kod w języku C i odpowiadający mu kod w asemblerze, a następnie wywnioskuj jaka jest wartość stałej «CNT» i jak wygląda definicja struktury «a_struct»

```c=
typedef struct {
    int? idx;
    int64[4] x;
} a_struct; //zajmuje 40 bajtów, z 5 linijki assemblera


typedef struct {
    int32_t first;
    a_struct a[CNT]; //offset 8, wiemy z 6 linjiki assemblera
    int32_t last;
} b_struct;

void test (int64_t i, b_struct *bp) {
    int32_t n = bp->first + bp->last;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n; //w struct_a x[idx] = n
}
```
```c=
test:
    movl   0x120(%rsi),%ecx   // n = bp->last; więc last jest na offset=288
    addl   (%rsi),%ecx        // n = bp->first + n;
    leaq   (%rdi,%rdi,4),%rax // rax = 5 * i
    leaq   (%rsi,%rax,8),%rax // rax = bp + 40 * i
    movq   0x8(%rax),%rdx     // rdx = *(bp + 40 * i + 8) -> bp + 8 to start tablicy ze struct_a -> więc sizeof(struct_a) = 40
    // rdx = idx (wartość idx)
    movslq %ecx,%rcx //ecx moze miec znak wiec musimy wypchnac go na rcx tez
    // rax = ap - 8, rdx = ap
    movq   %rcx,0x10(%rax,%rdx,8) // ap->x[ap->idx] = n
    // rax -> gówno (dokładnie rax = bp + 40 * i)
    // rax + 8 -> idx (na poczatek a_struct)
    // rax + 16 -> tablica w naszym dziwnym struccie
    retq  //kradnie bity
```

> 0x120 = 288

Czyli `last` jest na 288 bajcie.

> 0x8 -> 8
> 0x10 -> 16

|Zmienna |Koniec od początku structa|
|-|-|
|first|4 bajt|
|a[CNT]|4 + CNT * sizeof(struct_a)|
|last|4 + CNT * sizeof(struct_a) + 4|

last  = 4 + CNT * sizeof(struct_a) + 4
288 = 4 + CNT * sizeof(struct_a) + 4
280 = CNT * 40
CNT = 7

-----------------------------


0 - 3: first
4 - ?: padding?
? - ? + size(A) * CNT: a_struct[]
288 - 291: last

Z instrukcji ```leaq   (%rsi,%rax,8),%rax    // rax = bp + 40i```  wiadomo, że size(A) = 40.
Z instrukcji ```movq   0x8(%rax),%rdx        // rdx = bp + 40i + 8``` widać, że padding kończy się w bp+8.
Zatem A*CNT = 288 - 8 = 280, czyli CNT = 280 / 40 = 7.

```
typedef struct {
    long long idx;
    long long x[4]; \\ chyba 
} a_struct;
```


## Zadanie 5 ✅
#### Zdefiniuj semantykę operatora «?:» z językaC. Jakie zastosowanie ma poniższa funkcja.
```c=
#include <stdint.h>

int32_t cread(int32_t *xp) {
    return (xp ? *xp : 0);
}
```
>To to samo co: if(xp)return *xp; else return 0;


#### Używając  serwisu godbolt.org (kompilatorx86-64 gcc 8.2)  sprawdź,  czy  istnieje  taki  poziom  optymalizacji  (-O0, -O1, -O2 lub -O3),  że  wygenerowany  dla cread kod  asemblerowy  nie  używa  instrukcji  skoku. Jeśli nie, to zmodyfikuj funkcję cread tak, by jej tłumaczenie na asembler spełniało powyższy warunek.


##### **Wskazówka**: Dążysz do wygenerowania kodu używającego instrukcji cmov. Końcowej instrukcji ret nie uważamy w tym zadaniu za instrukcję skoku.

Nie istnieje, zawsze mamy skok hophop hops siup.
Sidenote: Podany na liście kod nie działa poprawnie -- xp castowane na boola zawsze daje true. Należy użyć xp == NULL.

```c=
int cread(int *xp) {
    int defaultVal = 0;
    int * yp = &defaultVal;
    int * res = (xp != NULL ? xp : yp); 
    return *res;
}
```

```c=
cread:
        movl    $0, -4(%rsp) //-4(rsp) to miejsce w pamieci bo rsp na jakąś komórkę i odejmuje od niej 4
        leaq    -4(%rsp), %rax // w rax wrzucamy ten wskaźnik co wyżej
        testq   %rdi, %rdi // ZF = 1 tylko jesli %rdi = NULL
        cmove   %rax, %rdi
        movl    (%rdi), %eax
        ret
```
![](https://i.imgur.com/w0HHrqv.png)

Dla kompilacji -O1 nie skacze, mamy warunkowe przeniesienie.



## Zadanie 6 ✅
#### W  języku C struktury  mogą  być  zarówno  argumentami  funkcji,  jak  i  wartościami  zwracanymi przez funkcje. Za pomocą serwisu godbolt.org zapoznaj się z tłumaczeniem do asemblera funkcji przyjmujących  pojedynczy  argument  każdego  z  poniższych  typów  strukturalnych.  Następnie  zapoznaj  się  z  tłumaczeniem funkcji zwracających wartość każdego z tych typów. Jakie reguły dostrzegasz?

```c=
struct first {
    int val1;
};

struct second {
    int val2;
    int val1;
};

struct third {
    int val3;
    int val2;
    int val1;
};

struct fourth {
    int val4;
    int val3;
    int val2;
    int val1;
};

struct fifth {
    short val6;
    short val5;
    int val3;
    int val2;
    int val1;
};

struct sixth {
    int val7;
    int val4;
    int val3;
    int val2;
    int val1;
};

struct seventh {
    int val8[10000];
    int val4;
    int val3;
    int val2;
    int val1;
};
```

#### Czy przekazywanie/zwracanie dużych struktur funkcjom jest dobrym pomysłem?


Testowane na
```
struct <<x>> foo(struct <<x>> a) {
    return a;
}
```
First i Second dają spodziewany krótki kilkulinijkowy wynik (wyjęcie elementu ze stosu i wrzucenie go do raxa). Przy flagach -O(1/2/3) zostaje to skrócone do dwulinijkowca
![](https://i.imgur.com/7GeO9J5.png)


Third, Fourth, Fifth do samego przeniesienia argumentów wymagają już po dwa rejestry.

![](https://i.imgur.com/axlyBRW.png)
![](https://i.imgur.com/Rcaow6Z.png)
![](https://i.imgur.com/oq5Tqdn.png)

Sixth ma już za dużo danych wg. kompilatora, więc będa one przenoszone za pomocą stosu zamiast rejestrów rax i rdx.

![](https://i.imgur.com/wfqTTIp.png)


Seventh już w ogóle nie radzi sobie sam ze struktura i zaprzęga do pomocy memcpy

![](https://i.imgur.com/gyiCVzF.png)


Widać zatem, że im większe struktury, tym bardziej assembler musi pajacować, aby być w stanie je obsłużyć. Jeśli struct jest wystarczająco dużych rozmiarów, to może się on nie zmieścić w pamięci podręcznej L1 i trafi do L2 lub RAMu, co znacząco zmniejszy wydajność operacji. Zatem należy powstrzymywać się przed przekazywaniem / zwracaniem dużych struktur.

"L1 and L2 are levels of cache memory in a computer. If the computer processor can find the data it needs for its next operation in cache memory, it will save time compared to having to get it from random access memory. L1 is "level-1" cache memory, usually built onto the microprocessor chip itself. For example, the Intel MMX microprocessor comes with 32 thousand bytes of L1.

L2 (that is, level-2) cache memory is on a separate chip (possibly on an expansion card) that can be accessed more quickly than the larger "main" memory. A popular L2 cache memory size is 1,024 kilobytes (one megabyte)."


## Zadanie 7 ✅
#### W poniższej funkcji zmienna field jest polem bitowym typu int32_to rozmiarze 4. Jaką wartość wypisze ta funkcja na ekranie i dlaczego? Co się stanie, gdy zmienimy typ pola field na uint32_t? Na obydwa te pytania odpowiedz analizując tłumaczenia tej funkcji na język asemblera.
```cpp=
void set_field(void) {
    struct {
        int32_t field : 4;
    } s;
    s.field = 10;
    printf("Field value is: %d\n", s.field);
}
```

Pole bitowe oznacza, że zamiast całej wartości bierzemy tylko jej n bitów, czyli wartość jest wtedy and-owana z maską bitową skladającą się z n jedynek i interpretowana jako liczba n-bitowa. 

(10 binarnie to 1010)

Dla int32_t: 1010 = -8 + 2 = -6
Dla uint32_t: 1010 = 10
**int32_t field**
![](https://i.imgur.com/QI9EGfr.png)
**uint32_t field**
![](https://i.imgur.com/EQ6fi94.png)


##### **Wskazówka**: Użyj poziomu optymalizacji «-O0». Dla wyższych poziomów optymalizacji kompilator zauważy, że deklaracja zmiennej «s» jest niepotrzebna i obliczy wartość wypisywaną przez «printf» podczas kompilacji.

## Zadanie 8 ✅
Język C dopuszcza  deklaracje  tablic  wielowymiarowych  z  opuszczonym  rozmiarem  pierwszego wymiaru.  Taka  deklaracja  może  wystąpić  w  nagłówku  funkcji,  np.  ```void process(int32_t A[][77],size_t len)```.  Nie  można  natomiast  opuszczać  rozmiarów  innych  wymiarów,  np. ```«void bad(int32_tA[77][], size_t len)```  nie  jest  poprawną  deklaracją.  Wyjaśnij,  dlaczego  tak  jest  odwołując  się  do  sposobu, w jaki kompilator tłumaczy odwołania do tablic z C na asembler.


`A[SIZE1][SIZE2]` oznacza, że mamy SIZE1 segmentów, każdy o długośći SIZE2 (razy rozmiar typu tablicy...). Mając `A[][SIZE]` znamy rozmiar segmentów, więc wiemy o ile bajtów trzeba przesunąc wskaźnik z A do A\[x]\[y]: (x*SIZE+y). Mając A\[SIZE]\[] nie wiadomo o ile należy się przesuwać, bo nie wiadomo jaki rozmiar ma każdy segment.
