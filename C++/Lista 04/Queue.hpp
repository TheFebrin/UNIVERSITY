#include <bits/stdc++.h>
using namespace std;

class Queue{

private:
  int capacity, number_of_elements, beg;
  string *queue;

public:

  /* konstruktory */
  Queue();
  Queue(int capacity);
  Queue(initializer_list <string> il);
  Queue(const Queue &k);
  Queue(Queue &&k);
  ~Queue();

  /* operatory przypisania */
  Queue &operator=(const Queue &k); // kopiujacy
  Queue &operator=(Queue &&k); // przenoszacy

 /* funkcje */
  string wyciagnij();
  string sprawdz();

  void wloz(string x);
  void wypisz();

  int rozmiar();
  bool czy_pelna();
  bool czy_pusta();
};
