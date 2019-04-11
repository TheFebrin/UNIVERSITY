#include "wielomian.hpp"
#include <bits/stdc++.h>
using namespace std;

int main(){
    wielomian p1 = wielomian();
    double a[] = {1.0, 1.0, 1.0};

    wielomian p2 = wielomian(2, a);
    wielomian p3 = wielomian({0.0, 0.0, 0.0, 1.0});
    wielomian p4 = p2;
    cout << "Test konstruktorow: " << endl;
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 <<endl;

    wielomian p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16;
    double c;

    cout <<"\nWczytywanie wielomianow: podaj stopien i wspolczynniki od najmniej znaczacego. " << endl;

    cout << "\n DODAWANIE \n";
    cout << "p5 += p6  <-- Podaj p5 i p6" << endl;
    cin >> p5 >> p6;
    p7 = p5 + p6;
    p5 += p6;
    cout << "p7 = p5 + p6" << endl;
    cout << "p7 = " <<p7<<"\n";
    cout << "p5 += p6" << endl;
    cout << "p5 = "<< p5 <<"\n";
    cout << "p6 = "<< p6 <<"\n";


    cout << "\n ODEJMOWANIE \n";
    cout << "p8 -= p9   <--Podaj p8 i p9" << endl;
    cin >> p8 >> p9;
    p10 = p8 - p9;
    p8 -= p9;
    cout << "p10 = p8 - p9" << endl;
    cout << "p10 = " << p10 << endl;
    cout << "p8 -= p9" << endl;
    cout << "p8 = " << p8 << endl;
    cout << "p9 = " << p9 << endl;

    cout << "\n MNOZENIE \n";
    cout << "p13 = p11 * p12   p11 *= p12  <--Podaj p11 i p12" << endl;
    cin >> p11 >> p12;
    p13 = p11 * p12;
    p11 *= p12;
    cout << "p13 = " << p13 << endl;
    cout << "p11 *= p12" << endl;
    cout << "p11 = " << p11 << endl;

    cout << "p15 = p14 * c   p14 *= c   <--Podaj p14 i c\n";
    cin >> p14 >> c;
    p15 = p14 * c;
    p14 *= c;
    cout << "p15 = " << p15 << endl;
    cout << "p14 *= c" << endl;
    cout << "p14 = "<< p14 << endl;


    cout << "\n TEST OPERATOROW \n ";
    cout <<"Podaj wielomian do testow operatorow () []" << endl;
    cin >> p16;
    cout << "p16(10): " << p16(10.0) << endl;
    cout << "p16[0]: " << p16[ 0 ] << endl;
    cout << "podaj numer wsplczynnika p16 (<=" << p16.wez_stopien() << ") i jego nowa wartosc" << endl;
    int i, j;
    cin >> i >> j;
    p16[ i ] = j;
    cout << "p16[" << i << "]: " << p16[ i ] << endl;
}
