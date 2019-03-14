#pragma once
#ifndef Trojkat
#include <bits/stdc++.h>
#include "punkt.hpp"

class Trojkat{
public:
    Trojkat();
    Trojkat(Punkt a, Punkt b, Punkt c);

    void print();
    Punkt get_a();
    Punkt get_b();
    Punkt get_c();

    double pole(Trojkat t);
    double obwod(Trojkat t);
    Punkt srodek(Trojkat t);
    double znak(Punkt p1, Punkt p2, Punkt p3);
    bool czy_punkt_w_srodku(Punkt t);
    bool zawiera(Trojkat t1, Trojkat t2);

    void translacja(double x, double y);
    void obrot(Punkt p, double alfa);

private:
    Punkt p1, p2, p3;

};
#endif
