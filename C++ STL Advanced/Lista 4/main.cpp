#include <bits/stdc++.h>
using namespace std;

vector < double > V;
list < string > L;
set < int > S;

void print_vector(vector < double > V)
{
  for(auto a: V) cout << a << " ";
  cout << endl;
}


void showlist(list <string> l)
{
    list <string> :: iterator it;
    for(it = l.begin(); it != l.end(); it ++)
        cout << *it << " ";
    cout << '\n';
}

void showset(set < int > S)
{
  for(auto a: S) cout << a << " ";
  cout << endl;
}

void fill_containers(int n)
{
  srand(time(NULL));
  while( n -- )
  {
    V.push_back(rand() % 1000 - 500);
    L.push_back(string(1, 'a' + rand() % 26));
    S.insert(rand() % 1000 - 500);
  }
}


int main()
{
  fill_containers(5);

  // 1. Wypisz wszystkie wartości z zadanego zakresu (większe od a i mniejsze od b).
  cout << "Vector V: \n";
  print_vector(V);
  cout << "\n";
  cout << "List L: \n";
  showlist(L);
  cout << "\n";
  cout << "Set S: \n";
  showset(S);
  cout << "\n";

  int a = -300, b = 300;
  [](vector < double > V, int a, int b){
    cout << a << " < V[i] < " << b << "\n";
    for(auto v: V){
      if(v > a and v < b) cout << v << " ";
    }
    cout << "\n\n";
  }(V, a, b);

  string sa = "h", sb = "z";
  [](list < string > L, string sa, string sb){
    cout << sa << " < L[i] < " << sb << "\n";
    for(auto l: L){
      if(l > sa and l < sb) cout << l << " ";
    }
    cout << "\n\n";
  }(L, sa, sb);

  // 2. Wypisz co k-tą wartość zaczynając od pozycji p-tej.
  int p = 2, k = 2;
  [](vector < double > V, int p, int k){
    if(p >= V.size()) return;
    cout << "V[i] : i >= p and i % k == 0\n";
    for(int i = p; i < V.size(); i ++){
      if((i - p) % k == 0) cout << V[ i ] << " ";
    }
    cout << "\n\n";
  }(V, p, k);


  [](set < int > V, int p, int k){
    if(p >= S.size() or  p < 0 ) return;
    cout << "Same for set: \n";
    auto it = S.begin();
    int no = 0;
    while( p -- ) it ++;
    while(it != S.end())
    {
      if(no % k == 0) cout << *it << " ";
      it ++; no ++;
    }
    cout << "\n\n";
  }(S, p, k);

  // 3. Wyznacz średnią arytmetyczną (dotyczy kolekcji z liczbami).
  [](vector < double > V)
  {
    double sum = 0;
    for(auto v: V) sum += v;
    sum /= (double)V.size();
    return sum;
  }(V);

  [](set < int > V)
  {
    double sum = 0;
    for(auto s: S) sum += s;
    sum /= (double)S.size();
    return sum;
  }(S);

  // 4. Wyznacz element minimalny i maksymalny (zwróć parę iteratorów).
  auto mi_and_mx =  [](vector < double > V)
                    {
                      cout << "Min and Max iterator of V:\n";
                      auto mi = V.begin();
                      auto mx = V.begin();
                      for(auto it = V.begin(); it != V.end(); it ++)
                      {
                        if(*it > *mx) mx = it;
                        if(*it < *mi) mi = it;
                      }
                      return make_pair(mi, mx);
                    }(V);
  cout << "Min: " << *mi_and_mx.first << "\n";
  cout << "Max: " << *mi_and_mx.second << "\n";
  cout << "\n";

  auto mi_and_mx_set =  [](set < int > S)
                        {
                          cout << "Min and Max iterator of S:\n";
                          auto mi = S.begin();
                          auto mx = S.begin();
                          for(auto it = S.begin(); it != S.end(); it ++)
                          {
                            if(*it > *mx) mx = it;
                            if(*it < *mi) mi = it;
                          }
                          return make_pair(mi, mx);
                        }(S);
  cout << "Min: " << *mi_and_mx_set.first << "\n";
  cout << "Max: " << *mi_and_mx_set.second << "\n";
  cout << "\n";     
  
  // 5. Wyznacz sumę/konkatenację wszystkich elementów.
  [](vector < double > V)
  {
    cout << "Sum of V:\n";
    double sum = 0;
    for(auto v: V) sum += v;
    cout << sum;
    cout << "\n\n";
  }(V);

  [](set < int > V)
  {
    cout << "Sum of S:\n";
    double sum = 0;
    for(auto s: S) sum += s;
    cout << sum;
    cout << "\n\n";
  }(S);

  [](list < string > l)
  {
    cout << "Concatenation of L:\n";
    string sum = "";
    list <string> :: iterator it;
    for(it = l.begin(); it != l.end(); it ++)
        sum += *it;
    cout << sum;
    cout << "\n\n";
  }(L);



  return 0;
}
