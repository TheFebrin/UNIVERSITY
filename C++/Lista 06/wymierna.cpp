#include "wymierna.hpp"
#include "wyjatki.hpp"

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
    int licznik = w.licznik;
    int mianownik = w.mianownik;

    string rozwiniecie_dziesietne;
    unordered_map < int, int > M;
    int r = licznik % mianownik;

    while( r and M.find( r ) == M.end() ){
        M[ r ] = rozwiniecie_dziesietne.size();
        r *= 10;
        rozwiniecie_dziesietne += to_string(r / mianownik);

        r %= mianownik;
    }

    if( r == 0 ) // brak okresowosci
    {
        string pocz = to_string(licznik / mianownik ) + ".";
        rozwiniecie_dziesietne = pocz + rozwiniecie_dziesietne;

        return wyj << rozwiniecie_dziesietne;
    }
    else // ulamek okresowy
    {
        string pocz = to_string(licznik / mianownik ) + ".";
        rozwiniecie_dziesietne.insert(M[ r ],"(");
        rozwiniecie_dziesietne = pocz + rozwiniecie_dziesietne + ")";

        return wyj << rozwiniecie_dziesietne;
    }


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

    if( 1LL * licznik * 1LL * licznik2 > INT_MAX ){
        throw out_of_range("Zakres int przekroczony!\n");
    }

    return wymierna(licznik + licznik2, lcm);
}


wymierna operator-(const wymierna &w1, const wymierna &w2){
    int lcm = w1.mianownik * w2.mianownik / gcd(w1.mianownik , w2.mianownik);

    int licznik = w1.licznik * lcm / w1.mianownik;

    int licznik2 = w2.licznik * lcm / w2.mianownik;

    return wymierna(licznik - licznik2, lcm);
}

wymierna operator*(const wymierna &w1, const wymierna &w2){

    if( 1LL * w1.licznik * 1LL * w2.licznik > INT_MAX ){
        throw przekroczenie_zakresu();
    }

    int licznik = w1.licznik * w2.licznik;
    int mianownik = w1.mianownik * w2.mianownik;

    if( mianownik < 0 ){
        mianownik *= -1;
        licznik *= -1;
    }
    return wymierna(licznik, mianownik);
}

wymierna operator/(const wymierna &w1, const wymierna &w2){
    int licznik = w1.licznik * w2.mianownik;
    int mianownik = w1.mianownik * w2.licznik;

    if( mianownik == 0 ){
        throw dzielenie_przez_0();
    }

    if( mianownik < 0 ){
        mianownik *= -1;
        licznik *= -1;
    }
    return wymierna(licznik, mianownik);
}



}



