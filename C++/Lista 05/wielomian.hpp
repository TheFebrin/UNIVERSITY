#include<initializer_list>
#include <iostream>
using namespace std;

class wielomian{
    private:
        int n;
        double* a;
    public:

        wielomian();
        wielomian(int n, double a[]);
        wielomian(initializer_list<double> a);
        wielomian(const wielomian& p);
        wielomian(wielomian&& p);
        wielomian &operator = ( const wielomian &p); // kopiujacy
        wielomian &operator = (wielomian&& p); // przenoszacy
        ~wielomian();

        friend istream& operator >> (istream &in, wielomian &p);
        friend ostream& operator << (ostream &out, wielomian &p);

        friend wielomian operator + (const wielomian &u, const wielomian &v);
        friend wielomian operator - (const wielomian &u, const wielomian &v);
        friend wielomian operator * (const wielomian &u, const wielomian &v);
        friend wielomian operator * (const wielomian &u, const double c);
        wielomian& operator += (const wielomian &v);
        wielomian& operator -= (const wielomian &v);
        wielomian& operator *= (const wielomian &v);
        wielomian& operator *= (double c);
        double operator () (double x) const; // obliczenie wartoœci wielomianu dla x
        double& operator [] (int i) const; // odczytanie i-tego wspó³czynnika
        int wez_stopien();


};
