//
//  main.c
//  Obraz PGM
//
//  Created by Dawid on 10/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[])
{
   
    int x=atoi(argv[1]);
    int y=atoi(argv[2]);
 
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            printf("%3d ",i*j);
        }
        printf("\n");
    }
    
    return 0;
}
