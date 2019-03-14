#include "punkt.hpp"


Punkt::Punkt(){
    x = 0;
    y = 0;
}

Punkt::Punkt(Punkt &p){
    this->x = p.x;
    this->y = p.y;
}

Punkt::Punkt(double xx, double yy){
    this->x = xx;
    this->y = yy;
}

Punkt::~Punkt(){
}


void Punkt::print(){
    cout << this->x << " " << this->y << endl;
}

double Punkt::get_x(){
    return this->x;
}

double Punkt::get_y(){
    return this->y;
}

void Punkt::obroc(Punkt a, double alfa){
    double a_x = a.get_x();
    double a_y = a.get_y();

    double t_x = this->x;
    double t_y = this->y;
    double kat = alfa * M_PI / 180;

    this->x = t_x * cos(kat) - t_y * sin(kat);
    this->y = t_x * sin(kat) + t_y * cos(kat);

    this->translacja(a_x, a_y);
}

void Punkt::translacja(double x, double y){
    this->x += x;
    this->y += y;
}
