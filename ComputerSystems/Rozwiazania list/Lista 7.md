# Lista zadań nr 7

### Zadanie 1
Na podstawie rozdziału §7.12 podręcznika „Computer Systems: A Programmer’s Perspective” opisz proces **leniwego wiązania** (ang. lazy binding) symboli i odpowiedz na następujące pytania:
• Czym charakteryzuje się **kod relokowalny** (ang. Position Independent Code)?
• Do czego służą sekcje «.plt» i «.got» – jakie dane są tam przechowywane?
• Czemu sekcja «.got» jest modyfikowalna, a sekcje kodu i «.plt» są tylko do odczytu?
• Co znajduje się w sekcji «.dynamic»?
Zaprezentuj leniwe wiązanie na podstawie programu:
``` c=
/* lazy.c */
#include <stdio.h>

int main(void) {
    puts("first time");
    puts("second time");
    return 0;
}
```
skompilowanego poleceniem gcc -Os -Wall -ggdb -o lazy lazy.c. Uruchom go pod kontrolą debuggera GDB, ustaw punkty wstrzymań (ang. breakpoint) na linię 4 i 5. Po czym wykonując krokowo program(stepi) pokaż, że gdy procesor skacze do adresu procedury «puts» zapisanego w «.got» – za pierwszym wywołaniem jest tam przechowywany inny adres niż za drugim.

*Wskazówka: Wykorzystaj rysunek 7.19. Dobrze jest zainstalować sobie nakładkę na debugger GDB dashboard1 lub GDB TUI.*

