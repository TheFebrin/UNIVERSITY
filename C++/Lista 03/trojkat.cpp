#include "trojkat.hpp"
#include "punkt.hpp"
#include "funkcje.hpp"

Trojkat::Trojkat(){
    Punkt a = Punkt(0,0), b = Punkt(1,0), c = Punkt(0,1);
    p1 = a;
    p2 = b;
    p3 = c;
}

Trojkat::Trojkat(Punkt a, Punkt b, Punkt c){
    // sprawdzenie czy punkty nie sa wspolniniowe
    double a_x = a.get_x(), a_y = a.get_y();
    double b_x = b.get_x(), b_y = b.get_y();
    double c_x = c.get_x(), c_y = c.get_y();

    if( (a_x == b_x and a_x == c_x and b_x == c_x)
    or (a_y == b_y and a_y == c_y and b_y == c_y))
        throw std::invalid_argument("Wszystkie wierzcholki są tym samym punktem!");

    if( (a_x == b_x and a_y == b_y) or (b_x == c_x and b_y == c_y) or (a_x == c_x and a_y == c_y) )
        throw std::invalid_argument("Wierzcholki nachodza na siebie!");

    p1 = a;
    p2 = b;
    p3 = c;
}


void Trojkat::print(){
    this->p1.print();
    this->p2.print();
    this->p3.print();
}

 Punkt Trojkat::get_a(){
    return this->p1;
 }

Punkt Trojkat::get_b(){
    return this->p2;
}

Punkt Trojkat::get_c(){
    return this->p3;
}

double Trojkat::pole(Trojkat t){
    Punkt a = t.get_a(), b = t.get_b(), c = get_c();
    double a_x = a.get_x(), a_y = a.get_y();
    double b_x = b.get_x(), b_y = b.get_y();
    double c_x = c.get_x(), c_y = c.get_y();

    return 0.5 * (a_x * b_y + b_x * c_y + c_x * a_y - c_x * b_y - a_x * c_y - b_x * a_y );
}

double Trojkat::obwod(Trojkat t){
    Punkt a = t.get_a(), b = t.get_b(), c = get_c();
    double dist1 = dist(a, b);
    double dist2 = dist(b, c);
    double dist3 = dist(b, c);

    return dist1 + dist2 + dist3;
}

Punkt Trojkat::srodek(Trojkat t){
    Punkt a = t.get_a(), b = t.get_b(), c = get_c();
    double a_x = a.get_x(), a_y = a.get_y();
    double b_x = b.get_x(), b_y = b.get_y();
    double c_x = c.get_x(), c_y = c.get_y();

    double x = (a_x + b_x + c_x) / 3;
    double y = (a_y + b_y + c_y) / 3;

    Punkt p = Punkt(x,y);
    return p;

}

double Trojkat::znak(Punkt p1, Punkt p2, Punkt p3){
    return (p1.get_x() - p3.get_x()) * (p2.get_y() - p3.get_y()) - (p2.get_x() - p3.get_x()) * (p1.get_y() - p3.get_y());
}

bool Trojkat::czy_punkt_w_srodku(Punkt p){
    double d1, d2, d3;
    bool minus, plus;

    d1 = znak(p, this->get_a(), this->get_b());
    d2 = znak(p, this->get_b(), this->get_c());
    d3 = znak(p, this->get_c(), this->get_a());

    minus = (d1 < 0) or (d2 < 0) or (d3 < 0);
    plus = (d1 > 0) or (d2 > 0) or (d3 > 0);

    return !(minus and plus);
}

bool Trojkat::zawiera(Trojkat t1, Trojkat t2) {
    Punkt a1 = t1.get_a();
    Punkt b1 = t1.get_b();
    Punkt c1 = t1.get_c();

    Punkt a2 = t2.get_a();
    Punkt b2 = t2.get_b();
    Punkt c2 = t2.get_c();

    return (!t1.czy_punkt_w_srodku(a1) and !t1.czy_punkt_w_srodku(b1) and !t1.czy_punkt_w_srodku(c1) and !t2.czy_punkt_w_srodku(a2) and !t2.czy_punkt_w_srodku(b2)and !t2.czy_punkt_w_srodku(c2));
}

void Trojkat::translacja(double x, double y){
    this->p1.translacja(x, y);
    this->p2.translacja(x, y);
    this->p3.translacja(x, y);
}

void Trojkat::obrot(Punkt p, double alfa){
    this->p1.obroc(p, alfa);
    this->p2.obroc(p, alfa);
    this->p3.obroc(p, alfa);
}
