#include <bits/stdc++.h>
using namespace std;

namespace obliczenia
{

class wymierna
{

public:
    wymierna();
    wymierna(int licznik, int mianownik);

    explicit wymierna(int liczba) // konstruktor konwertujacy
        : licznik(liczba), mianownik(1) {}

    ~wymierna();

    int get_licznik() const { return licznik; };
    int get_mianownik() const { return mianownik; };

    friend std::ostream &operator<<(std::ostream &wyj, const wymierna &w);

    wymierna &operator!();

    wymierna &operator-();

    explicit operator int();

    explicit operator double();

    friend wymierna operator+(const wymierna &, const wymierna &);

    friend wymierna operator-(const wymierna &, const wymierna &);

    friend wymierna operator*(const wymierna &, const wymierna &);

    friend wymierna operator/(const wymierna &, const wymierna &);


private:
    int licznik, mianownik;
    int gcd(int a , int b);

};

}
