#pragma once
#ifndef Punkt
#include <bits/stdc++.h>

using namespace std;

class Punkt{
public:
    Punkt();
    Punkt(Punkt &p); // konstruktor kopiujacy
    Punkt(double x, double y);
    ~Punkt();

    void print();
    double get_x();
    double get_y();

    void obroc(Punkt a, double alfa);
    void translacja(double x, double y);

private:
    double x, y;


};
#endif
