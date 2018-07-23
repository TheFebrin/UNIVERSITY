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
#define MAX (1000000+7)
#define INF 1000000000;
struct pair
{
    char first;
    int second;
};

struct pair wystapienia[130];

int iloscLiter=0;
int dlugosc=0;

void usun(struct pair kopiec[iloscLiter])
{
    kopiec[1]=kopiec[dlugosc];
    dlugosc--;
    int i=1;
    struct pair tmp;
    while(kopiec[i].second>kopiec[i+1].second && i<=dlugosc)
    {
        tmp= kopiec[i];
        kopiec[i]=kopiec[i+1];
        kopiec[i+1]=tmp;
        i++;
    }
}

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

/*
 int pocz=0; //poczatek kolejki
 int kon=0; //koniec kolejki
 int kolejka[MAX];
 
 void push(int m) //dodaje pare do kolejki
 {
 kolejka[kon]=m;
 kon=(kon+1)%10000000;
 }
 
 int front()  //zwraca i usuwa pierwsza pare z kolejki
 {
 int ret=kolejka[pocz];
 pocz=(pocz+1)%10000000;
 return ret;
 }
 
 bool notEmpty() //sprawdza czy kolejka jest pusta czy pelna
 {
 if(pocz<kon) return true;
 else return false;
 }
 
 int BFS(Node *Parent) //wypisywanie drzewka
 {
 int suma=0;
 while (Parent!=NULL)
 {
 push(Parent->data);
 
 printf("%d\n",Parent->data); Parent = Parent->right;
 }
 
 }
 */

int sum;
/* Function protoypes */
void printGivenLevel(struct node* root, int level);
int height(struct node* node);
struct node* newNode(int data);

/* Function to print level order traversal a tree*/
void printLevelOrder(Node* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
    {
        printGivenLevel(root, i);
    }
}//ALA MA KOTA, A KOT MA ALE.

/* Print nodes at a given level */
void printGivenLevel(Node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
    {
        sum+=root->data;
    }
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

/* Compute the "height" of a tree -- the number of
 nodes along the longest path from the root node
 down to the farthest leaf node.*/
int height(Node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
        
        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

int main(void)
{
    
    char tab[MAX];
    fgets(tab,MAX,stdin);
    
    int i=0;
    while(tab[i]!='\0')  //sprawdzam ile razy dany char wystapil w tekscie
    {
        int tmp=tab[i];
        wystapienia[tmp].first=tab[i];
        wystapienia[tmp].second++;
        i++;
    }
    
    
    for(int j=0;j<130;j++) //sprawdzam ile unikalnych liter wystapilo
    {
        if(wystapienia[j].second!=0) iloscLiter++;
    }
    
    struct pair WystapieniaZnakow[iloscLiter];  //tworze priority queue dla par t.ze <char, ilosc wystapienia>
    
    for(int j=0;j<130;j++) //wrzucam do powyzej utworzonej kolejki moje pary
    {
        if(wystapienia[j].second!=0 && wystapienia[j].second!='\n' && wystapienia[j].second!='\0')
        {
            dodaj(WystapieniaZnakow, wystapienia[j]);
        }
    }
    
    usun(WystapieniaZnakow); //usuwam dziwny nieporzadany znak co jest na samej gorze
    
    Node *nodes[iloscLiter];
    
    for(int k=1;k<iloscLiter;k++) //Tworze nowa kolejke typu Node, zebym mogl tam wrzucac i wyrzucac rzeczy
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
    printLevelOrder(nodes[1]);
    
    printf("%d\n",sum-nodes[1]->data);
    return 0;
}

