# POO Lista 1
###### tags: `POO`

![](https://i.imgur.com/KsWsWkV.png)


#### Dokument SIWZ: 
http://bip.ksap.gov.pl/pliki/ERP_BA_260_16_2019/SIWZ_po_zmianach.pdf


#### SMART:
* Simple - Szczegółowy / prosty
* Measurable - Mierzalny 
* Achievable - Osiągalny / atrakcyjny
* Relevant - Istotny /mrealistyczny
* Time-specific - Terminowy

### Analiza FURPS dla powyższego dokumentu:

* Functional - Funkcjonalności, możliwości, bezpieczeństwo:
    * System powinien być dostępny z różnych systemów operacyjnych.
        * S - mało szczegółowe, o jakie systemy dokładnie chodzi?
        * M - jeżeli wiadomo o jakie systemy chodzi, można to łatwo sprawdzić
        * A - tak
        * R - tak
        * T - nie sprecyzowane
        * O jakich dokładnie systemach operacyjnych mowa?
    * System powinien umożliwiać wysyłanie bezpośrednio z systemu wiadomości SMS i e-mail.
        * S - nie do końca szczegółowe
        * M - cięzko powiedzieć z powodu braku szczegółów
        * A - tak
        * R - tak
        * T - nie sprecyzowane
        * Do jakich krajów mogą zostać wysłane wiadomości SMS, jak dużo tych wiadmomości może być i jak szybko muszą dochodzić do odbiorcy?

    * wymagania ... włączona obsługa javaScript
        * S - mało szczegółowe, brak informacji o wersji
        * M - łatwo sprawdzić czy JS działa
        * A - tak
        * R - tak
        * T - czas nie jest sprecyzowany
        * Obsługa javaScript w jakiej wersji i na jakich przeglądarkach?
* Usability (UX) - Czynnik ludzki, pomoc, dokumentacja
    * System powinien umożliwiać z poziomu interfejsu tworzenie cech / pól dodatkowych, które będą mogły przechowywać niestandardowe wartości określone na etapie wdrożenia i utrzymania systemu.
        * S - niejasne wymaganie
        * M - niewiadomo co tu mierzyć
        * A - tak, jezeli sprecyzujemy
        * R - tak, jeżeli dowiemy się o celu omawianych pól
        * T - nie
        * O jakie cechy i pola dodatkowe chodzi? Jaki jest ich cel biznesowy, za co maja odpowiadać?
* Reliability - Awaryjność, odzyskiwanie, przewidywalność
     * Ze względu na posiadaną infrastrukturę, dostępność kadry technicznej oraz stabilność, system powinien umożliwiać instalacje bazy głównej w systemie Windows Server z wykorzystaniem bazy danych MS SQL lub innej, której producent zapewnia możliwość wsparcia oraz posiada wbudowane mechanizmy wspierające replikację oraz moduły analityczne na potrzeby BI.
        * S - nie bardzo
        * M - niewiadomo co mierzyć
        * A - na tym etapie ciężko powiedzieć
        * R - tak
        * T - nie podano
        * Jak dokładnie chcemy replikować bazę danych? O ilu replikach mowa? O jakie modułach anlityczne chodzi?
* Performance - Czas reakcji, przepustowość, dokładność, dostępność, wykorzystanie zasobów
    * wymagania sprzętowe ... komputer klasy PC lub MAC, o następującej konfiguracji: pamięć min. 3 GB RAM, procesor 1500 MHz lub lepszy, jeden z systemów operacyjnych: Windows 7, Linux Kernel 4.0 i MacOS 10.12 lub ich nowsze wersje,
        * S - tak
        * M - tak
        * A - tak
        * R - tak
        * T - nie podano
        * Ile pamięci dyskowej potrzebuje komputer?
    
* Supportability - Dostosowanie, utrzymanie, konfiguracja, lokalizacja
    * W szczególności Zamawiający wymaga, aby aktualizacja systemu głównego nie pociągała za sobą konieczności oddzielnego dostosowywania rozwiązań w kanale WWW.
        * S - tak
        * M - tak
        * A - tak
        * R - tak
        * T - nie podano
        * brak pytań

    * Wymagania techniczne to ... zainstalowana przeglądarka internetowa: Internet Explorer 11, Firefox ver. 46 i późniejsze, Chrome ver. 45 lub późniejsze, Opera ver. 37 lub późniejsze,
        * S - tak
        * M - tak
        * A - tak
        * R - tak
        * T - nie podano
        * Na jakim systemie operacyjnym ma działać dana przeglądarka?


![](https://i.imgur.com/PQiB9wt.png)

### Zakupy w sklepie internetowym

#### Brief
Klient wchodzi na stonę internetową sklepu i przegląda produkty. Produkty, które ma zamiar kupić dodaje do swojego koszyka. Gdy w koszyku jest już wszystko co chce kupić klient przechodzi on do koszyka w celu finalizacji zamówienia. Klient klika ikonkę logowania, wprowadza swój e-mail i hasło w odpowiednie pola i loguje się na swoje konto.
Następnie wypełnia on adres na który zamówienie ma zostać dostarczona i używa karty aby dokonać płatności. Zamówienie zostało złożone.


#### Fully dressed

** Zakupy w kasie samoobsługowej. **

* Primary Aktor - klient sklepu
* Interesariusze i interesy
    * Klient - chce zapłacić za zakupy
    * Sklep - chce umożliwić klientom szybkie i wygodne płacenie za zakupy, przy okazji odciąża też pracowników sklepu
* Warunki wstępne
    * W sklepie jest kasa samoobsługowa. Można w niej płacić kartą. Klient posiada kartę płatniczą oraz środki na koncie wystarczające na opłacenie zakupów.
* Warunki końcowe
    * Klient zapłacił za zakupy. Pieniądze z konta klienta zostały przelane na konto bankowe sklepu.
* Główny scenariusz sukcesu
    * Klient skanuje kody kreskowe wszystkich jego produktów.
    * W szczególnych przypadkach klient waży przedmioty i używa UI kasy aby wybrać odpowiednie artykuły.
    * Klient klika płatność kartą.
    * Klient zbliża kartę lub wprowadza ją do terminala.
    * W zależności od wymagań klient może zostać poproszony o podanie kodu PIN.
    * Kasa samoobsługowa akceptuje płatność i drukuje paragon.
    * Klient pakuje swoje zakupy i wychodzi ze sklepu.
* Rozszerzenia
    * W dowolnym momencie użytkownik może anulować zeskanowany przedmiot jeżeli się pomylił i np. skasował coś dwa razy. Pracownik sklepu potwierdza anlulowanie artykułu.
    * W przypadku braku środków na koncie klient jest proszony o inną kartę lub inny środek płatniczy, np. kod BLIK.
* Dodatkowe wymagania
    * Kasa musi posiadać dotykowy ekran.
    * Napisy na ekranie kasy są czytelne i dobrze widoczne.
    * Możliwa jest zmiana języku UI
    * Kasa musi posiadać miejsce na koszyk, z którego klient wyciąga produkty. Oraz wagę na którą te produkty odkłada.
* Technologia i format danych
    * System płatniczy zintegrowanty z kasą obsługuje transakcje kartą.
    * System płatniczy posiada klawiaturę na wprowadzenie kodu PIN do karty.
    * Komunikacja z kasą za pomocą dotykowego ekranu.

