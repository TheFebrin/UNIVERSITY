#include "polynomial.hpp"
#include<iostream>

using namespace std;
int main(){
    polynomial p1 = polynomial();
    double a[] = {1.0,1.0,1.0};
    polynomial p2 = polynomial(2, a);
    polynomial p3 = polynomial({0.0, 0.0, 0.0, 1.0});
    polynomial p4 = p2;
    cout<<"testowanie konstruktorow:\n p1: " << p1;
    cout <<"\n p2: "<< p2<<"\n p3: " << p3 << "\n p4: "<<p4<<endl;

    polynomial p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16;
    double c;
    cout <<"Wczytywanie wielomianow: podaj stopien i wspolczynniki od najmniej znaczacego\n";
    cout <<"p7 = p5 + p6   p5 += p6  <--Podaj p5 i p6\n";
    cin >> p5 >>p6;
    p7 = p5 + p6;
    p5 += p6;
    cout <<"p7 = " <<p7<<"      p5 = "<< p5 <<"\np10 = p8 - p9   p8 -= p9   <--Podaj p8 i p9\n";
    cin >> p8 >> p9;
    p10 = p8 - p9;
    p8-=p9;
    cout <<"p10 = " <<p10<<"     p8 = "<<p8<<"\np13 = p11 * p12   p11 *= p12  <--Podaj p11 i p12\n";
    cin >> p11 >> p12;
    p13 = p11 * p12;
    p11*=p12;
    cout <<"p13 = "<< p13<<"     p11 = "<<p11 << "\np15 = p14 * c   p14 *= c   <--Podaj p14 i c\n";
    cin >> p14 >> c;
    p15 = p14 * c;
    p14*=c;
    cout <<"p15 = "<< p15<<"     p14 = "<<p14 <<"\n";


    cout <<"Podaj wielomian do testow operatorow () []\n";
    cin >> p16;
    cout << "p16(2): " <<p16(2.0)<< "\np16[0]: " << p16[0]<<"\npodaj numer wsplczynnika p16 (<=" <<p16.getDegree()<<") i jego nowa wartosc\n";
    int i, j;
    cin >> i >> j;
    p16[i] = j;
    cout << "p16[" <<i<<"]: "<<p16[i]<<endl;
}
