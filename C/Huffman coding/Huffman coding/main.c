//
//  main.c
//  Huffman coding
//
//  Created by Dawid on 17/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//ALA MA KOTA, A KOT MA ALE.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000000

struct pair
{
    char first;
    int second;
};

struct pair wystapienia[130];

int iloscLiter=0;
int dlugosc=0;

void dodaj( struct pair kopiec[iloscLiter], struct pair a)
{
    dlugosc++;
    kopiec[dlugosc]=a;
    struct pair tmp;
    int index=dlugosc;
    while(kopiec[index].second<kopiec[index-1].second && index>1)
    {
        tmp= kopiec[index];
        kopiec[index]=kopiec[index-1];
        kopiec[index-1]=tmp;
        index--;
    }
}


struct node
{
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node Node;


Node* newNode(int data)
{
    Node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}
void usunNode(Node *kopiec[iloscLiter])
{
    if(kopiec[dlugosc]!=NULL)
    {
        kopiec[1]=kopiec[dlugosc];
        dlugosc--;
        int i=1;
        Node *tmp;
        while(kopiec[i]!=NULL && i<=dlugosc && kopiec[i]->data>kopiec[i+1]->data)
        {
            tmp=kopiec[i];
            kopiec[i]=kopiec[i+1];
            kopiec[i+1]=tmp;
            i++;
        }
    }
    
}

void dodajNode(Node *kopiec[iloscLiter], Node *a)
{
    dlugosc++;
    kopiec[dlugosc]=a;
    Node *tmp;
    int index=dlugosc;
    while(kopiec[index]!=NULL && index>1 && kopiec[index]->data<kopiec[index-1]->data)
    {
        tmp=kopiec[index];
        kopiec[index]=kopiec[index-1];
        kopiec[index-1]=tmp;
        index--;
    }
    
}

int sum;
void DFS(Node *node)
{
    sum+=node->data;
    if(node->left!=NULL)
    {
        DFS(node->left);
    }
    if(node->right!=NULL)
    {
        DFS(node->right);
    }
}

int main(void)
{
    struct pair trr;
    trr.first='0';
    trr.second=0;
    for(int q=0;q<130;q++) wystapienia[q]=trr;
    //  printf("ilosc1: %d\n",iloscLiter);
    
    char tab[MAX];
    char x;
    int u=0;
   while(scanf("%c", &x) != -1)
    {
        tab[u]=x;
        u++;
    }
    
    int i=0;
    while(tab[i]!='\0')  //sprawdzam ile razy dany char wystapil w tekscie
    {
        int tmp=tab[i];
        wystapienia[tmp].first=tab[i];
        wystapienia[tmp].second++;
        i++;
    }
    // printf("ilosc2: %d\n",iloscLiter);
    for(int j=0;j<130;j++) //sprawdzam ile unikalnych liter wystapilo
    {
        if(wystapienia[j].second!=0)
        {
            iloscLiter++;
        }
    }
    //   printf("ilosc3: %d\n",iloscLiter);
    
    struct pair WystapieniaZnakow[iloscLiter];  //tworze priority queue dla par t.ze <char, ilosc wystapienia>
    
    for(int j=0;j<130;j++) //wrzucam do powyzej utworzonej kolejki moje pary
    {
        if(wystapienia[j].second!=0 && wystapienia[j].first!='\0')
        {
            //printf("dodaje: %c %d\n",wystapienia[j].first,wystapienia[j].second);
            dodaj(WystapieniaZnakow, wystapienia[j]);
        }
    }
    
    
    Node *nodes[iloscLiter+1];
    
    for(int k=1;k<=iloscLiter;k++) //Tworze nowa kolejke typu Node, zebym mogl tam wrzucac i wyrzucac rzeczy
    {
        nodes[k]=newNode(WystapieniaZnakow[k].second);
    }
    while(dlugosc>1) //dopoki wiecej niz 1 Node jest w kolejce lacze je w pary
    {
        Node*Leftson=nodes[1];
        usunNode(nodes);
        Node*RightSon=nodes[1];
        usunNode(nodes);
        Node *Parent=newNode(Leftson->data+RightSon->data);
        Parent->left=Leftson;
        Parent->right=RightSon;
        dodajNode(nodes, Parent);
    }
    DFS(nodes[1]);
    //  printf("ilosc: %d\n",iloscLiter);
    if(iloscLiter==1)
        printf("%d\n",sum);
    else printf("%d\n",sum-nodes[1]->data);
    return 0;
}

