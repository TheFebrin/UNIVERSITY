#include <bits/stdc++.h>

#include "punkt.hpp"
#include "odcinek.hpp"
#include "trojkat.hpp"
#include "funkcje.hpp"

using namespace std;

int main()
{
	Punkt a = Punkt(1.0,1.0), b = Punkt(0.0,0.0), c = Punkt(6.0,6.0);

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
	Odcinek o = Odcinek(b,a);
	o.print();

	cout << "Dlugosc odcinka: " << o.dlugosc() << endl;

	cout << "Czy punkt c = (6, 6) lezy na odcinku?: " << o.czy_punkt_lezy_na_odcinku(c) << endl;

	cout << "Srodek odcinka o: ";
	 o.srodek_odcinka().print();
	 Punkt p = o.srodek_odcinka();

	 o.obrot(b,90);
	 o.print();

	cout << endl;


	//--TROJKAT-----------------------------------------------
	cout << "Trojkat t: \n";
	Trojkat t = Trojkat(Punkt(0,0), Punkt(5,0), Punkt(5,10));
	t.print();

	cout << "Czy punkt (1,1) w trojkacie?: " << t.czy_punkt_w_srodku(Punkt(1,1)) << endl;

	Trojkat t2 = Trojkat(Punkt(4,0), Punkt(10,0), Punkt(10,100));
	cout << "Czy t zawiera t1?: " << t.zawiera(t, t2) << endl;
	cout << endl;




    return 0;
}
