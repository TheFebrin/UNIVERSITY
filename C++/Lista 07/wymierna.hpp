#include <bits/stdc++.h>
using namespace std;

class wymierna
{

public:
    wymierna();
    wymierna(int licznik, int mianownik);

    wymierna(int liczba) // konstruktor konwertujacy
        : licznik(liczba), mianownik(1) {}

    ~wymierna();

    int get_licznik() const { return licznik; };
    int get_mianownik() const { return mianownik; };

private:
    int licznik, mianownik;
    int gcd(int a , int b);

};
// Zadbaj o to, aby miamownik zawsze był liczbą dodatnią oraz
// aby największy wspólny dziel- nik licznika i mianownika zawsze był równy 1.
