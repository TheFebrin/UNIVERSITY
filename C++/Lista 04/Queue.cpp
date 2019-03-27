#include <bits/stdc++.h>
#include "Queue.hpp"


Queue::Queue(){
    capacity = 1;
    queue = new string[capacity];
    beg = 0;
    number_of_elements = 0;
}

Queue::Queue(int capacity) : Queue()
{
    if (capacity <= 0) throw new invalid_argument("Zero capacity! \n");
    this->capacity = capacity;
    queue = new string[capacity];
}

Queue::Queue(initializer_list<string> il){
    if (il.size() == 0) throw new invalid_argument("Empty list! \n");

    capacity = il.size();
    queue = new string[capacity];
    number_of_elements = il.size();

    beg = 0;
    for (auto elem : il){
        queue[beg % capacity] = elem;
        beg ++;
    }
}


Queue::Queue(const Queue &k){
    capacity = k.capacity;
    queue = new string[capacity];
    beg = k.beg;
    number_of_elements = k.number_of_elements;
    copy(k.queue, k.queue + k.capacity, queue);
}

Queue::Queue(Queue &&k)
    : capacity(0), queue(nullptr), beg(0), number_of_elements(0)
{
    capacity = k.capacity;
    queue = k.queue;
    beg = k.beg;
    number_of_elements = k.number_of_elements;

    k.capacity = 0;
    k.queue = nullptr;
    k.beg = 0;
    k.number_of_elements = 0;
}

Queue::~Queue(){
    delete[] queue;
}




Queue &Queue::operator=(const Queue &k){
    if (this != &k){
        delete[] queue;
        capacity = k.capacity;
        queue = new string[capacity];
        beg = k.beg;
        number_of_elements = k.number_of_elements;
        copy(k.queue, k.queue + k.capacity, queue);
    }
    return *this;
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




string Queue::pop(){
    auto del = front();
    if (this->isEmpty()) throw invalid_argument("Empty queue! \n");
    beg++;
    number_of_elements --;
    return del;
}

string Queue::front(){
    if (this->isEmpty()) throw invalid_argument("Empty queue! \n");
    return queue[beg % capacity];
}




void Queue::insert(string x){
    if (this->isFull()) throw invalid_argument("Full queue! \n");
    queue[ (beg + number_of_elements) % capacity ] = x;
    number_of_elements ++;
}

void Queue::print_queue(){
    for (int i = 0; i < number_of_elements; i ++) cout << queue[ i ] << " ";
}




int Queue::size(){
    return number_of_elements;
}

bool Queue::isEmpty(){
    return number_of_elements == 0;
}

bool Queue::isFull(){
    return capacity == number_of_elements;
}

