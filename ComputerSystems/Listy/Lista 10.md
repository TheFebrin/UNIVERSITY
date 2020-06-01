
# Lista 10

### Zadanie 1
Wyjaśnij różnice między powłoką (ang. shell), systemem operacyjnym i jądrem systemu operacyjnego (ang.kernel). W tym celu dobierz kilka przykładów powszechnie wykorzystywanego oprogramowania. Jakie są główne zadania systemu operacyjnego z punktu widzenia programisty?

![](https://i.imgur.com/xPISwQb.png)

**powłoka / shell** - Program, z którym użytkownicy wchodzą w interakcje. Pośrednik pomiędzy systemem operacyjnym lub aplikacjami, a użytkownikiem.
Powłoki można podzielić na tekstowe i graficzne.

    - przykłady powłok: bash, Windows shell, gnome

**system operacyjny** - System operacyjny dostarcza programistom czystego abstrakcyjnego zestawu zasobów zamiast bałaganu sprzętowego i zarządza zasobami sprzętowymi. System operacyjny zarządza wątkami i procesami, rozporządza pamięcią.

    - przykłady systemów: Windows, Linux, MacOS


**jądro systemu operacyjnego** - Oprogramowanie działające w trybie jądra. W tym trybie ma pełny dostęp do całego sprzętu i może wykonywać dowolne instrukcje, które maszyna jest w stanie wykonać. Jądro to program komputerowy stanowiący rdzeń systemu operacyjnego komputera, który zapewnia pełną kontrolę nad wszystkim w systemie.

    - przykłady jąder: Solaris, Windows NT, Linux Kernel, FreeBSD


Główne zadania systemów operacyjnych z punktu widzenia programisty:
* planowanie listy procesów, zarządzanie działającymi procesami i wątkami
* zarządzanie pamięcią
* komunikacja między urządzeniami zewnętrznymi
* przekazanie interfejsu dla użytkownika


### Zadanie 2

![](https://i.imgur.com/XL2bPA0.jpg)

### Zadanie w systemach wsadowych

Pierwsze komputery były wielkimi maszynami wyposażonymi najczęściej w drukarki, czytniki kart, przewijaki taśm i konsolę. Ze względu na ich cenę i koszty utrzymania priorytetem było efektywne wykorzystanie czasu pracy komputera. Użytkownicy nie mieli bezpośredniego dostępu do komputera. Pracę komputera nadzorował wyspecjalizowany operator. Użytkownicy przekazywali swoje **zadania**, czyli programy i dane wejściowe (zazwyczaj w formie kart perforowanych), operatorowi, a po jakimś czasie mogli odebrać wyniki (w postaci wydruków). Operator łączył zadania o podobnych wymaganiach w tzw. wsady (ang. batch). System operacyjny był bardzo prosty, jego rola sprowadzała się do wczytywania kolejnych zadań i uruchamiania ich.
![](https://i.imgur.com/LEGo1Ae.jpg)


### Monitor

**Monitor** prosty program, stale przebywający w pamięci operacyjnej i umożliwiający śledzenie przebiegu realizacji programu. Monitor rozpoczynając zadanie przekazuje mu kontrolę nad komputerem i przejmuje ją po zakończeniu zadania.

### Planowanie zadań

**Planowanie zadań** to ustalanie kolejności wykonywania zadań, przydzielenie im czasu korzystania z procesora oraz zasobów, z których dane zadanie będzie korzystać.

### Język kontroli zdań
![](https://i.imgur.com/WrGrjPq.png)

`$JOB` - definiuje początek zadania o podanym ID
`$EXECUTE` - wykonuje zadanie o podanym ID
`$IBSYS` - System Supervisor zostaje wezwany do magazynowania rdzenia i jest mu przyznawana kontrola, czyta i przetwarza kolejne karty dopóki kontrola nie zostanie przekazana do podsystemu poprzez kartę execute
`$RELEASE` - uwolnia jednostkę przydzieloną do funkcji
`$IBEDT` - przekazanie kontroli do System Editor

Obecnie systemy wsadowe wykorzystywane są np. w drukarkach.

### Zadanie 3

Jaka była motywacja do wprowadzenia **wieloprogramowych** systemów wsadowych? W jaki sposób wieloprogramowe systemy wsadowe wyewoluowały w systemy z **podziałem czasu** (ang. time-sharing)? Podaj przykład historycznego systemu **interaktywnego**, który nie jest wieloprogramowy.

#### Rozwiązanie:
Jaka była motywacja do wprowadzenia **wieloprogramowych** systemów wsadowych?
* Poprzednio w komputerach (np. 7094) bieżące zadanie było wstrzymywane do czasu zakończenia operacji z taśmą lub innej operacji wejścia/wyjścia - no i procesor pozostawał bezczynny w tym czasie (w komercyjnym przypadku to było jakieś 80-90% czasu). Trzeba lepiej używać moc obliczeniową.

W jaki sposób wieloprogramowe systemy wsadowe wyewoluowały w systemy z **podziałem czasu** (ang. time-sharing)?
* Systemy operacyjne trzeciej generacji potrafiły bezpośrednio czytać informacje z karty na dysk, ale potem trzeba byo długo czekać na wynik, co się programistom nie podobało, bo nie mogli tak jak za czasów pierwszej generacji kiedy mieli komputer dla siebie na kilka godzin, podebugować w międzyczasie.
* Odpowiedzią na ten popyt zostały systemy time-sharing gdzie kilku użytkowników miało jednoczesny dostęp do komputera za pomocą wielu terminali - kiedy część z nich myślała albo debugowała, to ci którzy chcieli coś policzyć - wykorzystywali komputer.

Historyczny system **interaktywny**(czyli pozwala użytkownikowi wpływać na system operacyjny w trakcie pracy innego programu), który nie jest wieloprogramowy:
* MS-DOS

**wieloprogramowe systemy wsadowe** - pamięć podzielona na kilka cześci, podczas gdy jedno zadanie korzystało z wejścia/wyjścia to inne mogło zajmować procesor

**systemy z podziałem czasu** - komputer umożliwiającym dostęp wielu użytkownikom na raz za pomocą różnych terminali, co sprawiało że kiedy jeden naukowiec myślał to inny mógł używać procesora, kiedy ten stał bezczynnie



### Zadanie 4
Uruchom program «1_ls» pod kontrolą narzędzia «ltrace -S».

Na podstawie śladu wykonania programu zidentyfikuj, które z **wywołań systemowych** są używane przez procedury: «opendir», «readdir», «printf» i «closedir».

Do czego służy wywołanie systemowe «brk»?
Używając debuggera «gdb» i polecenia «catch syscall brk» zidentyfikuj, która funkcja używa «brk».

* **Wywołanie systemowe** (ang. system call) –

Stanowi interfejs między wykonywanym programem a (posiadającym zwykle wyższe uprawnienia) jądrem systemu operacyjnego. Funkcje systemowe wywoływane są przez specjalny mechanizm, wspierany przez dany procesor, na przykład z użyciem wyznaczonego przerwania lub instrukcji skoku dalekiego.

Mechanizm ten pozwala na realizację zależnych od platformy sprzętowej zadań, do których proces użytkownika może nie mieć bezpośredniego dostępu. W nowoczesnych systemach operacyjnych realizacja takiego wywołania poprzedzona jest przez weryfikację uprawnień programu. Przykładami wywołań systemowych mogą być:

- dostęp do systemu plików,
- komunikacja międzyprocesowa,
- uruchamianie innych programów,
- sterowanie urządzeniami systemowymi,
- obsługiwanie komunikacji sieciowej.

Lista wywołań systemowych ściśle zależy od typu oraz wersji systemu operacyjnego i dlatego w większości zastosowań bezpośrednie odwoływanie się do nich nie jest wskazane. Zamiast tego w wywołaniach pośredniczą standardowe biblioteki programistyczne.





* `ltrace -S ./1_ls <directory>`
> ltrace is a debugging utility in Linux, used to display the calls a userspace application makes to shared libraries.
![](https://i.imgur.com/JosVF0Z.png)

| Procedura | Wywołanie systemowe |
| - | - |
|«opendir» | SYS_openat|
|«readdir» | SYS_getdents64|
|«printf» | SYS_write|
|«closedir» | SYS_close|


* GDB
>brk and sbrk are basic memory management system calls used in Unix and Unix-like operating systems to control the amount of memory allocated to the data segment of the process.

>Wywołanie systemowe SYS_brk powoduje zmianę lokalizacji przerwania programu, czyli zmianę końca segmentu danych procesu. Zwiększenie wartosci brk powoduje przydzielenie pamieci do procesu, a zmiejszenie tej wartosci zwalnia tę pamięć.

`gdb ./1_ls <dir>`
`catch syscall brk`
`run`
`c`
`c`
`c`
`backtrace`


- _dl_start
![](https://i.imgur.com/BhJ0H2s.png)

- __opendir
![](https://i.imgur.com/qrSmz3n.png)

### Zadanie 5

Standardowe wejście/wyjście - strumienie danych z pomocą których można przekazać jakieś dane do wykonywanego programu lub odebrać dane obliczone w trakcie wykonywania programu.

Deskryptor pliku - prosty identyfikator tworzony przez system przy okazji otwierania jakiegoś pliku, z pomocą którego będzie się można później przy okazji odczytów/zapisów w prosty sposób odwołać do danego pliku.

Dane są wczytywane do deskryptora 0 i zapisywane do deskryptora 1
![](https://i.imgur.com/nh3r5Dh.png)

Zmodyfikowany program:
![](https://i.imgur.com/kriBrWn.png)

Ścieżka - ciąg znaków określający położenie dowolnego obiektu w strukturze katalogu na dysku twardym lub innym nośniku danych

Wynik programu po podaniu pliku:
![](https://i.imgur.com/JKODtnH.png)

Wynik programu po podaniu katalogu:
![](https://i.imgur.com/qfsRerx.png)

Wynik programu z użyciem strace'a po podaniu katalogu:
![](https://i.imgur.com/QWKlA4w.png)


### Zadanie 6
W systemach uniksowych wszystkie procesy są związane relacją **rodzic-dziecko**.
Uruchom polecenie «ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd».
Na wydruku zidentyfikuj **identyfikator procesu, identyfikator grupy procesów, identyfikator rodzica oraz właściciela procesu**.

1. Kto jest rodzicem procesu init?
> Rodzicem inita jest jądro (PID 0)
2. Wskaż, które z wyświetlonych zadań są **wątkami jądra**.
> Patrzymy na ziomów z PPID = 2 | nazwy są pod CMD
3. Jakie jest znaczenie poszczególnych znaków w kolumnie STAT?
> Screen niżej
4. Wyświetl drzewiastą reprezentację **hierarchii procesów** poleceniem pstree – które z zadań są wątkami?
> Screen niżej

#### Definicje
**rodzic-dziecko**
>każdy proces poza init ma swojego rodzica, proces od którego pochodzi

**Wątki jądra**
>Lekkie procesy, działające asynchronicznie w
przestrzeni jądra (podobnie jak zwykłe wątki w
przestrzeni użytkownika), niezwiązane z
żadnym procesem użytkownika
>http://students.mimuw.edu.pl/ZSO/Wyklady/00_stud/watki_jadra.pdf
>Rodzicem wszystkich wątków jądra jest kthreadd (PID = 2)

**hierarchia procesów**

![](https://i.imgur.com/XSqgcCX.png)
http://www.cs.put.poznan.pl/mholenko/modx/index.php?id=43


#### Screeny
* `ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd`
![](https://i.imgur.com/ENawEBN.png)
    - USER -- właściciel procesu
    - PID -- identyfikator procesu
    - PPID -- identyfikator procesu rodzica
    - PGID -- identyfikator grupy procesów

* kolumna STAT
![](https://i.imgur.com/NnwBroR.png)


* pstree (wątki to procesy w [{...}])
![](https://i.imgur.com/RKAuJhD.png)

### Zadanie 7

![](https://cdn.discordapp.com/attachments/689526193849892867/716989244303736833/unknown.png)

![](https://cdn.discordapp.com/attachments/689526193849892867/716989459878510612/unknown.png)

Addres - początkowy adres dla danego odwzorowania
Perm - prawo do oczytu / zapisu / wykonania / współdzielenia
Size - rozmiar
Mapping - plik, który jest odwzorowany / heap / stack / anon

Stos ma w kolumnie mapping [stack], sterta ma [heap] (widoczne tylko z opcją -X, lub -XX). Segment to fragment kodu, który został odwzorowany w przestrzeń adresową programu. Pamięć anonimowa [anon] jest rodzajem pamięci, która nie jest powiązana z żadnym nazwanym obiektem.

### Zadanie 8
![](https://i.imgur.com/yyMY4T4.png)

**Zasoby plikopodobne** - obiekty "wyglądające" jak pliki, nie odpowiadające zawartości trwałego nośnika.
**Pliki** - ciąg bajtów o swobodnym dostępie.
**Katalogi** - ciąg rekordów opisujących zawartość katalogu,
**Urządzenia** - pliki reprezentujące zawartość urządzeń fizycznych.

**Gniazda** - dwukierunkowe kanały komunikacyjne między procesami (również na znajdujących się na różnych komputerach).
**Potoki** - jednokierunkowe kanały komunikacyjne.

Wykaz wynikowy programu `lsof` zawiera kolumny opisujące:

|          |                                                                                                                              |
| -------- | ---------------------------------------------------------------------------------------------------------------------------- |
| COMMAND  | polecenie związane z procesem                                                                                                |
| PID      | PID                                                                                                                          |
| USER     | właściciel procesu (dokładniej: właściciel katalogu w /proc związanego z procesem                                            |
| FD       | numer deskryptora pliku lub cwd - gdy katalogiem roboczym, rtd – gdy korzeniem systemu plików, mem – plik mapowany w pamięci |
| TYPE     | rodzaj zasobu, np. gniazdo IPv4, katalog, zwykły plik                                                                        |
| DEVICE   | identyfikator urządzania, z którego pochodzi plik                                                                            |
| SIZE/OFF | rozmiar lub lokalizacja kursora w zasobie                                                                                    |
| NODE     | identyfikator i-węzła, oznaczenie TCP i inne                                                                                 |
