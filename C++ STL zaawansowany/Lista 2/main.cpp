/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;

class Licznik{
    private:

    public:
        uint64_t count = 1;

        Licznik()
        {
          
        }
};

vector < int > Primes;
void gen_primes()
{
  const int size = 1000000;
  vector < bool > p(size, true);
  for(int i = 2; i * i <= size; i ++)
  { 
    if(p[i])
    {
      for(int j = i * i; j <= size; j += i)
      {
        p[j] = false;
      }
      Primes.push_back(i);
    }
  }
}

void foo(int i, int m, unique_ptr<Licznik[]> &arr, int n)
{
  if(i >= m) return;
  int rand_int = rand() % n;
  
  while(rand_int --)
  {
    arr[rand() % n].count *= Primes[i];
  }

  foo(i + 1, m, arr, n);
}

unique_ptr<Licznik[]>  write(unique_ptr<Licznik[]> arr, int n)
{
  for(int i = 0; i < n; i ++)
  {
    cout << arr[ i ].count << " ";
  }
  cout << endl;
  return arr;
}

// --------------------------------------------


class LineWriter
{
  private:
    ofstream* o;
    vector< shared_ptr < ofstream > > FileList;

  public:
    LineWriter()
    {
      o = new ofstream("plik.txt", ios::app);
    }

    ~LineWriter()
    {
      o->close();
      free(o);
    }

    void write_to_file(vector < string > s)
    {
      for(string a: s)
      { 
        // o->write (a.c_str(), sizeof(char)*a.size());
        *o << a << endl;
      }
    }

  /*
    void test_file_list()
    {
      string filename = "plik.txt";
      FileList.push_back(make_shared<ofstream>(filename.c_str(), ios::app));
      FileList.push_back(make_shared<ofstream>(filename.c_str(), ios::app));
      FileList.push_back(make_shared<ofstream>(filename.c_str(), ios::app));

      int no = 1;
      for(auto w: FileList)
      {
        string text = "wkaznik" + to_string(no ++);
        *w << text << endl;
        w->close();
      }
    }
    */
};



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(NULL));

    gen_primes();
    int n = 5;
    int m = 3;
    
    unique_ptr<Licznik[]> ptr_L {new Licznik[n]};
    foo(1, m, ptr_L, n);
    write(move(ptr_L), n);

   

    LineWriter l = LineWriter();
    vector < string > S = {"Hey", "ABC"};
    l.write_to_file(S);
    //l.test_file_list();

    auto liner1 = shared_ptr<LineWriter>(new LineWriter());
    auto liner2 = liner1;
    auto liner3 = liner1;
    auto liner4 = liner1;


    S[0] = "Liner 1";
    liner1->write_to_file(S);
    S[0] = "Liner 2";
    liner2->write_to_file(S);
    S[0] = "Liner 3";
    liner3->write_to_file(S);
    S[0] = "Liner 4";
    liner4->write_to_file(S);




    shared_ptr< int > sptr;

    sptr.reset(new int);
    *sptr = 10;

    weak_ptr< int > weak1 = sptr;

    sptr.reset(new int);
    *sptr = 5;

    weak_ptr< int > weak2 = sptr;

    // weak1 is expired!
    if(auto tmp = weak1.lock())
        cout << *tmp << '\n';
    else
        cout << "weak1 is expired\n";

    // weak2 points to new data (5)
    if(auto tmp = weak2.lock())
        cout << *tmp << '\n';
    else
        cout << "weak2 is expired\n";




    return 0;
}
