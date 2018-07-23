//
//  main.c
//  Reorganizacja drzewa
//
//  Created by Dawid on 22/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *parent;
    
    struct node *one;
    struct node *two;
    struct node *three;
    struct node *four;
    struct node *five;
    struct node *six;
    struct node *seven;
    struct node *eight;
    struct node *nine;
    struct node *ten;
};
typedef struct node Node;


Node* newNode(int data)
{
    Node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->parent=NULL;
    
    node->one = NULL;
    node->two = NULL;
    node->three=NULL;
    node->four = NULL;
    node->five = NULL;
    node->six=NULL;
    node->seven = NULL;
    node->eight = NULL;
    node->nine=NULL;
    node->ten=NULL;
    
    return(node);
}

void DFS(Node *node, int deep)
{
    deep++;
    if(node->data==2)
    {
        printf("%d\n",deep);
        return;
    }
    
    if(node->one!=NULL)
    {
        DFS(node->one,deep);
    }
    if(node->two!=NULL)
    {
        DFS(node->two,deep);
    }
    if(node->three!=NULL)
    {
        DFS(node->three,deep);
    }
    if(node->four!=NULL)
    {
        DFS(node->four,deep);
    }
    if(node->five!=NULL)
    {
        DFS(node->five,deep);
    }
    if(node->six!=NULL)
    {
        DFS(node->six,deep);
    }
    if(node->seven!=NULL)
    {
        DFS(node->seven,deep);
    }
    if(node->eight!=NULL)
    {
        DFS(node->eight,deep);
    }
    if(node->nine!=NULL)
    {
        DFS(node->nine,deep);
    }
    if(node->ten!=NULL)
    {
        DFS(node->three,deep);
    }
    
    
}
int main(int argc, const char * argv[])
{
    char operation;
    int newNodeValue;
    int parentValue;
    
    Node *tab[1000000];
    Node *root=newNode(1);
    tab[1]=root;
    
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf(" %c %d %d",&operation,&newNodeValue,&parentValue);
        if(operation=='d')
        {
            tab[newNodeValue]=newNode(newNodeValue);
            if(tab[parentValue]->one==NULL) {tab[parentValue]->one=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                else if(tab[parentValue]->two==NULL){tab[parentValue]->two=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                    else if(tab[parentValue]->three==NULL){tab[parentValue]->three=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                        else if(tab[parentValue]->four==NULL){tab[parentValue]->four=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                            else if(tab[parentValue]->five==NULL){tab[parentValue]->five=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                                else if(tab[parentValue]->six==NULL){tab[parentValue]->six=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                                    else if(tab[parentValue]->seven==NULL){tab[parentValue]->seven=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                                        else if(tab[parentValue]->eight==NULL){tab[parentValue]->eight=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                                            else if(tab[parentValue]->nine==NULL){tab[parentValue]->nine=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
                                                else if(tab[parentValue]->ten==NULL){tab[parentValue]->ten=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            
        }
        else if(operation=='p')
        {
            if(tab[newNodeValue]->parent->one==tab[newNodeValue]) tab[newNodeValue]->parent->one=NULL;
            if(tab[newNodeValue]->parent->two==tab[newNodeValue]) tab[newNodeValue]->parent->two=NULL;
            if(tab[newNodeValue]->parent->three==tab[newNodeValue]) tab[newNodeValue]->parent->three=NULL;
            if(tab[newNodeValue]->parent->four==tab[newNodeValue]) tab[newNodeValue]->parent->four=NULL;
            if(tab[newNodeValue]->parent->five==tab[newNodeValue]) tab[newNodeValue]->parent->five=NULL;
            if(tab[newNodeValue]->parent->six==tab[newNodeValue]) tab[newNodeValue]->parent->six=NULL;
            if(tab[newNodeValue]->parent->seven==tab[newNodeValue]) tab[newNodeValue]->parent->six=NULL;
            if(tab[newNodeValue]->parent->eight==tab[newNodeValue]) tab[newNodeValue]->parent->eight=NULL;
            if(tab[newNodeValue]->parent->nine==tab[newNodeValue]) tab[newNodeValue]->parent->nine=NULL;
            if(tab[newNodeValue]->parent->ten==tab[newNodeValue]) tab[newNodeValue]->parent->ten=NULL;
                
            tab[newNodeValue]->parent=tab[parentValue];
            
            if(tab[parentValue]->one==NULL) {tab[parentValue]->one=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->two==NULL){tab[parentValue]->two=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->three==NULL){tab[parentValue]->three=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->four==NULL){tab[parentValue]->four=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->five==NULL){tab[parentValue]->five=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->six==NULL){tab[parentValue]->six=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->seven==NULL){tab[parentValue]->seven=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->eight==NULL){tab[parentValue]->eight=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->nine==NULL){tab[parentValue]->nine=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            else if(tab[parentValue]->ten==NULL){tab[parentValue]->ten=tab[newNodeValue]; tab[newNodeValue]->parent=tab[parentValue];}
            
        }
        
    }
    DFS(tab[1],0);
    return 0;
}
