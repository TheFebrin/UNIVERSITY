#include <bits/stdc++.h>
#include "wymierna.hpp"
using namespace std;
using namespace obliczenia;

int main()
{
    cout << "START!\n";

    wymierna w(2,-8);
    cout << w.get_licznik() << " " << w.get_mianownik() << endl << endl;

    wymierna x = w;
    cout << x.get_licznik() << " " << x.get_mianownik() << endl << endl;

    wymierna x1 = wymierna(4,5);
    cout << x1.get_licznik() << " " << x1.get_mianownik() << endl << endl;

    w = !w;
    cout << "Test operatora ! dla -1 / 4 \n";
    cout << w.get_licznik() << " " << w.get_mianownik() << endl << endl;

    w = -w;
    cout << "Test operatora - dla -4 / 1 \n";
    cout << w.get_licznik() << " " << w.get_mianownik() << endl << endl;

    int a = (int)w;
    cout << "Test rzutowania jawnego (int) \n";
    cout << a << endl << endl;

    double b = (double)wymierna(7,11);
    cout << "Test rzutowania jawnego (double) dla 7 / 11 \n";
    cout << b << endl << endl;

    cout << "Test operatora + dla 2 / 3 + 3 / 4 \n";
    wymierna plus = wymierna(2,3) + wymierna(3,4);
    cout << plus.get_licznik() << " " << plus.get_mianownik() << endl << endl;

    cout << "Test operatora - dla 2 / 3 + 3 / 4 \n";
    wymierna minus = wymierna(2,3) - wymierna(3,4);
    cout << minus.get_licznik() << " " << minus.get_mianownik() << endl << endl;

    cout << "Test operatora * dla 2 / 3 + 3 / 4 \n";
    wymierna razy = wymierna(2,3) * wymierna(3,4);
    cout << razy.get_licznik() << " " << razy.get_mianownik() << endl << endl;

    cout << "Test operatora / dla 2 / 3 + 3 / 4 \n";
    wymierna dziel = wymierna(2,3) / wymierna(3,4);
    cout << dziel.get_licznik() << " " << dziel.get_mianownik() << endl << endl;

    cout << "Wypisywanie dla 1 / 3 \n";
    cout << wymierna(1,3) << endl << endl;

    cout << "Wypisywanie dla 5 / 11 \n";
    cout << wymierna(5,11) << endl << endl;

    cout << "Wypisywanie dla 1 / 9801 \n";
    cout << wymierna(1,9801) << endl << endl;

    cout << "Wypisywanie dla 1 / 32 \n";
    cout << wymierna(1,32) << endl << endl;

    cout << "Wypisywanie dla 1 / 23 \n";
    cout << wymierna(1,23) << endl << endl;

    cout << "Wypisywanie dla 3227 / 555 \n";
    cout << wymierna(3227,555) << endl << endl;



    return 0;
}
