#include "odcinek.hpp"
#include "punkt.hpp"

Odcinek::Odcinek(){
    Punkt a = Punkt(0,0), b = Punkt(1,1);
    this->p1 = a;
    this->p2 = b;
}

Odcinek::Odcinek(Odcinek &o){
    this->p1 = o.get_first();
    this->p2 = o.get_second();
}

Odcinek::Odcinek(Punkt a, Punkt b){
    this->p1 = a;
    this->p2 = b;

    // wyjatek dla dwoch takich samych pkt
    if( a.get_x() == b.get_x() and a.get_y() == b.get_y() ){
        throw invalid_argument("nie można utworzyć odcinka o długości 0");
    }
}

Odcinek::~Odcinek(){
}

void Odcinek::print(){
    this->p1.print();
    this->p2.print();
}

Punkt Odcinek::get_first(){
    return this->p1;
}

Punkt Odcinek::get_second(){
    return this->p2;
}

double Odcinek::dlugosc(){
    return dist(this->p1, this->p2);
}

bool Odcinek::czy_punkt_lezy_na_odcinku(Punkt p){
    double left_dist = dist(p, this->p1);
    double right_dist = dist(p, this->p2);

    return abs(left_dist + right_dist - this->dlugosc()) <= 0.0001 ;
}

Punkt Odcinek::srodek_odcinka(){
    Punkt p1 = this->p1;
    Punkt p2 = this->p2;

    double x = (p1.get_x() + p2.get_x()) / 2;
    double y = (p1.get_y() + p2.get_y()) / 2 ;
    Punkt wynik = Punkt(x,y);

    return wynik;
}

void Odcinek::translacja(double x, double y){
    this->p1.translacja(x,y);
    this->p2.translacja(x,y);
}

void Odcinek::obrot(Punkt p, double alfa){
    this->p1.obroc(p, alfa);
    this->p2.obroc(p, alfa);
}

bool Odcinek::rownolegle(Odcinek o, Odcinek m){
    Punkt o_first = o.get_first();
    Punkt o_second = o.get_second();

    Punkt m_first = m.get_first();
    Punkt m_second = m.get_second();

    double odc_1 = (o_first.get_y() - o_second.get_y()) / (o_first.get_x() - o_second.get_x());

    double odc_2 = (m_first.get_y() - m_second.get_y()) / (m_first.get_x() - m_second.get_x());

    return odc_1 == odc_2;
}

bool Odcinek::prostopadle(Odcinek o, Odcinek m){
    Punkt o_first = o.get_first();
    Punkt o_second = o.get_second();

    Punkt m_first = m.get_first();
    Punkt m_second = m.get_second();


    double odc_1 = (o_first.get_y() - o_second.get_y()) / (o_first.get_x() - o_second.get_x());

    double odc_2 = (m_first.get_y() - m_second.get_y()) / (m_first.get_x() - m_second.get_x());

    return (odc_1 == -odc_2) or (-odc_1 == odc_2);
}

Punkt Odcinek::punkt_przeciecia(Odcinek o, Odcinek m){
    // wyjatek jesli nie ma punktu przeciecia
    if (rownolegle(o, m))
        throw std::invalid_argument("Odcinki sa rownolegle!");

    Punkt o_p = o.get_first();
    Punkt o_k = o.get_second();

    Punkt m_p = m.get_first();
    Punkt m_k = m.get_second();

    double ax1 = (o_p.get_y() - o_k.get_y()) / (o_p.get_x() - o_k.get_x());
    double b1  = o_p.get_y()- ax1 * o_p.get_x();

    double ax2 = (m_p.get_y() - m_k.get_y()) / (m_p.get_x() - m_k.get_x());
    double b2  = m_p.get_y()- ax1 * m_p.get_x();

    double x = (ax1 - ax2) / (b2 - b1);
    double y = ax1 * x + b1;

    Punkt p = Punkt(x, y);

    if( o.czy_punkt_lezy_na_odcinku(p) and o.czy_punkt_lezy_na_odcinku(p) ){
        return Punkt(x, y);
    }
    else{
        throw std::invalid_argument("Odcinki sa rozłączne!");
    }

}
