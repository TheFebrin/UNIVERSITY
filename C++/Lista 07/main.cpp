#include <bits/stdc++.h>
#include "wymierna.hpp"
using namespace std;

int main()
{

    cout << "START!\n";

    wymierna w(2,-8);
    cout << w.get_licznik() << " " << w.get_mianownik() << endl;

    wymierna x = w;
    cout << x.get_licznik() << " " << x.get_mianownik() << endl;


    return 0;
}