**Rozwiązanie:**
- Leniwe wiązanie: proces w którym rozwiązywanie symboli jest odwlekane w czasie, aż dany symbol zostanie użyty. O ile funkcje mogą być wiązane na żadanie, tak odniesienia do danych już nie. Leniwe wiązanie jest możliwe, dzięki sprawnej interakcji pomiędzy dwoma strukturami danych: GOT i PLT.
- Kod relokowalny: Kod który nie jest przywiązany do konkretnego miejsca w pamięci. Więc może być załadowany i wywoływany pod każdym adresem bez bycia modyfikowanym przez linker.
- GOT (Global Offset Table) zawiera adresy funkcji dynamicznie linkowanych, ale jego pierwsze 3 elementy są specjalne, jest to adres sekcji .dynamic, informacje dla linkera oraz punkt wejścia do linkera. Początkowo funkcje w .got nie są mapowane na ich właśćiwy kod - dzieje się tak dopiero po ich pierwszym wywołaniu. Dlatego .got jest modyfikowalny.
- PLT (Procedure Linkage Table) ma wpisy dla każdej funkcji w pliku relokowalnym oraz umożliwia zamiane jej adresu na adres faktyczny. Pierwszy element PLT też jest specjalny. 
- .dynamic: (z dokumentacji oracle): ![](https://i.imgur.com/kp5PVFd.png)
![](https://i.imgur.com/5dkdoFy.png)
![](https://i.imgur.com/aBN04Sz.png)

Jak działa leniwe wiązanie i interakcja GOT I PLT:
- Mając jakąś procedurę w pliku relokowalnym i wywołując ją pierwszy raz, np addvec wskaźnik instrukcji znajdzie się na pierwszej instrukcji PLT[2], ponieważ to ten wpis odpowiada za addvec. Ta intrukcja to bezwarunkowy skok do GOT[4], gdzie aktualnie znajduje się adres drugiej instrukcji z PLT[2], więc GOT "cofa nas" do PLT. Ta instrukcja to push ID dla addvec na stos. Następnie skaczemy do PLT[0], która pushuje na stos kolejne informacje do identyfikacji (GOT[1]) oraz skacze do linkera (to, gdzie on jest zapisane jest w GOT[2]). Mając na stosie te 2 informacje linker jest w stanie obliczyć adres addvec. Żeby nie powtarzać tego wszystkiego za każdym wywołaniem addvec, nadpisujemy GOT[4] adresem addvec.
  Jeśli wywołamy addvec po raz drugi ponownie zostaniemy przekierowani do pierwszej intrukcji PLT[2], czyli do skoku do GOT[4], ale tym razem nie będzie tam adresu, który wróci nas do PLT[2], ale będzie tam adres addvec. 

Teraz debugger:
![](https://i.imgur.com/RqHBb8E.png)

![](https://i.imgur.com/qyL5PQ2.png)

### Zadanie 2
Rozważmy program składający się z dwóch plików źródłowych:
``` cpp=
/* str-a.c */
#include <stdio.h>

char *somestr(void);

int main(void) {
    char *s = somestr();
    s[5] = ’\0’;
    puts(s);
    return 0;
}
```
```cpp=
/* str-b.c */
char *somestr(void) {
    return "Hello, world!";
}
```
Po uruchomieniu program kończy się z błędem dostępu do pamięci. Dlaczego? Gdzie została umieszczona stała znakowa "Hello, world!"? Popraw ten program tak, by się poprawnie zakończył. Gdzie został umieszczony ciąg znaków po poprawce? Nie wolno modyfikować sygnatury procedury «somestr» i pliku «str-a.c», ani korzystać z dodatkowych procedur.

Napisa "Hello world" trafił do sekcji rodata (read only data), ponieważ nie było przypisany do żadnej zmiennej, a jedynie zwracany. W linii 8 pliku str-a.c chcemy zmodyfikować ten string, co powoduje błąd dostępu do pamięci.

![](https://i.imgur.com/Dif2lvJ.png)


Jak poprawić program?
Zmieniamy plik str-b.c w następujący sposób:
 
```cpp=
static char aux[] = "Hello, world!";
char *somestr(void) {
    return aux;
}
```

Dzięki temu ciąg znaków zostanie umieszczony w sekcji data i będziemy mogli go edytować.

![](https://i.imgur.com/LBtbTZB.png)

![](https://i.imgur.com/vYIny9G.png)

![](https://i.imgur.com/yLijMA6.png)



### Zadanie 3
Korzystając z **dyrektyw asemblera** opisanych w GNU as: Assembler Directives stwórz plik źródłowy (z rozszerzeniem .s) w którym
1. zdefiniujesz globalną funkcję foobar,
2. zdefiniujesz lokalną strukturę podaną niżej:
```c=
static const struct {
char a[3]; int b; long c; float pi;
}
baz = { "abc", 42, -3, 1.4142 };
```
3. zarezerwujesz miejsce dla tablicy long array[100]?

Pamiętaj, że dla każdego zdefiniowanego symbolu należy uzupełnić odpowiednio tablicę .symtab o typ symbolu i rozmiar danych, do których odnosi się symbol. Z pliku źródłowego stwórz plik relokowalny. Analizując go przekonaj się o poprawności rozwiązania.

*Wskazówka Ktoś, a raczej coś może stworzyć rozwiązanie za Ciebie, a Ty musisz je tylko zrozumieć*

**Dyrektywa Assemblera** - wiadomość do assemblera, przekazująca assemblerowi coś, czego potrzebuje, aby wykonać proces assemblerowania.Nie jest częścią samego programu, nie jest konwertowana na kod maszynowy.

1:
```asm=
// ex3.s
.globl foobar
.type foobar, @function
// kod foobar
.size foobar, .-foobar
```
2:
```asm=
// ex3.s
.section .rodata
.align 16        
.type baz, @object
.size baz, 24
baz:
.ascii "abc"
.zero 1 // zero to padding
.long 42
.quad -3
.long 1068827777 // taka reprezentacja danego floata, dunno
// moze tez byc .float
.zero 4
```
3:
```
// ex3.s
// kompilator wygeneruje:
.comm array, 800, <offset> (u mnie wychodzilo zawsze 32?)
// ale mozna tez tak:
array: .fill 800
```

![](https://cdn.discordapp.com/attachments/690922931139903519/704303571285573652/unknown.png)
Gdzie xs to array 

### Zadanie 4
**Jakie konstrukcje językowe w C są blokadami optymalizacji (ang. optimization blockers)? Porównaj funkcje combine1 i combine4 ze slajdów i wyjaśnij, dlaczego wydajniejsza wersja musiała zostać stworzona ręcznie.**

```c=
void combine1(vec_ptr v, data_t *dest)
{
	long int i;
	*dest = IDENT;
	for (i = 0; i < vec_length(v); i++) 
	{
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}
```
```c=
void combine4(vec_ptr v, data_t *dest)
{
	long i;
	long length = vec_length(v);
	data_t *d = get_vec_start(v);
	data_t t = IDENT;
	for (i = 0; i < length; i++)
		t = t OP d[i];
	*dest = t;
}
```
Dokonane zmiany:
1. liczymy wielokrotnie vec_length(v) -> liczymy raz vec_length(v), a następnie odwołujemy się do obliczonej wartości
2. liczymy wielokrotnie get_vec_element(v, i, &val) -> ustawiamy wskaźnik na początek wektora i następnie iterujemy się po kolejnych jego elementach
3. odwołujemy się wielokrotnie do zmiennej *dest -> tworzymy tymczasową zmienną t i na koniec podstawiamy wynik pod *dest

**Blokada optymalizacji** - aspekt programu, który może poważnie ograniczyć możliwości generowania zoptymalizowanego kodu przez kompilator.

Kompilator nie jest w stanie ocenić warunków, w jakich funkcja może być użyta, i jakie mogą być intencje programisty.
Kompilatory są zazwyczaj bardzo ostrożne w dokonywaniu transformacji w kodzie, które zmieniają miejsce lub liczbę wywołań procedury. Nie mogą wiarygodnie wykryć, czy funkcja będzie miała skutki uboczne, i zakładają, że może.

### Zadanie 5
![](https://i.imgur.com/JBuBaev.jpg)

**Procesor superskalarny** posiada możliwość wykonywania kilku instrukcji jednocześnie

**Spekulatywne wykonywanie instrukcji** - wykonywanie instrukcji znajdujących się już po skoku warunkowym, co do którego jeszcze nie wiadomo, czy nastąpi, a więc czy (formalnie) kolejne instrukcje zostaną kiedykolwiek wykonane. Ostatecznie wyniki uzyskane z wyprzedzeniem zostaną albo uwzględnione, albo odrzucone – w zależności od tego czy skok zostanie wykonany zgodnie z wynikiem mechanizmu predykcji skoków, czy też nie

Przykład (*z wikipedii*):
```
    a := 0
adres 100:
    a := a + 1
    c := c - 1
    ...
    jeśli a < 10 wtedy skok_do_adresu_100
    jeśli c = 20 wtedy skok_do_adresu_200
adres 120:
    b := 0
    ...
adres 200:
    c := 0
```
W powyższym przykładzie, gdy mechanizm predykcji skoków określi, że jest duże prawdopodobieństwo wykonania skoku do adresu 200, to do potoku wykonawczego procesora zostaną wstawione instrukcje od adresu 200, a nie od adresu 120. Jeśli jednak w rzeczywistej realizacji programu okaże się, że skok do adresu 200 nie nastąpi (wartość c jest różna od 20), to potok zostaje wyczyszczony, a tym samym wyniki tego fragmentu kodu anulowane, i ładowane są do niego instrukcje od adresu 120. 

**Poszczególne jednostki funkcjonalne procesora działają w sposób potokowy** - działają w taki sposób, aby każda z jednostek wykonywała część pracy związanej z wykonaniem rozkazu. Jednostki te są połączone sekwencyjnie – w potok *(pipe)* – i wykonują pracę równocześnie, pobierając dane od poprzedniego elementu w sekwencji. W każdej z tych grup rozkaz jest na innym stadium wykonania. Można to porównać do taśmy produkcyjnej.

Przykład z wykładu:
![](https://i.imgur.com/kqqKABq.jpg)

![](https://i.imgur.com/n2I8TI0.jpg)

### Zadanie 6
Rozpatrujemy procesor o charakterystyce podanej w tabeli 5.12 podręcznika „Computer Systems: A Programmer’s Perspective”. Zdefiniuj miarę wydajności CPE (ang. cycles per element/operation), następnie wyjaśnij pojęcie granicy opóźnienia (ang. latency bound) oraz granicy przepustowości (ang. throughput bound) procesora. Skąd biorą się wartości w tabelce na stronie 560 (502?)?

![](https://scontent-waw1-1.xx.fbcdn.net/v/t1.15752-9/94645003_441345946720551_1123523011811475456_n.png?_nc_cat=108&_nc_sid=b96e70&_nc_ohc=IGKpoYBiXeUAX9veyHA&_nc_ht=scontent-waw1-1.xx&oh=d2caea8a081ebeda33bffe578e9e070b&oe=5ECBD30B)

Definicje:
* **CPE** [cycles per operation]: To miara wydajności dla programów operujących na wektorach albo listach. Mówi ona jak dużo cykli było potrzebne na wykonanie programu operującego na liście o danej długości (help us understand the loop performance of an iterative program at a detailed level)
* Granica opóźnienia (**latency bound**): Jest osiągnięta gdy mamy serię operacji, które muszą być wykonywane jedna po drugiej, gdyż wynik każdej z nich jest wymagany do rozpoczęcia kolejnej operacji. Ta granica może ograniczać wydajność programu, gdy zależności danych w kodzie ograniczają zdolność procesora do wykorzystywania równoległości obliczeń na poziomie instrukcji.
* Granica przepustowości (**throughput bound**): jest to surowa moc obliczeniowa jednostek funkcjonalnych procesora. Jest to ostateczna granica wydajności programu.

```
wersja angielska z książki

Although the detailed design of a modern microprocessor is well beyond 
the scope of this book, having a general idea of the principles by 
which they operate suffices to understand how they achieve 
instruction-level parallelism. 
We will find that two different lower  bounds characterize the maximum 
performance of a program. 
The latency  bound is encountered when a series of operations must be 
performed in strict sequence, because the result of one operation is 
required before the next one can begin. This bound can limit program 
performance when the data dependencies in the code limit the ability 
of the processor to exploit instruction level parallelism. 
The throughput bound characterizes the raw computing capacity of the 
processor’s functional units. This bound becomes the ultimate limit on 
program performance.
```

![](https://scontent-waw1-1.xx.fbcdn.net/v/t1.15752-9/95143884_2677613855682323_1398141962292297728_n.png?_nc_cat=107&_nc_sid=b96e70&_nc_ohc=uLfxswsF-ToAX-U8dxN&_nc_ht=scontent-waw1-1.xx&oh=a30090728871ea2621f365d4a331c312&oe=5ECD81BB)

Granica opóźnienia (**latency bound**) podaje minimalną wartośc **CPE** dla dowolnej funkcji, która musi przeprowadzić operacje w ściśle określonej kolejności. 
Granica przepustowości (**throughput bound**) daje minimalne ograniczenie dla **CPE** w oparciu o maksymalne tempo, z jakim jednostki funkcjonalne mogą wytwarzać wyniki.

Przykład: Ponieważ istnieje tylko jeden mnożnik, a jego issue time wynosi 1 cykl zegara, procesor nie jest w stanie uzyskać wydajności większej niż jedno mnożenie na cykl zegara. 
Procesor ma 3 jednostki funkcjonalne zdolne do wykonania dodawania liczb całkowitych, dlatego w tabeli podany jest czas wykonania jednej takiej operacji jako 0.33. Niestety potrzeba odczytu elementów z pamięci tworzy dodatkową granicę przepustowości dla CPE wynoszącą 1.00.

issue time - minimalna liczba cykli zegara między dwiema operacjami tego samego typu

```
wersja angielska z książki

The latency bound gives a minimum value for the CPE for any function that 
must perform the combining operation in a strict sequence. The throughput 
bound gives a minimum bound for the CPE based on the maximum rate at which 
the functional units can produce results. 

For example, since there is only one multiplier, and it has an issue 
time of 1 clock cycle, the processor cannot possibly sustain a rate of 
more than one multiplication per clock cycle.We noted earlier that the 
processor has three functional units capable of performing integer 
addition, and so we listed the issue time for this operation as 0.33. 
Unfortunately, the need to read elements from memory creates an 
additional throughput bound for the CPE of 1.00 for the combining 
functions.

The issue time, meaning the minimum number of clock cycles between
two successive operations of the same type.
```


### Zadanie 7
Z czego wynika wysoka wydajność funkcji `combine6` (tabelka 5.21, str. 573)? Jak zoptymalizować ten kod by dojść do granicy przepustowości procesora?

```c
void combine6(vec_ptr v, data_t *dest) {
    long int i;
    long int length = vec_length(v);
    long int limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc0 = IDENT;
    data_t acc1 = IDENT;
    
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
        acc0 = acc0 OP data[i];       // acc0 i acc1 nie są
        acc1 = acc1 OP data[i+1];     // zależne od siebie
    }
    
    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc0 = acc0 OP data[i];
    }
    *dest = acc0 OP acc1;
}
```
Wyodrębnienie `vec_length(v)` poza warunek sprawdzenia pętli for pozwala wykonać tę procedurę tylko raz. Proces optymalizacji nie zrobi tego na własną rękę, ponieważ nie będzie miał wiedzy o efektach ubocznych danej procedury.

Dzięki wykorzystaniu _loop unrollingu_, dwa niezależne od siebie akumulatory _acc0_ i _acc1_ mogą być obliczane równolegle, maksymalizując zyski z wykorzystania potokowania jednostek funkcjonalnych procesora.

![](https://i.imgur.com/iDmVjNt.png)

### Zadanie 8
```
1 talerz
1 głowica
400 tys ścieżek na powierzchnię
2500 sektorów na ścieżkę
7200 obrotów na minutę
czas wyszukiwania: 1ms -> przeskok o 50 tys ścieżek
```
1. Średni czas wyszukiwania? (czas, zanim głowica ustawi się na ściezkę, na której jest szukany sektor)
  
Czyli mamy **gdzieś** głowicę i chcemy ją przesunąć. Jakie mamy sytuacje?


| Głowica na | Czas do 0 | Czas do 50k | Czas do 100k | Czas do 150k |
| ---------- | --------- | ----------- | ------------ | ------------ |
|     0      |     0ms   |     1ms     |      2ms     |      3ms     |
|    50k     |     1ms   |     0ms     |      1ms     |      2ms     |
|    100k    |     2ms   |     1ms     |      0ms     |      1ms     |
itd  
  
Ta tabelka to tylko przybliżenie.  
Trzeba by zrobić wartość oczekiwaną  
  
W przybliżeniu jest to n/3, gdzie n to najwieksza odległość, czyli:  
Tseek = 8ms/3 = 2.67ms  

2. Średni czas opóźnienia obrotowego? (czas, aż głowica wejdzie na pierwszy bit)  
Głowica kręci się tylko w jedną stronę, więc tutaj średnią będzie połowa czasu całego obrotu  
Tlatency = 1/2 * 1/RPMs * 60s/1min = 1/2 * 1/7200 * 60 = 0,004s = 4ms  

3. Czas transferu sektora? (ile czasu trwa czytanie bitów z sektora)  
Trzeba przelecieć cały sektor.  
Ttransfer = 1/RPM * 1/avg(#sector/track) * 60s/1min = 1/7200 * 1/2500 * 60/1 = 0,003ms  

4. Całkowity średni czas obsługi żądania?  
Znajdź ścieżkę, dojedź do pierwszego bitu, odczytaj
Tseek + Tlatency + Ttransfer = ~7ms


### Zadanie 9
Rozważmy dysk o następujących parametrach: 
* 360 obrotów na minutę, 
* 512 bajtów na sektor,
* 96 sektorów na ścieżkę,
* 110 ścieżek na powierzchnię.

Procesor czyta z dysku całe sektory. Dysk sygnalizuje dostępność danych zgłaszając przerwanie na każdy przeczytany bajt. 
Jaki procent czasu procesora będzie zużywała obsługa wejścia-wyjścia, jeśli wykonanie procedury przerwania zajmuje 2.5µs? Należy zignorować czas wyszukiwania ścieżki i sektora.

![](https://i.imgur.com/FohXR3q.png)
* Czas transferu:
$T_{avg\ transfer} = \frac{1}{96 \frac{sektory}{ścieżka}} * \frac{1}{360 RPM} \approx 0.00002893518min \approx 1.736 ms$

* Czas przerwań:
$512\frac{bajty}{sektor} * 2.5µs = 1.28ms$

* Jaki procent czasu będzie zajmowała obsługa wejścia/wyjścia:
$\frac{\text{czas przerwań}}{\text{czas transferu}} = \frac{1.28ms}{1.736ms} *100 = 73.7\%$

* Do systemu dodajemy kontroler DMA. Przerwanie będzie generowane tylko raz po wczytaniu sektora do pamięci. Jak zmieniła się zajętość procesora?
$\frac{\text{czas przerwań}}{\text{czas transferu}} = \frac{0.0025ms}{1.736ms} *100 = 0.144\%$

> Disk controller reads the sector and performs a direct memory access (DMA) transfer into main memory.
> When the DMA transfer completes, the disk controller notifies the CPU with an interrupt (i.e., asserts a special “interrupt” pin on the CPU).


### Zadanie 10
**W przeważającej większości systemów implementujących moduły DMA, procesor ma niższy  priorytet dostępu do pamięci głównej niż moduły DMA. Dlaczego?**


DMA (direct memory access) - moduł dający gwarancję wykonywania transferów. Moduły DMA zazwyczaj mają wyższy priorytet dostępu do pamięci ogólnej, gdyż nie mają wystarczającej pamięci podręcznej, aby zapisywać dane. Procesor z kolei może sobie te dane zapisać.

Przykładem może być karta sieciowa, która wymaga regularnej możliwości transferu danych.

Dzięki temu modułowi procesor nie musi pośredniczyć w dostępie do pamięci.

DMA ma za zadanie odciążyć procesor główny od przesyłania danych (np. z urządzenia wejściowego do pamięci). Procesor może w tym czasie zająć się innymi działaniami, wykonując kod programu pobrany uprzednio z pamięci RAM do pamięci podręcznej. 