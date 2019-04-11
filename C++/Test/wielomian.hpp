#include<initializer_list>
#include <bits/stdc++.h>
using namespace std;

class wielomian{
    private:
        int n;  // stopień wielomianu
        double* a; // współczynniki wielomianu
    public:

        wielomian();
        wielomian (int st=0, double wsp=1.0); // konstruktor tworzący jednomian
        wielomian(int n, const double a[]); // konstruktor tworzący wielomian
        wielomian(initializer_list<double> l); // lista współczynników
        wielomian(const wielomian& W);  // konstruktor kopiujący
        wielomian(wielomian&& W); // konstruktor przenoszący
        wielomian &operator = ( const wielomian &W); // przypisanie kopiujące
        wielomian &operator = (wielomian &&W); // przypisanie przenoszące
        ~wielomian(); // destruktor

        friend istream& operator >> (istream &in, wielomian &W);
        friend ostream& operator << (ostream &out, wielomian &W);

        friend wielomian operator + (const wielomian &u, const wielomian &v);
        friend wielomian operator - (const wielomian &u, const wielomian &v);
        friend wielomian operator * (const wielomian &u, const wielomian &v);
        friend wielomian operator * (const wielomian &u, const double c);
        wielomian& operator += (const wielomian &v);
        wielomian& operator -= (const wielomian &v);
        wielomian& operator *= (const wielomian &v);
        wielomian& operator *= (double c);
        double operator () (double x) const; // obliczenie wartości wielomianu dla x
        double& operator [] (int i) const; // odczytanie i-tego współczynnika
        int wez_stopien();


};
