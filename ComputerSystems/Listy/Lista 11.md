# Lista 11

### Zadanie 1
Podaj główne motywacje projektantów systemów operacyjnych do wprowadzenia **procesów** i **wątków**? Wymień główne różnice między nimi – rozważ współdzielone **zasoby**.

**Definicje:**
* **Proces:** to środowisko uruchomieniowe składające się:
    * z przestrzeni adresowej,
    * załadowanego programu,
    * przydzielonej pamięci, otwartych plików i innych zasobów.
    
Proces można zasiedlić niezależnymi kontekstami wykonania instrukcji, czyli **wątkami**.

* **Wątek:** to część programu wykonywana współbieżnie w obrębie jednego procesu; w jednym procesie może istnieć wiele wątków.

* **Zasoby:** Zasobem jest element sprzętowy lub programowy systemu komputerowego, którego brak może potencjalnie zablokować wykonywanie programu (przetwarzanie). Przykłady zasobów: procesor, pamięć, plik (dane) itp.

**Motywacje:**

* Teoretycznie prostszy model programowania: 
![](https://i.imgur.com/ZT19mhr.png)
W przypadku wątku (np. przy tworzeniu serwera plików - przykad z wykładu), gdy chcemy realizować wiele połączeń, w jednowątkowym modelu byłoby bardzo utrudnione, pozwalałoby na jedno połączenie na raz. Jednak gdy rozważamy wątki, dużo prościej realizowalibyśmy to zadanie.

* Wydajność:
    * Czasem chcielibyśmy mieć współpracujące procesy, jednak wtedy ich koszt jest bardzo duży, płacimy za ich tworzenie, niszczenie, zmiany kontekstu i synchronizację.
    * W przypadku maszyn wieloprocesorowych chcielibyśmy rozdzielać obliczenia pomiędzy wątki.
    * Operacje asynchroniczne np. podczas połączeń z wieloma serwerami. Jeśli nie musimy szeregowo, to równoległe przetwarzanie będzie szybsze (fork-join). Inny wariant? Jeden wątek ładuje dane z dysku, drugi przetwarza, trzeci zapisuje (pipeline).

* Responsywność:
    * Przy edycji tekstu chcemy by obciążające zadania (np. formatowanie książki) były wykonywane w tle, pozwalając użytkownikowi edytować stronę.
    * Chcemy przewijać stronę www zanim doczytają się wszystkie obrazki.

**Różnice:**
Wszystkie wątki działające w danym procesie w przestrzeni adresowej oraz wszystkich innych strukturach systemowych dysponują współdzielonymi zasobami. Natomiast procesy posiadają niezależne zasoby.
Przełączanie się pomiędzy wątkami jest dużo szybsze, niż pomiędzy procesami (bo tu dochodzi cała zmiana kontekstu, zmiana przestrzeni adresowej). Gdy zmieniamy przestrzeń adresową TLB zawiera obce wpisy tabeli stron, pamięć podęczna zawiera obce bloki pamięci, predykator skoków ma wiedzę o instrukcjach, które zniknęły.
Proces może zawierac wiele wątków, jednak wątek nie może zawierać procesów.

Tutaj zasoby dla procesów i wątków:
![](https://i.imgur.com/aVX8DsH.png)
Wątek korzysta głównie z zasobów przydzielonych procesowi współdzieli je z innymi wątkami tego procesu. Zasobem, o który wątek rywalizuje z innymi wątkami, jest procesor, co wynika z faktu, że jest on odpowiedzialny za wykonanie fragmentu programu. Wątek ma więc własne sterowanie, w związku z czym kontekst każdego wątku obejmuje licznik rozkazów, stan rejestrów procesora oraz stos. Każdy wątek musi mieć swój własny stos, gdzie odkładane są adresy powrotów z podprogramów oraz alokowane lokalne zmienne.


### Zadanie 2

Wymień mechanizmy sprzętowe niezbędne do implementacji **wywłaszczania** (ang. preemption). Jak działa **algorytm rotacyjny** (ang. round-robin)? Jakie zadania pełni **planista** (ang. scheduler) i **dyspozytor** (ang. dispatcher)? Który z nich realizuje **politykę**, a który **mechanizm**?

**Definicje:**

* **Wywłaszczenie:** technika używana w środowiskach wielozadaniowych, w której algorytm szeregujący zwany planistą lub dyspozytorem może wstrzymać aktualnie wykonywane zadanie (np. proces lub wątek), aby umożliwić działanie innemu zadaniu. Dzięki temu rozwiązaniu zawieszenie jednego procesu nie powoduje blokady całego systemu operacyjnego. 

* **Algorytm rotacyjny:** najprostszy algorytm szeregowania dla procesów w systemie operacyjnym, który przydziela każdemu procesowi odpowiednie przedziały czasowe, nie uwzględniając żadnych priorytetów. W związku z tym wszystkie procesy mają ten sam priorytet. W mechanizmach szeregowania używających priorytetów, często mechanizmu round robin używa się w stosunku do procesów o tym samym priorytecie.

* **Planista:** ogólnym zadaniem planistów (programów szeregujących) jest wybieranie procesów z pewnego zbioru tak, aby dążyć do optymalizacji przetwarzania w systemie. Kryteria optymalizacji mogą być jednak bardzo zróżnicowane. Może wstrzymać uruchomiony proces, przenieść go na spód kolejki i rozpocząć nowy.

* **Dyspozytor:** jest zaangażowany w funkcję planowania CPU. Jest on modułem, który daje kontrolę nad CPU procesowi wybranemu przez planistę krótkoterminowego. Odbiera kontrolę w trybie jądra w wyniku przerwania lub wywołania systemowego. Zostaje wywołany kiedy następuje zmiana dostępu do CPU. Odpowiada on za zapisanie stanu procesu ulegającemu zatrzymaniu oraz za wznownie stanu procesu wskazanego przez planistę. 

* **Polityka:** zestaw zasad związany z podejmowanymi przez system decyzjami.

* **Mechanizm:** rozwiązanie prowadzące do osiągnięcia jakiegoś określonego efektu (np. mechanizm synchronizacji).


**Odpowiedzi:**
Mechanizmy sprzętowe potrzebne do realizacji wywłaszczenia:  
Pełne wywłaszczanie zapewniają tylko mechanizmy sprzętowe działające niezależnie od oprogramowania (np. dołączanie wywłaszczania do procedury obsługi przerwania zegarowego).

Jak działa algorytm rotacyjny:
Każdemu procesowi jest przydzialany równa jednostka czasu. Gdy ten okres upłynie lub proces zakończy swoje działanie albo nastąpi wyjątek to następny proces będzie mógł skorzystać z procesora.

Planista realizuje politykę, a dyspozytor realizuje mechanizm.

### Zadanie 3

![](https://i.imgur.com/XYjDgYm.png)

Proc to specjalny “wirtualny” system plików. Zawiera informacje o procesach uruchomionych w systemie,o ich przestrzeni adresowej. Możemy tam znaleźć m. in. informacje o tym pod jakimi adresami leży sterta, stos czy sekcje procesu.

Zawartość katalogu /proc/pid:

![](https://i.imgur.com/mrwWrNK.png)

Argumenty wywołania – Argumenty, z jakimi został wywołany program. Znajdują się w /proc/[pid]/cmdline.

Zmienne środowiskowe – Są to takie zmienne globalne dla programu, które ułatwiają dostęp do ścieżek czy plików. Znajdują się w /proc/[pid]/environ.

Przestrzeń adresowa procesu znajduje się w /proc/[pid]/maps

man proc:

![](https://i.imgur.com/PHqTjc4.png)


Znaczenie kolumn:
- Address - Adres danego elementu
- Perms - Uprawnienia (read/write/execute/private,shared). Jeśli process próbuje skorzystać z fragmentu pamięci w sposób zablokowany przez uprawnienia, dostajemy Segmentation Fault.
- Offset - Położenie danego elementu względem początku mapowanego pliku (jeśli jest mapowanie, jeśli nie – 0)
- Dev – Jeśli region był mapowany z pliku, to jest oznaczenie na jakim urządzeniu znajduje się ten plik w kodzie szesnastkowym w formacie major:minor
- Inode – Numer pliku jeśli region był mapowany z pliku
- Pathname – ścieżka do pliku, który jest zmapowany na fragment pamięci. Dla anonimowych regionów to miejsce jest puste. Poza tym mamy też specjalne oznaczenia: [stack], [heap] oraz [vdso] (vitrual dynamic shared object – procedury jądra).

Zawartość maps:
![](https://i.imgur.com/LnSvJih.png)


Stos:
![](https://i.imgur.com/HR8j4nM.png)

Sterta:
![](https://i.imgur.com/OH5teD5.png)

Segment data tam gdzie mamy uprawnienia do czytania i zapisywania ale nie możemy wykonywać:
![](https://i.imgur.com/cSdMVPR.png)

Segment text tam gdzie mamy uprawnienia do czytania i wykonywania ale nie możemy zapisywać:
![](https://i.imgur.com/fK4lbkY.png)

Segment bss tam gdzie kolumna ze ścieżką jest pusta:
![](https://i.imgur.com/wAD0GxG.png)


### Zadanie 4

Na podstawie slajdu 25 przedstaw **stany procesu** w systemie Linux. Jakie akcje lub zdarzenia **synchroniczne** i **asynchroniczne** wyzwalają zmianę stanów? Kiedy proces opuszcza stan **zombie**? Wyjaśnij, które przejścia mogą być rezultatem działań podejmowanych przez: jądro systemu operacyjnego, kod sterowników, proces użytkownika albo administratora.

![](https://i.imgur.com/vf9pqlk.png)

**Stany procesu**:
* stopped - zatrzymay proces, może być wznowiony przy pomocy innego procesu; występuje na przykład gdy proces jest debugowany
* Ready - gotowy do wykonania; czeka na bycie wybranym przez planistę
* Executing - wykonywany w tej chwili
* Zombie - zakończony proces, ale istnieje powód dla którego wciąż musi być trzymany na liście procesów
* Interruptible - stan zablokowany, w którym proces czeka na  zdarzenie np. operację wejścia/wyjścia, dostępność zasobów albo na sygnał z innego procesu
* Uninterruptible - stan zablokowany, ale tutaj proces czeka bezpośrednio na odpowiednie warunki sprzętowe, dlatego nie może być wznowiony przez sygnał.


#### Jakie akcje lub zdarzenia **synchroniczne** i **asynchroniczne** wyzwalają zmianę stanów?
Zdarzenia synchroniczne to takie które są związane z wykonaniem instrukcji. Natomiast asynchroniczne to zdarzenia zewnętrzne to np. budzik, użytkownik naciskający Ctrl+C, itd.

#### Kiedy proces opuszcza stan **zombie**?
Kiedy jego rodzic odczyta informacje dotyczące tego procesu, wtedy też zostaje usunięty z tablicy procesów.

### Zadanie 5

Jaką rolę pełnią **sygnały** w systemach uniksowych? W jakich sytuacjach jądro wysyła sygnał procesowi? Kiedy jądro **dostarcza** sygnały do procesu? Co musi zrobić proces by **wysłać sygnał** albo **obsłużyć sygnał**? Których sygnałów nie można **zignorować** i dlaczego? Podaj przykład, w którym obsłużenie **sygnału SIGSEGV** lub **SIGILL** może być świadomym zabiegiem programisty.

**Sygnały** są mechanizmem asynchronicznym - proces nie wie z góry, kiedy sygnał może nadejść i głównym ich zadaniem jest informowanie procesu o zaistnieniu w systemie wyjątkowej sytuacji (np. spadek napięcia w sieci). Ponadto są wykorzystywane przez powłokę do kontroli pracy swoich procesów potomnych.

Istnieje różnica między procesem działającym w przestrzeni użytkownika a procesem działającym w jądrze w sposobie obsługi sygnałów. W przypadku przestrzeni użytkownika wystąpienie sygnału natychmiast przerywa wykonanie programu. Niektóre z sygnałów można ignorować lub można zarejestrować własną funkcję obsługi sygnału, ale z częścią z nich nic nie można zrobić.
W przypadku procesów wykonujących kod jądra jest zupełnie inaczej. Kiedy proces jest w stanie ready lub uninterruptible, to nie jest on nawet informowany o wystąpieniu sygnału. Informacja ta jest tylko zapisywana w stanie procesu i sygnał jest wyzwalany dopiero w momencie powrotu do przestrzeni użytkownika, kiedy jądro zakończy obsługę wywołania. Natomiast gdy proces jest w stanie interruptible, to w momencie wystąpienia sygnału jest on przełączany w stan ready, a funkcja jądra, która wprowadziła proces w stan uśpienia zwraca natychmiast kod błędu - ERESTARTSYS.
To co stanie się dalej zależy tylko i wyłącznie od kodu jądra. Może on zakończyć obsługę wywołania systemowego z błędem, ale może też wykonać dowolną inną operację lub po prostu zignorować to zdarzenie. W każdym wypadku działanie procesu w reakcji na sygnał zostanie przerwane dopiero w momencie powrotu do przestrzeni użytkownika.

Proces nigdy nie może ignorować sygnału SIGSTOP, powodującego zatrzymanie wykonywanego procesu, jak również SIGKILL, powodującego zabicie procesu. Jest to sposób na pozostawienie administratorowi kontroli nad systemem.

Sygnały mogą być generowane bezpośrednio przez użytkownika, może wysyłać je jądro oraz procesy między sobą. Dodatkowo pewne znaki z terminala powodują wygenerowanie sygnałów. Na przykład na każdym terminalu istnieje tak zwany *znak przerwania* (ang. interrupt character)  i *znak zakończenia* (ang. quit character). Znak przerwania (zazwyczaj Ctrl-C lub Delete) służy do zakończenia bieżącego procesu (wygenerowania sygnału SIGINT). Wygenerowanie znaku zakończenia (zazwyczaj Ctrl-\\) powoduje wysłanie sygnału SIGQUIT powodującego zakończenie wykonywania bieżącego procesu z zapisaniem obrazu pamięci.
Istnieją oczywiście pewne ograniczenia - proces może wysyłać sygnały tylko do procesów mających tego samego właściciela oraz z tej samej grupy. Bez ograniczeń moze to czynić jedynie jądro i administrator.
Jedynym procesem, który nie odbiera sygnałów jest init.


**SIGILL** - Niedozwolony rozkaz
Sygnał ten jest wysyłany po wystąpieniu wykrywanej sprzętowo sytuacji wyjątkowej, spowodowanej przez niewłaściwą implementację systemu.
Domyślnie powoduje zakończenie procesu z zapisem obrazu pamięci.

**SIGSEGV** - Naruszenie segmentacji
Sygnał jest generowany po wystąpieniu błędu sprzętowego spowodowanego niewlasciwą implementacją systemu. Pojawia się na ogół wtedy, kiedy proces odwoła się do takiego adresu w pamięci, do którego nie ma dostępu.
Domyślnie powoduje zakończenie procesu z zapisem obrazu pamięci.

Kiedy obsłużenie sygnału SIGSEGV może być celowym zabiegiem programistycznym?
Program może zaalokować małą stertę i nie sprawdzać jej przepełnienia, za to kiedy ono nastąpi - i nastąpi naruszenie ochrony pamięci - przechwycić ten sygnał i rozszerzyć stertę. Jest to o wiele bardziej efektywne od ciągłego sprawdzania przepełnienia (co musi następować ogromną liczbę razy), oraz od alokacji dużej ilości pamięci na stertę (co marnuje pamięć).
### Zadanie 6

Uruchom program *«xeyes»* po czym użyj na nim polecenia *«kill»*, *«pkill»* i *«xkill»*. Który sygnał jest wysyłany domyślnie? Przy pomocy kombinacji klawiszy *«CTRL+Z»* wyślij *«xeyes»* sygnał «SIGSTOP», a następnie wznów jego wykonanie. Przeprowadź inspekcję pliku «/proc/PID/status» i wyświetl **maskę sygnałów** zgłoszonych procesowi (ang. pending signals). Pokaż jak będzie się zmieniać, gdy będziemy wysyłać wstrzymanemu procesowi po kolei: *«SIGUSR1»*, *«SIGUSR2»*, *«SIGHUP»* i *«SIGINT»*. Co opisują pozostałe pola pliku *«status»* dotyczące sygnałów? Który sygnał zostanie dostarczony jako pierwszy
po wybudzeniu procesu?

Domyślnie jest wysyłany SIGTERM dla kill i xkill oraz SIGHUP dla pkill.

![](https://cdn.discordapp.com/attachments/689526193849892867/718854182374998016/unknown.png)

![](https://cdn.discordapp.com/attachments/689526193849892867/718855159551229962/unknown.png)

```=
xeyes 
cat /proc/pid/status
kill -s USR1 pid
cat /proc/pid/status
kill -s USR2 pid
cat /proc/pid/status
kill -1 pid
cat /proc/pid/status
kill -2 pid
cat /proc/pid/status
kill -s CONT pid
```

Przed
![](https://cdn.discordapp.com/attachments/689526193849892867/718860539652210759/unknown.png)

SIGUSR1
![](https://cdn.discordapp.com/attachments/689526193849892867/718860595008372777/unknown.png)

SIGUSR2
![](https://cdn.discordapp.com/attachments/689526193849892867/718860708670079076/unknown.png) 

SIGHUP
![](https://cdn.discordapp.com/attachments/689526193849892867/718860829197467668/unknown.png) 

SIGINT
![](https://cdn.discordapp.com/attachments/689526193849892867/718860940317163590/unknown.png) 

Po wznowieniu
![](https://cdn.discordapp.com/attachments/689526193849892867/718861460310196314/unknown.png)

### Zadanie 7

`time find /usr`

![](https://i.imgur.com/s7K0jED.png)

**real** - rzeczywisty czas, który upływa od momentu wywołania polecenia do jego zakończenia

**user** - czas, który procesor spędza w trybie użytkownika 

**sys** - czas, który procesor spędza w trybie jądra

---

**Czemu suma czasów user i sys nie jest równa real?**
*Real podaje czas rzeczywisty wykonania polecenia oraz uwzględnia w tym przerwy działania lub oczekiwanie. Sys i user liczy czas tylko podczas wykonywania procesu.*

**Czemu suma czasów user i sys może być większa od real?**
*Jeśli wiele jednostek obliczeniowych wykonywało proces to user oraz sys jako wynik dadzą sumę łącznego czasu z każdej jednostki. Real patrzy tylko na faktyczny czas wykonania.*

`ulimit -t 1`
`time find /usr`
`echo $?` *- kod wyjścia ostatniego polecenia*
`kill -l 137`

![](https://i.imgur.com/HlpZfvR.png)

Proces został unicestwiony, ponieważ przekroczył dozwoloną długość wykonywania polecenia.
**SIGKILL** - zabicie procesu

### Zadanie 8

Zaprezentuj sytuację, w której proces zostanie **osierocony**. W terminalu uruchom dodatkową kopię powłoki`bash`. Z jej poziomu wystartuj w tle program `xclock` i sprawdź, kto jest jego rodzicem. Poleceniem `kill` wyślij sygnał `SIGKILL` do uruchomionej wcześniej powłoki i sprawdź, kto stał się nowym rodzicem procesu `xclock`. Wyjaśnij przebieg i wyniki powyższego eksperymentu. Co się stanie, gdy zamiast `SIGKILL` wyślemy powłoce sygnał `SIGHUP`?


Proces zostaje **osierocony**, gdy jego rodzic zakończy działanie, a on jeszcze nie. Wtedy inny proces zostaje jego rodzicem.
