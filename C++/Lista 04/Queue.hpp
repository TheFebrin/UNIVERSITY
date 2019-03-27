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

  /* operatory przypisania */
  Queue &operator=(const Queue &k); // kopiujacy
  Queue &operator=(Queue &&k); // przenoszacy
  ~Queue();

 /* funkcje */
  string pop();
  string front();

  void insert(string x);
  void print_queue();

  int size();
  bool isEmpty();
  bool isFull();
};
