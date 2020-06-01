# Lista  9

### Zadanie 1
Opisz różnice między **przerwaniem sprzętowym** (ang. _hardware interrupt_), **błędem** (ang. _fault_) i **pułapką** (ang. _trap_). Dla każdego z tych rodzajów **wyjątków** (ang. _exceptions_) podaj co najmniej trzy przykłady zdarzeń, które je wyzwalają. W jakim scenariuszu błąd nie spowoduje błędu czasu wykonania (przerwania działania) programu?

![](https://i.imgur.com/bOwSGXw.png)

**Przerwanie sprzętowe** (ang. _hardware interrupt_) - zdarzenie wywołane przez zewnętrzne urządzenia. Niepowiązane z aktualnie wywoływaną instrukcją. Z punktu widzenia programu wygląda to tak, jak gdyby błąd nie wystąpił.
- timer systemowy
- informacja o zakończeniu operacji I/O
- nadejście pakietu z sieci

**Błąd** (ang. _fault_) - wyjątki, dla których istnieje możliwość wykonania korekcji. Błąd może być wynikiem błędnej implementacji przez użytkownika. Po obsłużeniu błędu przez _handler_, procesor może powrócić do tej samej instrukcji i ją ponowie wykonać.
- Page Fault (kontynuacja)
- Floating Point Fault - np. dzielenie przez zero (przerwanie)
- Segmentation Fault (kontynuacja, często przerwanie)

**Pułapka** (ang. _trap_) - wyjątki występujące jako efektu uboczny wywołania jakiegoś polecenia (celowo). Po obsłużeniu, kontynuuje od następnej instrukcji.
- syscalle (odwołanie do kernela aby np. odczytać plik, stworzyć nowy proces)
- polecenia programistyczne, np. breakpointy

**Wyjątek** (ang. _exceptions_) - nagła zmiana przepływu wykonywach operacji będąca wywołana zmianą stanu procesora.

![](https://i.imgur.com/ae7DQjH.png)

### Zadanie 2
Opisz mechanizm **obsługi przerwań** bazujący na **wektorze przerwań** (ang. interrupt vector table). Co robi procesor przed pobraniem pierwszej instrukcji procedury obsługi przerwania (ang. interrupt handler) i po natrafieniu na instrukcję powrotu z przerwania? Dlaczego procedura obsługi przerwania powinna być wykonywana w **trybie nadzorcy** i używać odrębnego stosu?



**Przerwania** występują asynchronicznie jako konsekwencja sygnału z urządzeń in/out, które są poza procesorem.  
Przerwania hardwarowe (sprzętowe) są asynchroniczne w znaczeniu, że nie są powodowane przez wykonanie żadnej specjalnej instrukcji.  

**Procedury obsługi wyjątków dla przerwań sprzętowych** są często nazywane **procedurami obsługi przerwań** (ang. *interrupt handlers*).


Zawsze gdy procesor wykryje, że nastąpił event (zdarzenie), wykonuje pośrednie wywołanie procedury (wyjątku), poprzez skok do tablicy nazywanej: *tablicą wyjątków* (ang. exception table) do podprogramu systemu operacyjnego - exception handlera, który jest zaprojektowany specjalnie dla tego typu eventu.


![](https://i.imgur.com/L3mU5Ff.png)
#### Tablica wyjątków
Każdemu możliwego wyjątkowi w systemie przypisany jest unikalny nieujemny numer całkowity wyjątku.  
W czasie uruchamiania systemu (gdy komputer jest zresetowany lub włączany) system operacyjny przydziela i inicjuje tabelę skoków zwaną tabelą wyjątków, tak aby wpis k zawierał adres procedury obsługi wyjątku k.  
W czasie wykonywania (gdy system wykonuje jakiś program) procesor wykrywa wystąpienie zdarzenia i określa odpowiedni numer wyjątku k. Następnie procesor uruchamia wyjątek, wykonując pośrednie wywołanie procedury, poprzez wpis k tabeli wyjątków, do odpowiedniego modułu obsługi.  

![](https://i.imgur.com/WLC1NnK.png)

Gdy aktualna instrukcja zostanie wykonana, procesor zauważa, że interrupt pin osiągnął wysoką wartość, czyta numer wyjątku z magistrali systemowej (system bus) i uruchamiana jest właściwa procedura obsługi przerwań (interrupt handler). Gdy ta się kończy, zwraca kontrolę następnej instrukcji, czyli tej, która zostałaby wykonana gdyby nie wystąpiło przerwanie.  
Efekt jest taki, że program jest dalej wykonywany jak gdyby przerwanie nigdy nie nastąpiło.

#### Wektor przerwań (ang. Interrupt vector table)

![](https://i.imgur.com/sEGQrBa.png)
Tablica wektorów przerwań (IVT) to struktura danych, która wiąże listę programów obsługi przerwań z listą żądań przerwań w tabeli wektorów przerwań.
Każdy wpis w tabeli wektorów przerwań, jest adresem modułu obsługi przerwań (interrupt handler).

#### Co robi procesor przed pobraniem pierwszej instrukcji procedury obsługi przerwania?
Podobnie jak w przypadku wywołania procedury, **procesor wypycha adres zwrotny na stosie przed przejściem do procedury obsługi.** (W przypadku przerwań adresem zwrotnym jest następna instrukcja, czyli taka, która normalnie byłaby wykonywana jako następna, gdyby nie nastąpiło przerwanie.)  
**Procesor wypycha również pewien dodatkowy stan procesora na stos, który będzie niezbędny do ponownego uruchomienia przerwanego programu po powrocie procedury obsługi.**
Jeśli kontrola jest przenoszona z programu użytkownika do jądra, wszystkie te elementy są wypychane na stos jądra, a nie na stos użytkownika.

#### Co robi procesor po natrafieniu na instrukcję powrotu z przerwania?
Gdy sprzęt uruchamia wyjątek, reszta pracy jest wykonywana w oprogramowaniu przez exception handler. Po przetworzeniu zdarzenia przez handler, opcjonalnie powraca do przerwanego programu, wykonując specjalną instrukcję „return from interrupt”, która wysyła odpowiedni stan z powrotem do kontroli procesora i rejestrów danych, przywraca stan do trybu użytkownika (user mode) jeśli wyjątek przerwał program użytkownika, a następnie zwraca kontrolę przerywanemu programowi.


#### Tryby pracy procesora:
Procesor ma dwa tryby pracy: **użytkownika (user mode) i nadzorcy (supervisor mode)**.
W trybie użytkownika wykonywane są programy aplikacyjne, w trybie nadzorcy – kod systemu operacyjnego.
W porównaniu z trybem nadzorcy tryb użytkownika ma ograniczenia w dostępie do zasobów maszyny (niedostępne są krytyczne dla bezpieczeństwa systemu rejestry oraz obszary pamięci), dysponuje też nieco mniejszą listą rozkazów. Zestaw rejestrów nadzorcy i użytkownika jest ten sam z wyjątkiem wskaźnika stosu (są dwa oddzielne rejestry) oraz starszego bajtu rejestru statusu dostępnego tylko w trybie nadzorcy.

![](https://i.imgur.com/CwJuJM7.png)


#### Dlaczego osobny stos?
![](https://i.imgur.com/6EwfEhn.png)

### Zadanie 3
Wzorując się na slajdach do wykładu „Virtual Memory Systems” (strony 10–21) powtórz proces **translacji adresów** i adresowania pamięci podręcznej dla adresów: **0x027c, 0x03a9 i 0x0040** zakładając poniższy stan **TLB**, pamięci podręcznej i **tablicy stron**.

![](https://i.imgur.com/seFzG3G.png)


**Translacja adresów** - sprawdzanie, która strona fizyczna jest mapowana na którą stronę wirtualną. Podczas tłumaczenia adresu wirtualnego na adres fizyczny mamy do czynienia tylko z numerem strony. Istotą procedury jest pobranie numeru strony podanego adresu i sprawdzenie go w tabeli stron, aby znaleźć wskaźnik do adresu fizycznego, do którego dodano przesunięcie adresu wirtualnego, podając rzeczywistą lokalizację w systemie pamięć.

**Translation lookaside buffer, TLB** – to pamięć podręczna, która służy do skrócenia czasu potrzebnego na uzyskanie dostępu do lokalizacji pamięci użytkownika. Jest to część jednostki MMU (memory menagement unit). TLB przechowuje ostatnie translacje pamięci wirtualnej na pamięć fizyczną i można ją nazwać pamięcią podręczną translacji adresów.

**Tablica stron** - struktura danych używana przez system pamięci wirtualnej w systemie operacyjnym komputera do przechowywania mapowania między adresami wirtualnymi a adresami fizycznymi. Valid = 1 wtedy wiemy że strona w pamięci.


Symbole: ![](https://i.imgur.com/qALlE8Z.png)
Adresowanie:
 - 14-bit virtual addresses
 - 12-bit physical address
 - Page size = 64 bytes


Potrzebujemy 6 bitów VPO, ooffsetowych bitów i reszta bitów (6-13 bit = 8 bitów) zostaje na VPN, tak samo potrzebujemy 6 bitów na PPO, a reszta (6-11 bit = 6 bitów) zostaje na PPN.
Nasza tablica ma 16 wejść

**ADRES: 0x027c**
1. Zapisujemy binarnie: 0000 0010 0111 1100, dzielimy na bity VPO i VPN, mamy:
 - VPO: 11 1100 -> 0011 1100 = 0x3c
 - VPN: 0000 0010 01 -> 0000 1001 = 0x09
 - TLBI: 01 -> 0001 = 1
 - TLBT: 000010 -> 0000 0010 = 0x02

![](https://i.imgur.com/7x2N0br.png)

2. Patrzymy na TLB table: szukamy w secie 1 tagu 02
![](https://i.imgur.com/qcChTZj.png)


**Valid = 0 -> TBL hit? N, Page Fault? N, PPN:?**
Mamy TLB miss, więc trzeba zejść z układu i zrobić kosztowny dostęp do pamięci, aby przeczytać page table entry z page table.
Sprawdzamy page table o wartości VPN = 0x09, żeby sprawdzić czy ta strona jest w pamięci, jeśli valid = 1 => tak

![](https://i.imgur.com/Pu5B3JX.png)

stąd prawidłowy PPN = 17

3. Bity offsetu przepisujemy, kodujemy PPN: 0X17 = 0001 0111
![](https://i.imgur.com/orpddCq.png)


Mamy:
 - CO: 0
 - CI: 1111 = 15 = 0xF
 - CT: 0001 0111 = 0x17
4. Patrzymy w cache'u czy mamy hit pod idx = F, tagiem = 17
![](https://i.imgur.com/4a4CMWI.png)
Nie mamy matchującego tagu, mamy cache miss, więc teraz cache musi zażądać przekazania tego adresu fizycznego do pamięci w celu pobrania tego bajtu.

**Adres 0x03a9**
1. Zapisujemy binarnie: 0000 0011 1010 1001, dzielimy na bity VPO i VPN, mamy:
 - VPO: 10 1001 -> 0010 1001 = 0x29
 - VPN: 0000 0011 10 -> 0000 1110 = 0x0e
 - TLBI: 10 = 0x2
 - TLBT: 000011 = 0x03

![](https://i.imgur.com/6svGP0x.png)

2. Patrzymy na TLB table: szukamy w secie 2 tagu 03
![](https://i.imgur.com/6d1XJdX.png)
**Valid = 0 -> TBL hit?: N, Page Fault?: N, PPN:?**
Sprawdzamy page table o wartości VPN= 0x0e, żeby sprawdzić czy ta strona jest w pamięci, jeśli valid = 1 => tak
![](https://i.imgur.com/dqHihxS.png)
PPN: 11

3. Bity offsetu przepisujemy, kodujemy PPN: 11 = 0001 0001 = 010001
![](https://i.imgur.com/IbJkVIN.png)

Mamy:
 - CO: 1
 - CI: 1010 = 10 = 0xa
 - CT: 010001 = 0x11
4. Patrzymy w cache'u czy mamy hit pod idx = a, tagiem = 11
![](https://i.imgur.com/fjbY3ZC.png)
Nie mamy matchującego tagu, mamy cache miss, więc teraz cache musi zażądać przekazania tego adresu fizycznego do pamięci w celu pobrania tego bajtu.

**Adres 0x0040**
1. Zapisujemy binarnie: 0000 0000 0100 0000, dzielimy na bity VPO i VPN, mamy:
 - VPO: 00 0000 = 0
 - VPN: 0000 0000 01 = 0000 0001 = 0x01
 - TLBI: 01 = 0x1
 - TLBT: 000000 = 0x00
![](https://i.imgur.com/RPOXi17.png)

2. Patrzymy na TLB table: szukamy w secie 1 tagu 00
![](https://i.imgur.com/Bs3yTG3.png)

**Valid = 0 -> TBL hit?: N, Page Fault?: N, PPN:?**
Sprawdzamy page table o wartości VPN= 0x01, żeby sprawdzić czy ta strona jest w pamięci, jeśli valid = 1 => tak
![](https://i.imgur.com/PdUQ0aD.png)
Nie ma tej strony w pamięci, nie umiemy pobrać PPN, page fault.

---


### Zadanie 4

W tym zadaniu będziemy analizowali w jaki sposób system operacyjny musi aktualizować **tablicę stron** wraz z kolejnym dostępami do pamięci głównej. Załóż, że strony są wielkości 4KiB, TLB jest
**w pełni asocjacyjne** z zastępowaniem LRU. Jeśli potrzebujesz **wtoczyć (ang. swap-in)** stronę z dysku użyj następnego numeru **ramki (ang. page frame)** większego od największego istniejącego w tablicy stron.

Dla poniższych danych podaj ostateczny stan TLB i tablicy stron po wykonaniu wszystkich dostępów do
pamięci. Dla każdej operacji dostępu do pamięci wskaż czy było to trafienie w TLB, trafienie w tablicę stron,
czy też **błąd** strony.
![](https://i.imgur.com/gGFp1Vy.png)


**Tablica stron** - Struktura danych stosowana do przechowywania aktualnych adresów wirtualnych wraz z odpowiadającymi im adresami fizycznymi.

**TLB jest w pełni asocjacyjne** - Każdy adres może być pamiętany w dowolnym bloku pamięci podręcznej.

LRU = Least Recently Used

**wtoczyć (ang. swap-in) stronę z dysku** - Wczytanie przez OS wpisu w tablicy stron, którego nie było w RAMie

**ramka (ang. page frame)** -  „physical page” (tj. fragment pamięci fizycznej).

**Błąd strony(ang. page fault)**  - rodzaj wyjątku zgłaszanego przez sprzęt komputerowy, gdy uruchomiony program uzyskuje dostęp do strony pamięci, która nie jest obecnie mapowana przez jednostkę zarządzania pamięcią do wirtualnej przestrzeni adresowej procesu.
(strony nie ma w pamięci głównej DRAM)

### rozwiązanie:

- Page size: 4KiB = 4096 bytes = 2^12 bytes
- VPO: log2(2^12) = 12 bitów na offset
    Rozmiar strony to 4KiB => P = 4 * 2^10 B = 2^12 B       => p = 12  (bitów na offset(najmłodsze bity))
- Reszta bitów to tag (skoro mamy w pełni asocjacyjną to nie ma indeksu)

#### Zmiany:

1. Adres: 4669 = 0001 001000111101
    - VPO: 0010 0011 1101 = 0x23d
    - VPN, TLBT: 0001 = 0x1 => tag = 1

Szukamy w TLB tagu 1, nie ma go w TLB;
Szukamy PPN, sprawdzamy tablicę stron po VPN = 1.
PageFault, bo nie ma w tablicy stron (nie ma w RAMie, jest na dysku), uzupełniamy tablicę; TLB: Tag=11 wypada, bo jego LRU = 0,  Tag=1 wpada, jego LRU ustawiamy na max możliwą wartość = 3, resztę dekrementujemy.

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
| 1     | 1   | 3   | 13  |
| 1     | 7   | 0   | 4   |
| 1     | 3   | 1   | 6   |
| 0     | 4   | 2   | 9   |

| VPN | Valid |  PPN  |
| --- | ----- | ----- |
| 0   | 1     | 5     |
| 1   | 1     | 13    |
| 2   | 0     | dysk  |
| 3   | 1     | 6     |
| 4   | 1     | 9     |
| 5   | 1     | 11    |
| 6   | 0     | dysk  |
| 7   | 1     | 4     |
| 8   | 0     | dysk  |
| 9   | 0     | dysk  |
| 10  | 1     | 3     |
| 11  | 1     | 12    |
| 12  | 0     | brak  |



2. Adres: 2227 = 0000 100010110011
    - VPO: 1000 1011 0011 = 0x8b3
    - VPN, TLBT: 0000 = 0 => tag = 0

Szukamy w TLB tagu 0, nie ma go w TLB;
Szukamy PPN, sprawdzamy tablicę stron po VPN = 0.
Jest w tablicy stron, PPN=5;
TLB: Tag=7 wypada, bo jego LRU=0, Tag=0 wpada, jego LRU ustawiamy na max możliwą wartość (3).

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
| 1     | 1   | 2   | 13  |
| 1     | 0   | 3   | 5   |
| 1     | 3   | 0   | 6   |
| 0     | 4   | 1   | 9   |


3. Adres: 13916 = 11 0110 0101 1100
    - VPO: 0110 0101 1100
    - VPN, TLBT: 0011 = 3
Szukamy w TLB tagu 3, jest w TLB => PPN = 6, ustawiamy mu max wartość LRU, reszcie dekrementujemy.

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
| 1     | 1   | 1   | 13  |
| 1     | 0   | 2   | 5   |
| 1     | 3   | 3   | 6   |
| 0     | 4   | 0   | 9   |


4. Adres: 34587 = 1000 0111 0001 1011
    - VPO: 0111 0001 1011
    - VPN, TLBT: 1000 = 8
Szukamy w TLB tagu 8, nie ma go w TLB;
Szukamy w tablicy stron PPN strony o VPN=8,
PageFault, bo nie ma w tablicy stron (nie ma w RAMie, jest na dysku), uzupełniamy tablicę; Tag 4 wypada, bo jesgo LRU=0, wpada tag 8, jego LRU=3, a PPN=14;

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
| 1     | 1   | 0   | 13  |
| 1     | 0   | 1   | 5   |
| 1     | 3   | 2   | 6   |
| 1     | 8   | 3   | 14   |


| VPN | Valid |  PPN  |
| --- | ----- | ----- |
| 0   | 1     | 5     |
| 1   | 1     | 13    |
| 2   | 0     | dysk  |
| 3   | 1     | 6     |
| 4   | 1     | 9     |
| 5   | 1     | 11    |
| 6   | 0     | dysk  |
| 7   | 1     | 4     |
| 8   | 1     | 14    |
| 9   | 0     | dysk  |
| 10  | 1     | 3     |
| 11  | 1     | 12    |
| 12  | 0     | brak  |


5. Adres: 48870 = 1011 1110 1110 0110
    - VPO: 1110 1110 0110
    - VPN, TLBT: 1011 = 11
Szukamy w TLB tagu 11, nie ma go w TLB;
Szukamy w tablicy stron PPN strony o VPN= 11, znajdujemy PPN=12, w TLB tag 1 wypada, bo LRU=0, tag 11 wchodzi z LRU=3

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
| 1     | 11  | 3   | 12  |
| 1     | 0   | 0   | 5   |
| 1     | 3   | 1   | 6   |
| 1     | 8   | 2   | 14  |



6. Adres: 12608 = 0011 0001 0100 0000
    - VPO: 0001 0100 0000
    - VPN, TLBT: 0011 = 3

Szukamy tagu 3 w TLB, jest tam tenże tag, więc ustawiamy LRU na 3 i się cieszymy

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
| 1     | 11  | 2   | 12  |
| 1     | 0   | 0   | 5   |
| 1     | 3   | 3   | 6   |
| 1     | 8   | 1   | 14  |

7.  49225 =  1100 000001001001
    - VPO: 0000 0100 1001
    - VPN, TLBT: 1100 = 12

Szukamy tagu 12, nie ma go w TLB, nie ma go tam, więc szukamy w tablicy stron, PPN strony o VPN=12, jest tam, ale jest brak PPN, więc nie możemu pobrać PPN, więc jest Page Fault;

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
| 1     | 11  | 2   | 12  | => czy tu tag=12?
| 1     | 0   | 0   | 5   |
| 1     | 3   | 3   | 6   |
| 1     | 8   | 1   | 14  |

### Zadanie 5
Niech system posługuje się 32-bitowymi adresami wirtualnymi, rozmiar strony ma 4KiB, a rozmiar wpisu tablicy stron zajmuje 4 bajty. Dla procesu, który łącznie używa 1GiB swojej przestrzeni adresowej podaj rozmiar tablicy stron: (a) jednopoziomowej, (b) dwupioziomowej, gdzie katalog tablicy stron (czyli tablica stron pierwszego poziomu) ma 1024 wpisy. Dla drugiego przypadku – jaki jest maksymalny i minimalny rozmiar tablicy stron?

rozmiar strony $4KiB = 2^{12}B$
rozmiar wpisu $4B=2^{2}B$
przestrzeń adresowa $1GiB$ = $2^{30}B$ = $1024^{3}B$

a) $\frac{2^{32}*2^{2}}{2^{12}}=2^{22}B = 4MB$
b) 12 bitów na offset -> na pierwszą i drugą tablicę jest po 10 bitów
* minimalny rozmiar tablicy stron:
$\frac{2^{30}}{2^{10}*2^{12}}= 2^{8}$ tablic II poziomu
poziom II: $2^{8}*2^{10}*2^{2} = 2^{20}B = 1 MB$
poziom I: $2^{10}*2^{2} = 2^{12} = 4 KiB$
$1MB + 4 KiB$
* maksymalny rozmiar tablicy stron:
wszystkie tablice w drugim poziomie są używane
poziom II: $2^{10}*2^{10}*2^{2} = 2^{22}B = 4 MB$
poziom I: $2^{10}*2^{2} = 2^{12} = 4 KiB$
$4MB + 4 KiB$

### Zadanie 6

![](https://i.imgur.com/PFK2b2N.png)

**Pomoc naukowa:**

**Organizacja tablic stron i format adresu wirtualnego**

![](https://i.imgur.com/QWLZVeB.png)

**W jaki sposób tłumaczone są adresy wirtualne na fizyczne?**

Tak jak widzimy na 1 obrazku: adres wirtualny składa się z 5 części, ostatnia z nich to offset, czyli standardowo tak jak w rozwiązaniu z 1 tablicą stron. Pierwsze 4 części (oznaczmy je sobie jako VPN1, VPN2, VPN3, VPN4) to natomiast indeksy tablic kolejnych 4 warstw tablic stron. Aby przetłumaczyć taki adres najpierw z pierwszej tablicy stron wybieramy wpis o indeksie VPN1. Ten wpis będzie zawierał między innymi addres tablicy w 2 warstwie tablic stron. Teraz VPN2 będzie naszym indexem w tablicy z drugiej warstwy. I znowu dostaniemy adres tablicy z trzeciej warstwy tablic stron. Bierzemy VPN3 jako offset tej tablicy itd. I w taki sam sposób docieramy aż do warstwy 4 z której otrzymujemy już faktyczny adres fizyczny strony której szukamy.

**Jaką przewagę ma taka tablica nad tablicą jednopoziomową?**

Główną zaletą jest oszczędzenie olbrzymiej ilości pamięci ponieważ zamiast wczytywać całą tablicę stron która może być naprawdę olbrzymia wczytujemy tylko te części tablicy z której faktycznie korzystamy, a często zdarza się tak że korzystamy tylko z małej części całej tej przestrzeni adresowej. Co prawdopodobnie można było zauważyć w poprzednim zadaniu. Przykładowo* dla 32 bitowego procesora, 64KB rozmiaru strony i każdy wpis jest 4B:
- jeśli mamy jedną tablicę całkowita potrzebna pamięć to 4MB
- jeśli mamy już 2 warstwy to może się okazać że  wystarczy nam zaledwie 8KB

**Opisz pola w tablicach każdego poziomu.**

**Kolejne pomoce naukowe:**

**Wpisy tablicy stron poziomu 1, 2 i 3**

![](https://i.imgur.com/xsMJdBm.png)

**Wpisy tablicy stron poziomu 4**

![](https://i.imgur.com/3lCcr4o.png)

*- znalezione w jakiejś mądrej książce której tytułu nie pamiętam, sam tego nie liczyłem

### Zadanie 7
*Na wykładzie przyjęliśmy, że translacja adresów jest wykonywana przed dostępem do pamięci podręcznej. Taki schemat określa się mianem pamięci podręcznej **indeksowanej** i **znakowanej adresami fizycznymi** (ang. physically-indexed, physically-tagged). Wyjaśnij jak zrównoleglić dostęp do TLB i pamięci podręcznej, stosując schemat pamięci indeksowanej wirtualnie i znakowanej fizycznie.
Wskazówka: Posłuż się slajdem 34 do wykładu „Virtual Memory: Concepts”, ale wytłumacz to szczegółowo!*

**Pamięci podręczne indeksowane fizycznie, fizycznie znakowane** (ang. *physically-indexed, physically-tagged - PIPT*) używają adresu fizycznego zarówno dla indeksu, jak i tag. Proste w implementacji, ale powolne, ponieważ adres fizyczny musi zostać wyszukany (co może wiązać się z brakiem TLB i dostępem do pamięci głównej), zanim ten adres będzie można wyszukać w pamięci podręcznej.

**Pamięci podręczne wirtualnie indeksowane, fizycznie znakowane** (ang. *virtually indexed, physically tagged - VIPT*) używają adresu wirtualnego dla indeksu i adresu fizycznego w tagu.
Przewagą nad PIPT jest mniejsze opóźnienie, ponieważ linię pamięci podręcznej można przeglądać równolegle z translacją TLB. Jednak tag jest porównywany dopiero, gdy adres fizyczny jest dostępny. Przy odpowiednio dobranym rozmiarze indeksu, można również zapobiec problemom ze spójnością. Prawidłowy rozmiar indeksu zależy od rozmiaru strony: translacja między adresem wirtualnym a fizycznym są wykonywane na poziomie strony, jeśli indeks jest wybrany w taki sposób, że zawsze odnosi się do offsetu pamięci podręcznej w stronie, nie ma znaczenia, czy korzystamy z adresu fizycznego lub wirtualnego.

![](https://i.imgur.com/UtpwKFf.png)
