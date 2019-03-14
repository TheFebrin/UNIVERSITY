#pragma once
#ifndef Funkcje

#include <bits/stdc++.h>
#include "odcinek.hpp"
#include "punkt.hpp"

inline double dist(Punkt a, Punkt b){
    double a_x = a.get_x();
    double a_y = a.get_y();

    double b_x = b.get_x();
    double b_y = b.get_y();

    return sqrt((a_x - b_x) * (a_x - b_x) + (a_y - b_y) * (a_y - b_y));
}

#endif
