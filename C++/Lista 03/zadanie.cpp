#include <bits/stdc++.h>

#include "punkt.hpp"
#include "odcinek.hpp"
#include "trojkat.hpp"
#include "funkcje.hpp"

using namespace std;

int main()
{
	Punkt a = Punkt(1.0,1.0), b = Punkt(2.0,2.0), c = Punkt(6.0,6.0);

	cout << "Punkt a: ";
	a.print();
	cout << "Translacja o punktu 'a' o (7,7): ";
	a.translacja(7,7);
	a.print();
	cout << endl;


	cout << "Punkt c: ";
	c.print();
	cout <<"Odleglosc: a <-> c: " << dist(a,c) << endl;
	cout << endl;

	//--ODCINEK-----------------------------------------------
	cout <<"Odcinek o: \n";
	Odcinek o = Odcinek(a,b);
	o.print();

	cout << "Dlugosc odcinka: " << o.dlugosc() << endl;

	cout << "Czy punkt c = (6, 6) lezy na odcinku?: " << o.czy_punkt_lezy_na_odcinku(c) << endl;

	cout << "Srodek odcinka o: ";
	 o.srodek_odcinka().print();


	cout << endl;


	//--TROJKAT-----------------------------------------------
	cout << "Trojkat t: \n";
	Trojkat t = Trojkat(a,b,c);
	t.print();
	cout << endl;




    return 0;
}
