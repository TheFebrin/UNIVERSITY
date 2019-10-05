/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;

void Zadanie1(){
  cout << "Zadanie 1: \n";
  cout << "---------------------------\n";

  //printf( "1. ??!\n" );
  cout << "1. ??!\n";
  cout << "2. ??=\n";
  cout << "3. ??(\n";
  cout << "4. ??>\n";

  cout << "---------------------------\n\n";
}

void Zadanie2(){
  cout << "Zadanie 2: \n";
  cout << "---------------------------\n";

  cout << "()(())()\")()\")()()\")()()(\")()))\")\")\"(\"()\"(\")(()\"())\")\"))\n";

  cout << "---------------------------\n\n";
}

void Zadanie3(){
  cout << "Zadanie 3: \n";
  cout << "---------------------------\n";

  using string_set = set < string >;
  string_set S{"ala", "ma", "kota", "domek"};
  for(auto x: S) cout << x << endl;

  cout << "---------------------------\n\n";
}

enum class Names : uint16_t {Adam, Ania, Bartek, Beata};
void message(Names name, string m){
  switch (name){
    case Names::Adam:
      cout << "To Adam: " << m << "\n";
      break;
    case Names::Ania:
      cout << "To Ania: " << m << "\n";
      break;
    case Names::Bartek:
      cout << "To Bartek: " << m << "\n";
      break;
    case Names::Beata:
      cout << "To Beata: " << m << "\n";
      break;
    default:
      cout << "Wrong name! \n";
  }
}
void Zadanie4(){
  cout << "Zadanie 4: \n";
  cout << "---------------------------\n";

  message(Names::Adam, "Hello!");

  cout << "---------------------------\n\n";
}


auto Lucas(int n){
  if( n == 0 ) return 2;
  if( n == 1 ) return 1;
  return(Lucas(n - 1) + Lucas(n - 2));
}

void Zadanie5(int n){
  cout << "Zadanie 5: \n";
  cout << "---------------------------\n";

  cout << n << " Lucas number: "<< Lucas( n ) << "\n";

  cout << "---------------------------\n\n";
}

void Zadanie6(double a, double b, double c){
  cout << "Zadanie 6: \n";
  cout << "---------------------------\n";

  if(auto delta {b * b - 4 * a * c}; delta == 0)
  {
    cout << -b / (2 * a) << "\n";
  }
  else if(delta > 0)
  {
    cout << "x1: " << (-b - sqrt(delta)) / (2 * a) << "\n";
    cout << "x2: " << (-b + sqrt(delta)) / (2 * a) << "\n";
  }
  else
  {
    cout << "No zeros!\n";
  }


  cout << "---------------------------\n\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    /*
      Zadanie 1. Trigraphs
      Kompilator pokazuje warning: trigraph ??! ignored, use -trigraphs to enable
      Aby dzialaly potrzebna flaga -trigraphs przy kompilacji.
      c++ main.cpp -o main -std=c++17 -trigraphs
    */
     Zadanie1();

    /*
      Zadanie 2. Raw string
    */
    Zadanie2();

    /*
      Zadanie 3. String alias, uniform initialization
      https://subscription.packtpub.com/book/application_development/9781786465184/1/ch01lvl1sec6/creating-type-aliases-and-alias-templates
    */
    Zadanie3();

    /*
      Zadanie 4. Strongly typed enum for names
      https://www.codeguru.com/cpp/cpp/article.php/c19083/C-2011-Stronglytyped-Enums.htm
    */
    Zadanie4();

    /*
      Zadanie 5. nth Lucas number
    */
    Zadanie5(10);

    /*
      Zadanie 6. Quadratic equations
    */
    Zadanie6(2,-2,-7);

    return 0;
}
