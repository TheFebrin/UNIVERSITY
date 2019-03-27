#include <bits/stdc++.h>
using namespace std;

#include "Queue.hpp"

int main()
{
    bool run = true;
    char c;
    int n;

    cout << "Queue size: ";
    cin >> n;

    Queue *k;
    k = new Queue(n);

    while (run){

        cout << "\n";
        cout << "i - insert \n"
             << "p - pop \n"
             << "f - front \n"
             << "s - size \n"
             << "z - print Queue \n"
             << "q - quit \n";
        cout << "\n";

        cin >> c;

        system("clear");

        switch (c){

            case 'i':
            {
                cout << "Insert something: \n";
                string x;
                cin >> x;
                k->insert(x);
                cout << "Added: " << x << "\n";
                break;
            }

            case 'p':
            {
                cout << "Deleted: " << k->pop() << "\n";
                break;
            }

            case 'f':
            {
                cout << "Front: " << k->front() << "\n";
                break;
            }

            case 's':
            {
                cout << "Size: " << k->size() << "\n";
                break;
            }

            case 'z':
            {
                k->print_queue();
                cout << "\n";
                break;
            }

            case 'q':
            {
                run = false;
                break;
            }
        }
    }

    // cout << "TEST KONSTRUKTORÓW I OPERATORÓW \n";
    // Queue *Q, *Q2;
    // Q = new Queue(initializer_list<string>{"cat", "dog", 12, 112, "dskgjndfgdjng"});
    // Q2 = new Queue(*kolejka);

    // Q->print_queue();
    // cout << "\n";

    // Q = Q2;

    // Q->print_queue();
    // cout << "\n";

    // Q->print_queue();

    return 0;
}
