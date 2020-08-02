# Lista zadań nr 12

### Zadanie 1

http://15418.courses.cs.cmu.edu/spring2013/article/27

**zakleszczenie**
Sytuacja, w której co najmniej dwie różne akcje czekają na siebie nawzajem, więc żadna nie może się zakończyć.
System ma zaległe operacje do wykonania, ale żadna operacja nie może zrobić postępu.
Zakleszczenie może wystąpić, gdy każda operacja uzyska zasób współużytkowany, którego potrzebuje inna operacja. W rezultacie nikt nie może kontynuować, ponieważ wszyscy czekają na udostępniony zasób, który wstrzymuje inny proces. 

![](https://i.imgur.com/9ho1UOw.png)
![](https://i.imgur.com/8tVkjIQ.png)
![](https://i.imgur.com/QtzlaAY.png)


---

**uwięzienie**
Uwięzienie występuje gdy procesy nie są blokowane, ale są zbyt zajęte odpowiadaniem sobie nawzajem.
Uwięzienie jest podobne do zakleszczenia, z tym wyjątkiem, że każdy proces wykonuje bezużyteczną pracę. Uwięzienie to stan, w którym system wykonuje wiele transakcji / operacji, ale żaden wątek nie robi znaczącego postępu. Typowym przykładem w systemie komputerowym jest ciągłe przerywanie i ponawianie operacji.

![](https://i.imgur.com/xwh8Rru.png)
![](https://i.imgur.com/GcyNbW8.png)

---

**głodzenie**

System robi ogólny postęp, ale niektóre procesy nie czynią postępu. Głodzenie dotyczy jednak określonego procesu, którego obsługa — najczęściej ze względu na niski priorytet — jest odkładana na dalszy plan, przy czym w systemie ciągle jest rywal o wyższym priorytecie. 
Na rysynku żólte samochody muszą czekać, aż wszystkie zielone przejadą.

![](https://i.imgur.com/qQ23Pb6.png)


**zapobieganie zakleszczeniom**
Chcemy zapobiec:
1. Wzajemnemu wykluczeniu - żaden proces nie może mieć wyłącznego dostępu do zasobu. Przeważnie nie jest możliwe zapobiegnięcie sytuacji wzajemnego wykluczania, ponieważ obsługa urządzeń w większości przypadków realizowana jest w trybie wyłączności. 
2. Trzymanie zasobu i oczekiwanie - zadanie może rozpocząć działanie dopiero w momencie dostępności wszystkich zasobów niezbędnych do jego zakończenia lub zadanie zwalnia wszystkie zajmowane zasoby przed żądaniem tych, które potrzebują (rozwiązanie niepraktyczne). Metoda ta jest podatna na zagłodzenie, dla procesów które żądają wielu zasobów.
3. Cykliczne oczekiwanie - Zapobieganie cyklicznemu oczekiwaniu pozwala procesom na oczekiwanie na zasoby, zapewniając jednakże, iż nie ma ono charakteru cyklicznego.
4. Brak wywłaszczania zasobu 


**wykrywanie i usuwanie zakleszczeń**
Często występuje sytuacja, w której zarówno unikanie, jak i zapobieganie zakleszczeniom nie może być użyte. Wykrycie zakleszczenia oraz zrestartowanie procesów może również prowadzić do usunięcia zakleszczeń. Jest to stosunkowo łatwe do wykonania od momentu zajęcia przez procesy zasobów lub na podstawie planera systemu operacyjnego. 


### Zadanie 2
```cpp=
const int n = 50;
shared int tally = 0;

void total() {
    for (int count = 1; count <= n; count++)
        tally = tally + 1;
        }

void main() { parbegin (total(), total()); }
```

**Sytuacja wyscigu** - zdarzenie, gdy co najmniej dwa procesy mają współbieżny dostęp do wspólnej zmiennej. Obydwa odczytują tę samą wartość zmiennej, następnie wykonują na niej operacje. Wartość zmiennej zależy od tego, który proces wykonał zapis jako ostatni.


## 2 procesy
Mamy dwa procesy `total()`.


### Maksymalna wartość

Może dojść do takiej sytuacji, że procesy A i B będą działać "na zmianę". Czyli np. proces A odczytuje wartość zmiennej, inkrementuje ją, a potem zapisuje. Następnie proces B odczytuje wartość zmiennej (już zinkrementowaną przez proces A), inkrementuje ją i zapisuje. I tak 50 razy.

Prześledźmy wartość `tally` w pierwszych 5 obrotach pętli:


| Proces A | Proces B |
| -------- | -------- |
|    1     |    2     |
|    3     |    4     |
|    5     |    6     |
|    7     |    8     |
|    9     |    10    |

Końcowa wartość `tally` jest równa 100.

### Minimalna wartość

Może też dojść do następującej sytaucji

1. Proces A odczytuje wartość `tally` i inkrementuje ją. Potem traci procesor, więc ta wartość nadal pozostaje w rejestrze, zatem `tally = 0`.
2. Proces B odczytuje wartość `tally` (nadal 0) i wykonuje 49 inkrementacji (odczyt, inkrementacja, zapis), a następnie traci procesor. Wtedy `tally = 49`.
3. Proces A odzyskuje procesor i dokonuje zapisu (w rejestrze miał wartość 1), więc po tej operacji `tally = 1`.
4. Proces B dokonuje ostatniej inkrementacji. Odczytuje wartośc `tally`, czyli w rejestrze ma 1, a potem traci procesor.
5. Proces A przejmuje procesor i wykonuje 49 inkrementacji, więc `tally = 49`.
6. Proces B odzyskuje procesor. Pozostało mu zinkrementować wartośc rejestru i zapisać. W rejestrze było 1, więc ostatecznie zapisuje do `tally` 2.

Końcowa wartość `tally` jest równa 2.

Zatem końcowa wartość zmiennej `tally` mieści się w przedziale $[2, 100]$

## k procesów

Analogicznie do powyższego przykładu.

### Maksymalna wartość - 50k

### Minimalna wartość - 2

### Zadanie 3
Przeanalizuj poniższy pseudokod wadliwego rozwiązania problemu producent-konsument. Zakładamy, że kolejka «queue» przechowuje do n elementów. Wszystkie operacje na kolejce są **atomowe** (ang. atomic). Startujemy po jednym wątku wykonującym kod procedury «producer» i «consumer». Procedura «sleep» usypia wołający wątek, a «wakeup» budzi wątek wykonujący daną procedurę. Wskaż przeplot instrukcji, który doprowadzi do:
* (a) błędu wykonania w linii 6 i 13 
* (b) zakleszczenia w liniach 5 i 12.
```=cpp
1 def producer():
2     while True:
3         item = produce()
4         if queue.full():
5             sleep()
6         queue.push(item)
7         if not queue.empty():
8             wakeup(consumer)

9 def consumer():
10     while True:
11         if queue.empty():
12             sleep()
13         item = queue.pop()
14         if not queue.full():
15             wakeup(producer)

16 consume(item)
```
*Wskazówka: Jedna z usterek na którą się natkniesz jest znana jako problem zagubionej pobudki (ang. lost wake-up problem)*

Operacja jest atomowa jeśli obserwator nie może zobaczyć wyników pośrednich.

1. Błędy w liniach 6 i 13
    * błąd w linii 6 (push do pełnej kolejki):
        * konsument sprawdza, że kolejka nie jest pełna (jest prawie pełna)
        * producent dodaje nowy element do kolejki, po czym idzie spać
        * konsument budzi producenta
        * producent próbuje dodać nowy element do pełnej kolejki
    * błąd w linii 13 (pop z pustej kolejki):
        * producent sprawdza, że kolejka nie jest pusta
        * konsument popuje z kolejki ostatni element, po czym idzie spać
        * producent budzi konsumenta
        * konsument wykonuje pop na pustej kolejce

2. Zakleszczenie w liniach 5 i 12
    * konsument sprawdza, że kolejka jest pusta
    * producent produkuje n elementów, za każdym razem budzi konsumenta, który jeszcze nie śpi
    * konsument idzie spać
    * producent idzie spać

### Zadanie 4
Poniżej znajduje się propozycja programowego rozwiązania problemu **wzajemnego wykluczania** dla dwóch procesów. Znajdź kontrprzykład, w którym to rozwiązanie zawodzi. Okazuje się, że nawet recenzenci renomowanego czasopisma „Communications of the ACM” dali się zwieść.

```cpp=1
shared boolean blocked [2] = { false, false };
shared int turn = 0;

void P (int id) {
    while (true) {
        blocked[id] = true;
        while (turn != id) {
            while (blocked[1 - id])
                continue;
            turn = id;
        }
        /* put code to execute in critical section here */
        blocked[id] = false;
    }
}
void main() { parbegin (P(0), P(1)); }
```
**Problem wzajemnego wykluczania** (ang. mutual execlusion) - równoczesne użycie wspólnych zasobów przez różne wątki/procesy. 
Algorytmy wzajemnego wykluczania są używane w przetwarzaniu współbieżnym w celu uniknięcia równoczesnego użycia wspólnego zasobu (np. zmiennej globalnej) przez różne wątki/procesy w częściach kodu zwanych sekcjami krytycznymi.
**Sekcja krytyczna** jest fragmentem kodu w programie każdego z procesów, który ze względu na poprawność nie może być wykonywany współbieżnie. Wykonywanie sekcji krytycznej przez jeden proces wyklucza możliwość wykonywania swoich sekcji krytycznych przez inne procesy (stąd nazwa wzajemne wykluczanie). Sekcja krytyczna każdego procesu może być inna. Najczęściej jest to fragment kodu związany z modyfikacją jakieś współdzielonej zmiennej lub z dostępem do jakiegoś zasobu, który może być używany w trybie wyłącznym.

Kontrprzykład:
Stan początkowy:
blocked[2] = {false, false};
turn = 1;

1. P(0) wykonuje się. Ustawia blocked[0] = true, zostaje przerwany przed krytyczną sekcją i blocked[0] = false.
2. Następnie P(1) wykonuje się i przechodzi do sekcji krytycznej.
3. Ponownie wykonuje się P(0) i chce wykonać sekcje krytyczną.
Błąd - dwukrotnie wykonywana jest sekcja krytyczna.


Kolejne wykonywanie:
P0: while (true) {
P0:   blocked[0] = true;
P0:   while (turn != 0) {
P0:     while (blocked[1]) {
P0:     }
P1: while (true) {
P1:   blocked[1] = true;
P1:   while (turn != 1) {
P1:   }
P1:   criticalSection(P1);
P0:     turn = 0;
P0:   while (turn != 0)
P0:   }
P0:   critcalSection(P0);

### Zadanie 5

Algorytm  Petersona rozwiązuje  programowo  problem  wzajemnego  wykluczania.  Zreferuj  poniższą wersję implementacji tego algorytmu dla dwóch procesów. Wykaż jego poprawność.
```cpp=1
shared boolean flag [2] = { false, false };
shared int turn = 0;
void P (int id) {
    while (true) {
        flag[id] = true;
        turn = 1 - id;
        while (flag[1 - id] && turn == (1 - id))
            continue;
            
    /* put code to execute in critical section here */
    
    flag[id] = false;
    }
}

void main() { parbegin (P(0), P(1)); }
```
Ciekawostka:Czasami ten algorytm stosuje się w praktyce dla architektur bez instrukcji atomowych np.: [tegra_pen_lock](https://elixir.bootlin.com/linux/latest/source/arch/arm/mach-tegra/sleep-tegra20.S)

1. Jeżeli `P(a)` utknie w pętli (linia 7), to może zostać z niej uwolniony tylko przez `P(b)`, nadając wartość zmiennej `turn = a`, wtedy `P(b)` albo sam się zapętli (bo wtedy `flag[a] == true && turn = a`), albo właśnie opuścił sekcję krytyczną (`turn[b] = false`).
2. `P(b)` przed sprawdzeniem/w trakcie sprawdzannia warynku wejścia do pętli (linia 7). Warunek wejścia do pętli (linijka 7) nie został sełniony, dla `P(a)`. Czyli nie zaszło `flag[b] && turn == b`. W momencjie sprawdzania warunków musiało dojśc do jednej z następujących sytuacji:
    * `flag[b] == false`, wtedy `P(b)` się zapętli.
    * `turn == a`, `P(a)` ustawił wartość zmiennej `turn = b`, więc `P(b)` musiał ustawić wartość `turn = a`, ale w tym przypadku `P(b)` zapętli się.

### Zadanie 6

TODO

### Zadanie 7

TODO

### Zadanie 8

Rozważmy zasób, do którego dostęp jest możliwy wyłącznie w kodzie otoczonym parą wywołań `acquire` i `release`. 

Chcemy by wymienione operacje miały następujące właściwości:
- mogą być co najwyżej trzy procesy współbieżnie korzystające z zasobu,
- jeśli w danej chwili zasób ma mniej niż trzech  użytkowników, to możemy bez opóźnień przydzielić zasób kolejnemu procesowi,
- jednakże, gdy zasób ma już trzech użytkowników, to muszą oni wszyscy zwolnić zasób, zanim zaczniemy dopuszczać do niego kolejne procesy,
- operacja `acquire` wymusza porządek _„pierwszy na wejściu, pierwszy na wyjściu”_ (ang. _FIFO_). 

Podaj co najmniej jeden kontrprzykład wskazujący na to, że poniższe rozwiązanie jest niepoprawne.

```python
mutex = semaphore(1)  # implementuje sekcję krytyczną
block = semaphore(0)  # oczekiwanie na opuszczenie zasobu
active = 0            # liczba użytkowników zasobu
waiting = 0           # liczba użytkowników oczekujących na zasób
must_wait = False     # czy kolejni użytkownicy muszą czekać?
```

```python=
def acquire():
    mutex.wait()
    if must_wait:        # czy while coś zmieni?
        waiting += 1
        mutex.signal()   # <-- !!!
        block.wait()     # <-- !!!
        mutex.wait()
        waiting -= 1
    active += 1
    must_wait = (active == 3)
    mutex.signal()

def release():
    mutex.wait()
    active -= 1
    if active == 0:
        n = min(waiting, 3);
        while n > 0:
            block.signal()
            n -= 1
        must_wait = False
    mutex.signal()
```

Wątek | Działanie i efekty uboczne
--- | ---
_Thread 0_ | Wywołuje `acquire()`, _must_wait_ pozostaje jako `False`, active=1
_Thread 1_ | Wywołuje `acquire()`, _must_wait_ pozostaje jako `False`, active=2
_Thread 2_ | Wywołuje `acquire()`, _must_wait_ staje się `True`, active=3
_Thread 3_ | Wywołuje `acquire()`, wchodzi do bloku `if must_wait:`, następuje przerwanie po `mutex.signal()` w 5 wierszu
_Thread 0_ | Wywołuje `release()`, zwalnia zasób, _active_=2
_Thread 1_ | Wywołuje `release()`, zwalnia zasób, _active_=1
_Thread 2_ | Wywołuje `release()`, zwalnia zasób, _active_=0
_Thread 4_ | Wywołuje `acquire()`, przeskakuje blok `if must_wait:`, _active_=1

`Thread 4` otrzymał dostęp do zasobu przed `Thread 3`, pomimo tego, że czwarte założenie gwarantuje porządek _FIFO_.

### Czy `while` coś zmieni?

Możemy wykorzystać `while` zamiast `if` aby wymusić ponowne sprawdzenie warunku - może się okazać, że wątek zostanie wybudzony, pomimo tego, że warunek w instrukcji warunkowej nie został spełniony - ponowne jego sprawdzenie pozwoli uniknąć dalszego, nieoczekiwanego wykonania kodu danej sekcji.

W tym wypadku _must_wait_ i tak wynosi `True`, więc `Thread 3` wykonałby zarówno `if must_wait:` jak i `while must_wait:`.