#include<initializer_list>
#include <iostream>
using namespace std;

class polynomial{
    private:
        int n;
        double* a;
    public:

        polynomial();
        polynomial(int n, double a[]);
        polynomial(initializer_list<double> a);
        polynomial(const polynomial& p);
        polynomial(polynomial&& p);
        polynomial &operator = ( const polynomial &p); // kopiujacy
        polynomial &operator = (polynomial&& p); // przenoszacy
        ~polynomial();

        friend istream& operator >> (istream &in, polynomial &p);
        friend ostream& operator << (ostream &out, polynomial &p);

        friend polynomial operator + (const polynomial &u, const polynomial &v);
        friend polynomial operator - (const polynomial &u, const polynomial &v);
        friend polynomial operator * (const polynomial &u, const polynomial &v);
        friend polynomial operator * (const polynomial &u, const double c);
        polynomial& operator += (const polynomial &v);
        polynomial& operator -= (const polynomial &v);
        polynomial& operator *= (const polynomial &v);
        polynomial& operator *= (double c);
        double operator () (double x) const; // obliczenie wartoœci polynomialu dla x
        double& operator [] (int i) const; // odczytanie i-tego wspó³czynnika
        int getDegree();


};
