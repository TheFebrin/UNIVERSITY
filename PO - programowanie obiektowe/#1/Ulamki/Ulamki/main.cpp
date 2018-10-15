#include <bits/stdc++.h>
using namespace std;

typedef struct Ulamki
{
    int licznik;
    int mianownik;
}Ulamek;

int NWD(int a, int b)
{
    while(b)swap(a %= b, b);
    return a;
}
int NWW(int a, int b)
{
    return(a*b/NWD(a,b));
}

Ulamek dodaj(Ulamek a, Ulamek b);
Ulamek pomnoz(Ulamek a, Ulamek b);
Ulamek odejmij(Ulamek a, Ulamek b);
Ulamek podziel(Ulamek a, Ulamek b);

Ulamek *dodaj2(Ulamek a, Ulamek b);
Ulamek *pomnoz2(Ulamek a, Ulamek b);
Ulamek *odejmij2(Ulamek a, Ulamek b);
Ulamek *podziel2(Ulamek a, Ulamek b);

int main()
{
    ios_base::sync_with_stdio(0);
    Ulamek a,b;
    a.licznik = 1; a.mianownik = 2;
    b.licznik = 2; b.mianownik = 3;
    cout<<"Rozwazam : "<<a.licznik<<" / "<<a.mianownik<<"   oraz   "<<b.licznik<<" / "<<b.mianownik<<"\n\n";
    cout<<"Dodawanie: "<<dodaj(a, b).licznik <<" / " <<dodaj(a, b).mianownik<<"\n";
    cout<<"Mnozenie: "<<pomnoz(a, b).licznik << " / "<<pomnoz(a, b).mianownik<<"\n";
    cout<<"Odejmowanie: "<<odejmij(a, b).licznik <<" / " <<odejmij(a, b).mianownik<<"\n";
    cout<<"Dzielenie: "<<podziel(a, b).licznik <<" / " <<podziel(a, b).mianownik<<"\n";
    cout<<"\nMetoda wskaznikowa: \n\n";
    cout<<"Dodawanie: "<<dodaj2(a, b)->licznik <<" / " <<dodaj(a, b).mianownik<<"\n";
    cout<<"Mnozenie: "<<pomnoz2(a, b)->licznik << " / "<<pomnoz2(a, b)->mianownik<<"\n";
    cout<<"Odejmowanie: "<<odejmij2(a, b)->licznik <<" / " <<odejmij2(a, b)->mianownik<<"\n";
    cout<<"Dzielenie: "<<podziel2(a, b)->licznik <<" / " <<podziel2(a, b)->mianownik<<"\n";
    
    

    
    return 0;
}

void skroc(Ulamek &a)
{
    int nwd  = NWD(a.licznik, a.mianownik);
    a.licznik /= nwd;
    a.mianownik /= nwd;
}

Ulamek dodaj(Ulamek a, Ulamek b)
{
    int WspMian = NWW(a.mianownik, b.mianownik);
    a.licznik *= WspMian / a.mianownik;
    b.licznik *= WspMian / b.mianownik;
    b.mianownik = a.mianownik = WspMian;
    a.licznik +=b.licznik;
    skroc(a);
    return a;
}

Ulamek pomnoz(Ulamek a, Ulamek b)
{
    a.licznik *= b.licznik;
    a.mianownik *= b.mianownik;
    skroc(a);
    return a;
}

Ulamek odejmij(Ulamek a, Ulamek b)
{
    int WspMian = NWW(a.mianownik, b.mianownik);
    a.licznik *= WspMian / a.mianownik;
    b.licznik *= WspMian / b.mianownik;
    b.mianownik = a.mianownik = WspMian;
    a.licznik -=b.licznik;
   if(a.licznik > 0) skroc(a);
    else
    {
        a.licznik *= -1;
        skroc(a);
        a.licznik*=-1;
    }
    return a;
}

Ulamek podziel(Ulamek a, Ulamek b)
{
    swap(b.licznik, b.mianownik);
    return pomnoz(a, b);
}

Ulamek *dodaj2(Ulamek a, Ulamek b)
{
    Ulamek *wynik = new Ulamek;
    *wynik=dodaj(a, b);
    return wynik;
}

Ulamek *pomnoz2(Ulamek a, Ulamek b)
{
    {
        Ulamek *wynik = new Ulamek;
        *wynik=pomnoz(a, b);
        return wynik;
    }
}

Ulamek *odejmij2(Ulamek a, Ulamek b)
{
    Ulamek *wynik = new Ulamek;
    *wynik=odejmij(a, b);
    return wynik;
}

Ulamek *podziel2(Ulamek a, Ulamek b)
{
    Ulamek *wynik = new Ulamek;
    *wynik=podziel(a, b);
    return wynik;
}
