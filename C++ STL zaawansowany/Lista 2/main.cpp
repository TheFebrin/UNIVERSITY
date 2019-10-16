/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;

class ProstaKlasa{
    private:
        uint64_t count = 1;
        unique_ptr<uint64_t[]> arr;
        vector < int > Primes;
        int n;

    public:
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
        ProstaKlasa(int n)
        {
            gen_primes();

            this->n = n;
            arr = make_unique<uint64_t[]> (n);
            
            for(int i = 0; i < n; i ++)
            {
              arr[ i ] = count;
            }
        }

        void foo(int i, int m)
        {
          if(i >= m) return;
          int rand_int = rand() % n;
          
          while(rand_int --)
          {
            arr[rand() % n] *= Primes[i];
          }

          foo(i + 1, m);
        }

        void print_all()
        {
          for(int i = 0; i < n; i ++)
          {
            cout << arr[ i ] << " ";
          }
          cout << endl;
        }
};

class LineWriter
{
  private:
    ofstream* o;
    vector< shared_ptr < ofstream > > FileList;

  public:
    LineWriter()
    {
      o = new ofstream("plik.txt");
    }

    ~LineWriter()
    {
      o->close();
    }

    void write_to_file(vector < string > s)
    {
      for(string a: s)
      { 
        // o->write (a.c_str(), sizeof(char)*a.size());
        *o << a << endl;
      }
      o->close();
    }

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
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ProstaKlasa P = ProstaKlasa(5);
    P.foo(1, 10);
    P.print_all();



    LineWriter l = LineWriter();
    vector < string > S = {"abc", "def", "ghi"};
    l.write_to_file(S);
    l.test_file_list();



    // OLD, problem with dangling pointer
    // PROBLEM: ref will point to undefined data!

    int* ptr = new int(10);
    int* ref = ptr;
    delete ptr;

    // NEW
    // SOLUTION: check expired() or lock() to determine if pointer is valid

    // empty definition
    shared_ptr< int > sptr;

    // takes ownership of pointer
    sptr.reset(new int);
    *sptr = 10;

    // get pointer to data without taking ownership
    std::weak_ptr< int > weak1 = sptr;

    // deletes managed object, acquires new pointer
    sptr.reset(new int);
    *sptr = 5;

    // get pointer to new data without taking ownership
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
