#include <bits/stdc++.h>
using namespace std;

struct osoba{
  string imie;
  string nazwisko;
  int wiek;
  int waga;
  int wzrost;
};

void najstarsza(vector < osoba > &O)
{
  osoba o = *max_element(O.begin(), O.end(),
  [](osoba a, osoba b)
  {
    return a.wiek < b.wiek;
  });
  cout << "Najstarsza: ";
  cout << o.imie << " ";
  cout << o.nazwisko << " ";
  cout << ", wiek: " << o.wiek << endl;
}

void najciezsza(vector < osoba > &O)
{
  osoba o = *max_element(O.begin(), O.end(),
  [](osoba a, osoba b)
  {
    return a.waga < b.waga;
  });
  cout << "Najciezsza: ";
  cout << o.imie << " ";
  cout << o.nazwisko << " ";
  cout << ", waga: " << o.waga << endl;
}

void najwyzsza(vector < osoba > &O)
{
  osoba o = *max_element(O.begin(), O.end(),
  [](osoba a, osoba b)
  {
    return a.wzrost < b.wzrost;
  });
  cout << "Najwyzsza: ";
  cout << o.imie << " ";
  cout << o.nazwisko << " ";
  cout << ", wzorst: " << o.wzrost << endl;
}


// ZADANIE 2 -------------------
struct Punkt{
  string nazwa;
  int x;
  int y;
  int R;
  int G;
  int B;
};

int main()
{
  osoba o1 = {"Ami", "Awa", 12, 120, 180};
  osoba o2 = {"Ber", "Bawar", 130, 40, 160};
  osoba o3 = {"Ciru", "Asni", 14, 31, 120};
  osoba o4 = {"Dom", "Amber", 112, 100, 220};
  vector < osoba > O = {o1, o2, o3, o4};

  sort(O.begin(), O.end(),
  [](osoba a, osoba b) -> bool
  {
    double a_bmi = (double)a.waga;
    a_bmi /= (double)(a.wzrost * a.wzrost);
    double b_bmi = (double)b.waga;
    b_bmi /= (double)(b.wzrost * b.wzrost);

    return a_bmi > b_bmi;
  });


  for(auto o: O)
  {
    double a_bmi = (double)o.waga;
    a_bmi /= (double)(o.wzrost * o.wzrost);
    cout << o.imie << " " << o.nazwisko;
    cout << ", BMI: " << a_bmi << endl;
  }
  cout << endl;

  najstarsza(O);
  najciezsza(O);
  najwyzsza(O);
  cout << "---------------\n";
  // ------------------------

  Punkt p1 = {"Adam", -1, 1, 100, 100, 100};
  Punkt p2 = {"Bartek", 1, -1, 200, 200, 200};
  Punkt p3 = {"Cyprian", 1, 1, 0, 0, 0};
  Punkt p4 = {"Dominik", -1, -1, 20, 30, 50};
  vector < Punkt > P = {p1, p2, p3, p4};
  vector < Punkt > V1, V2, V3, V4;

  copy_if (P.begin(), P.end(), back_inserter(V1),
        [](Punkt p)
        {
          return p.x > 0 and p.y > 0;
        });

  copy_if (P.begin(), P.end(), back_inserter(V2),
        [](Punkt p)
        {
          return p.x < 0 and p.y > 0;
        });


  copy_if (P.begin(), P.end(), back_inserter(V3),
        [](Punkt p)
        {
          return p.x < 0 and p.y < 0;
        });


  copy_if (P.begin(), P.end(), back_inserter(V4),
        [](Punkt p)
        {
          return p.x > 0 and p.y < 0;
        });

  cout << "1 cwiartka\n";
  for(auto p: V1)
    cout << p.nazwa << " " << p.x << " " << p.y << endl;
  cout << endl;

  cout << "2 cwiartka\n";
  for(auto p: V2)
    cout << p.nazwa << " " << p.x << " " << p.y << endl;
  cout << endl;

  cout << "3 cwiartka\n";
  for(auto p: V3)
    cout << p.nazwa << " " << p.x << " " << p.y << endl;
  cout << endl;

  cout << "4 cwiartka\n";
  for(auto p: V4)
    cout << p.nazwa << " " << p.x << " " << p.y << endl;
  cout << endl;


  // 0.2126*R + 0.7152*G + 0.0722*B
  auto naj = minmax_element(P.begin(), P.end(),
  [](Punkt a, Punkt b)
  {
    double val_a = 0.2126 * (double)a.R;
    val_a += 0.7152 * (double)a.G;
    val_a += 0.0722 * (double)a.B;

    double val_b = 0.2126 * (double)b.R;
    val_b += 0.7152 * (double)b.G;
    val_b += 0.0722 * (double)b.B;

    return val_a < val_b;
  });

  cout << "Najjasniejszy: \n";
  cout << naj.first->nazwa << " " << naj.first->R << " " \
  << naj.first->G << " " << naj.first->B << endl;

  cout << "Najciemniejszy: \n";
  cout << naj.second->nazwa << " " << naj.second->R << " " \
  << naj.second->G << " " << naj.second->B << endl;

  return 0;
}
