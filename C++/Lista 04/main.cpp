#include <bits/stdc++.h>
using namespace std;

#include "Queue.hpp"

int main()
{
    bool nieKoniec = true;
    char c;
    int n;

    cout << "Podaj rozmiar kolejki: ";
    cin >> n;

    Queue *k;
    k = new Queue(n);

    while (nieKoniec)
    {
        cout << "e - wloz do koleki\n"
             << "d - wyciagnij z kolejki\n"
             << "b - sprawdz poczatek\n"
             << "s - podaj rozmiar\n"
             << "f - czy jest pelna\n"
             << "c - zawartosc\n"
             << "l - wyjdz\n";

        cin >> c;

        switch (c)
        {
        case 'e':
            try
            {
                string element;
                cin >> element;
                k->insert(element);
                cout << "Do kolejki dodano element: " << element << "\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        case 'd':
            try
            {
                string element = k->pop();
                cout << "Z kolejki usunieto element: " << element << "\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        case 'b':
            try
            {
                string element = k->front();
                cout << "Poczatek kolejki: " << element << "\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        case 's':
            cout << "Rozmiar kolejki: " << k->size() << "\n";
            break;
        case 'f':
            cout << "Czy pelna: " << k->isFull() << "\n";
            break;

        case 'c':
            k->print_queue();
            cout << "\n";
            break;
        case 'l':
            nieKoniec = false;
            break;
        }
    }

    Queue *kolejka, *kolejka2, *kolejka3, *kolejka4;

    kolejka = new Queue(initializer_list<string>{"A", "B", "C"});

    kolejka2 = new Queue(*kolejka);
    kolejka3 = new Queue(initializer_list<string>{"X", "y", "Z"});

    kolejka3->print_queue();
    cout << "\n";

    kolejka3 = kolejka;

    kolejka3->print_queue();
    cout << "\n";

    kolejka3->print_queue();

    return 0;
}
