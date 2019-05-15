#include "wymierna.hpp"

namespace obliczenia
{

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


std::ostream &operator<<(std::ostream &wyj, const wymierna &w){
    //Liczba rzeczywista z rozwinieciem ulamkowym
    return wyj <<  (double)w.licznik / (double)w.mianownik;
}

wymierna &wymierna::operator!(){
    swap(this->licznik,this->mianownik);

    if( this->mianownik < 0 ){
        this->mianownik *= -1;
        this->licznik *= -1;
    }

    return *this;
}


wymierna &wymierna::operator-(){
    this->licznik *= -1;
    return *this;
}


wymierna::operator int(){
    return this->licznik / this->mianownik;
}


wymierna::operator double(){
    return (double)this->licznik / (double)this->mianownik;
}

wymierna operator+(const wymierna &w1, const wymierna &w2){
    int lcm = w1.mianownik * w2.mianownik / gcd(w1.mianownik , w2.mianownik);

    int licznik = w1.licznik * lcm / w1.mianownik;

    int licznik2 = w2.licznik * lcm / w2.mianownik;

    return wymierna(licznik + licznik2, lcm);
}


wymierna operator-(const wymierna &w1, const wymierna &w2){
    int lcm = w1.mianownik * w2.mianownik / gcd(w1.mianownik , w2.mianownik);

    int licznik = w1.licznik * lcm / w1.mianownik;

    int licznik2 = w2.licznik * lcm / w2.mianownik;

    return wymierna(licznik - licznik2, lcm);
}

wymierna operator*(const wymierna &w1, const wymierna &w2){
    int licznik = w1.licznik * w2.licznik;
    int mianownik = w1.mianownik * w2.mianownik;

    if( mianownik < 0 ){
        mianownik *= -1;
        licznik *= -1;
    }
    return wymierna(licznik, mianownik);
}



}



