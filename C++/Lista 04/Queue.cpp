#include <bits/stdc++.h>
#include "Queue.hpp"


Queue::Queue(){
    beg = 0, capacity = 1, number_of_elements = 0;
    queue = new string[ capacity ];
}

Queue::Queue(int capacity){
    if (capacity <= 0){
        clog << "Zero capacity! \n";
    }
    else{
         this->capacity = capacity;
        beg = 0, number_of_elements = 0;
        queue = new string[capacity];
    }
}

Queue::Queue(initializer_list <string> list){
    if (list.size() == 0){
        clog << "Empty list! \n";
    }
    else{
        capacity = list.size();
        queue = new string[capacity];
        number_of_elements = list.size();
        beg = 0;

        int ptr = beg;
        for (auto elem : list) queue[ ptr ++ ] = elem;
    }
}


Queue::Queue(const Queue &k){
    capacity = k.capacity;
    beg = k.beg;
    number_of_elements = k.number_of_elements;

    queue = new string[capacity];
    copy(k.queue, k.queue + k.capacity, queue);
}

Queue::Queue(Queue &&k){
    capacity = k.capacity;
    queue = k.queue;
    beg = k.beg;
    number_of_elements = k.number_of_elements;

    k.capacity = 0;
    k.beg = 0;
    k.number_of_elements = 0;
    k.queue = nullptr;
}

Queue::~Queue(){
    delete[] queue;
}




Queue &Queue::operator=(const Queue &k){
    if (this == &k){
        return *this;
    }
    else{
        delete[] queue;
        capacity = k.capacity;
        queue = new string[capacity];
        beg = k.beg;
        number_of_elements = k.number_of_elements;
        copy(k.queue, k.queue + k.capacity, queue);

        return *this;
    }
}

Queue &Queue::operator=(Queue &&k){
    if (this != &k){
        delete[] queue;
        capacity = k.capacity;
        queue = k.queue;
        beg = k.beg;
        number_of_elements = k.number_of_elements;
    }
    return *this;
}




string Queue::wyciagnij(){
    if (this->czy_pusta()){
        clog << "Empty queue! \n";
        return 0;
    }
    else{
        auto del = sprawdz();
        beg ++;
        number_of_elements --;
        return del;
    }
}

string Queue::sprawdz(){
    if (this->czy_pusta()){
        clog << "Empty queue! \n";
        return 0;
    }
    else{
        beg %= capacity;
        return queue[ beg ];
    }
}




void Queue::wloz(string x){
    if (this->czy_pelna()){
        clog << "Full queue! \n";
    }
    else{
        queue[ (beg + number_of_elements) % capacity ] = x;
        number_of_elements ++;
    }
}

void Queue::wypisz(){
    // cout << "Beg: " << beg << endl;
    int i = beg, cnt = number_of_elements;
    while( cnt -- ) {
        cout << queue[ i % capacity ] << " ";
        i ++;
    }
}




int Queue::rozmiar(){
    return number_of_elements;
}

bool Queue::czy_pusta(){
    return number_of_elements == 0;
}

bool Queue::czy_pelna(){
    return capacity == number_of_elements;
}

