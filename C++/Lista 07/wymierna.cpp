#include "wymierna.hpp"

wymierna::wymierna()
{
    this->licznik = 1;
    this->mianownik = 1;
}

wymierna::wymierna(int licznik, int mianownik)
        : licznik(licznik), mianownik(mianownik)
{
    if( mianownik == 0 ){
        throw invalid_argument("Mianownik nie moze byc ZEREM!\n");
    }

    if( mianownik < 0 ){
        this->mianownik *= -1;
        this->licznik *= -1;
    }

    int NWD = gcd(abs(licznik), abs(mianownik));
    this->licznik /= NWD;
    this->mianownik /= NWD;
}

wymierna::~wymierna()
{

}

int wymierna::gcd(int a , int b)
{
   if ( b == 0 ) return a;
   a %= b;
   return gcd(b,a);
}





