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
    if (capacity <= 0){
        throw new std::invalid_argument("Kolejka o wielkosci 0!!!\n");
    }

    this->capacity = capacity;
    queue = new string[capacity];
}

Queue::Queue(initializer_list<string> il){
    if (il.size() == 0){
        throw new std::invalid_argument("Kolejka o wielkosci 0!!!\n");
    }
    capacity = il.size();
    queue = new string[capacity];
    beg = 0;
    number_of_elements = il.size();

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

Queue::~Queue(){
    delete[] queue;
}

void Queue::insert(string x){
    if (this->isFull()){
        throw std::invalid_argument("Kolejka pelna!\n");
    }
    queue[ (beg + number_of_elements) % capacity ] = x;
    number_of_elements ++;
}

string Queue::pop(){
    if (this->isEmpty()){
        throw std::invalid_argument("Kolejka pusta!\n");
    }
    string s = front();
    beg++;
    number_of_elements--;
    return s;
}

string Queue::front(){
    if (this->isEmpty()){
        throw std::invalid_argument("kolejka jest pusta");
    }
    return queue[beg % capacity];
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

void Queue::print_queue(){
    for (int i = 0; i < number_of_elements; i++) cout << queue[i] << " ";
}
