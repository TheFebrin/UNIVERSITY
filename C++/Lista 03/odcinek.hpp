#pragma once
#ifndef Odcinek
#include <bits/stdc++.h>
#include "punkt.hpp"
#include "funkcje.hpp"

using namespace std;

class Odcinek{
public:
    Odcinek();
    Odcinek(Odcinek &o); // konstruktor kopiujacy
    Odcinek(Punkt p1, Punkt p2);
    ~Odcinek();

    void print();
    Punkt get_first();
    Punkt get_second();

    double dlugosc();
    bool czy_punkt_lezy_na_odcinku(Punkt p);
    Punkt srodek_odcinka();

    void translacja(double x, double y);
    void obrot(Punkt p, double alfa);

    bool rownolegle(Odcinek o, Odcinek m);
    bool prostopadle(Odcinek o, Odcinek m);
    Punkt punkt_przeciecia(Odcinek o, Odcinek m);


private:
    Punkt p1, p2;
};
#endif
