
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>

 // To execute C, please define "int main()

 typedef struct node
   {
     int val;
     int size;
     struct node *left;  //<---
     struct node *right;
   } Node;


 Node* newNode(int val, int size)
 {
    Node *nowy = (Node*)malloc(sizeof(Node));

    nowy->val = val;
    nowy->size = size;
    nowy->left = NULL;
    nowy->right = NULL;

   return nowy;
 }

 int wysokoscS(Node*root)
 {
   printf("%d \n",root->val);
   int x=0;
   int y=0;
   if(root == NULL)
     return 0;
   if(root->right!=NULL)
     x= wysokoscS(root->right);
   if(root->left!=NULL)
     y= wysokoscS(root->left);

   if(x>y) //<----
     return x+1;
   else
     return y+1;
 }

 int ile;
 void DFS(Node *root , int ileTamChcemy)
   {
     printf("%d %d\n",root->val, root->size);
     if(root->val >= ileTamChcemy)ile++;
     if(root->right != NULL) DFS(root->right , ileTamChcemy);
     if(root->left != NULL) DFS(root->left , ileTamChcemy);
   }



 /*
 int wysokosc(Node *root)
 {
     int H=0;
     if(root == NULL) return 0;
     else
     {
       H++;
       if(root->right != NULL)H = max(wysokosc(root->right), H);
       if(root->left != NULL) H = max(wysokosc(root->left), H);
     }
   return H;
 }*/

 int main()
 {
   // ios_base::sync_with_stdio(0);

    Node *root = newNode(1,5);  //<- tworze roota

     Node *a = newNode(2,3);
     Node *b = newNode(3,1);
     Node *c = newNode(4,1);
     Node *d = newNode(5,1);
     Node *e = newNode(6,1);
     Node *f = newNode(7,1);

   root->right=b; // == *root.right=b;
   root->left=a;
   a->left=c;
   a->right=d;
   d->right =e;
   e->right = f;

   DFS(root, 0);
   printf("\n\n Ilosc %d\n\n", ile);
   printf("\n\n%d", wysokoscS(root));

   return 0;
 }



 /*jesli size danego wierzcholka =1 to jesli value > a to zwroc 1
 else zwroc elementy wieksze od a z lewego + elementy wieksze od a z prawego poddrzewa*/
