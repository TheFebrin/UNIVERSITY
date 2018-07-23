//
//  binheap.h
//  Kopiec binarny
//
//  Created by Dawid on 05/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

#pragma once
#define BH_CMP(a, b) ((a) - (b)) /* relacja porządku */
#define BH_TYPE int /* typ elementów kopca */


#define INF 1000000000
int prawySyn=INF;
int lewySyn=INF;

 typedef struct binheap
{
    unsigned size;
    unsigned capacity;
    BH_TYPE *data;
}

binheap_t;
binheap = malloc(capacity * sizeof * binheap);

binheap_t *binheap_new(unsigned capacity);

void binheap_delete(binheap_t *heap);
bool binheap_valid(binheap_t *heap);
bool binheap_find(binheap_t *heap, BH_TYPE elem);
bool binheap_add(binheap_t *heap, BH_TYPE elem);
bool binhead_remove(binheap_t *heap, BH_TYPE elem);

void binheap_delete(binheap_t *heap)
{
    size=0;
    capacity=0;
    *heap=NULL;
}

bool binheap_valid(binheap_t *heap)
{
    if(capacity>0 && size>0) return true;
    else return false;
}

bool binheap_find(binheap_t *heap, BH_TYPE elem)
{
    for(int i=0;i<=capacity;i++)
    {
        if(binheap[i]==elem) return true;
    }
    return false;
}

bool binheap_add(binheap_t *heap, BH_TYPE elem)
{
    if(capacity<size) * = realloc(heap, capacity+1 * sizeof *heap)
    size++;
    heap[size]=elem;
    
    int index=size;
    
    while(heap[index]<heap[index/2] and index>1)
    {
        swap(heap[index],heap[index/2]);
        index/=2;
    }
    return true;
}

bool binhead_remove(binheap_t *heap, BH_TYPE elem)
{
    int pozycja;
    
    if(binheap_find==false) return false;
    else
    {
        for(int i=0;i<=capacity;i++)
        {
            if(binheap[i]==elem) pozycja=i;
        }
      
        heap[pozycja]=heap[size];
        size--;
        
        int i=1;
        int tmp=0;
        if(2*i<=dlugosc) lewySyn=heap[2*i];
        if(2*i+1<=dlugosc) prawySyn=heap[2*i+1];
        
        while(heap[i]>prawySyn and heap[i]>lewySyn)
        {
            if(heap[i]>prawySyn)
            {
                // swap(kopiec[i],kopiec[i*2]);
                tmp=heap[i];
                heap[i]=heap[i*2];
                heap[i*2]=tmp;
                i*=2;
            }
            else
            {
                swap(heap[i],heap[i*2+1]); i=2*i+1;
            }
            
            if(2*i<=dlugosc) lewySyn=heap[2*i];
            if(2*i+1<=dlugosc) prawySyn=heap[2*i+1];
        }
        
    }
}


