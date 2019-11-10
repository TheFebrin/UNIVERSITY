#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
/**Dawid Dieu**/

void print_bin(unsigned n) //print bin number
{
    int t[n];
    int i=0;

    while(n>0)
    {
        t[i]=n%2;
        n/=2;
        i++;
    }
    int j;

    for(j=i-1; j>=0; j--)
    {
        printf("%d",t[j]);
    }

}

void unary(unsigned n)  //p as unar
{
    int i=0;
    for( i=0; i<n; i++)
        printf("1");
}


void encode(unsigned number, unsigned k)
{
    unsigned power=pow(2,k);
    unsigned q=number%power;
    unsigned p=(number-q)/power;

    unary(p);
    printf("0 ");

    unsigned qLength=floor(log2(q));
    int i;
    for(i=1; i<k-qLength; i++) printf("0");
    print_bin(q);

}

unsigned countQ(char *str)
{
    int length=strlen(str)-1;
    int number=0;
    int i=0;


    if(str!=NULL && length>=0)
    {
        while(length>=0)
        {

            number+=(str[i]-'0')*pow(2,length);
            //printf("\n str[i] to: %d, a number to: %d\n",str[i],number);
            length--;
            i++;
            //printf("%d\n",length);

        }
    }

    return number;
}
void decode(unsigned code, unsigned k, unsigned q)
{
    int p=0;
    while(code>1)
    {
        p++;
        code/=10;
    }
    unsigned power=pow(2,k);
    unsigned number=p*power+q;  //n=p*2^k+q

    /*LOOKING FOR Q*/
    /*
    unsigned tmpNmb=0;
    for(q=1;q<10000;q++)
    {
       tmpNmb=number+q;
       if((number+(tmpNmb%power))==tmpNmb)
       {
           number+=q;
           break;
       }

    }
*/
    printf("%d",number);
    printf("\n");
    printf("\nLiczba  %d w zapisie binarnym to: ",number);
    print_bin(number);


}

int toNumber(char *str)  //converts string int to int int
{
    int length=strlen(str)-1;
    int number=0;
    int i=0;
    //printf("\nDlugosc poczatkowa to: %d\n",length);
    if(str!=NULL && length>=0)
    {
        while(length>=0)
        {

            number+=(str[i]-'0')*pow(10,length);
            //printf("\n str[i] to: %d, a number to: %d\n",str[i],number);
            length--;
            i++;

        }
    }
    return number;
}

unsigned countK(char *str) //returns number of bits
{
    return strlen(str);
}



int main(int argc, char** argv)
{
//gcc -g -Og -Wall -Werror kod.c
//a.exe e 13 3
//a.exe d 1111110 1


    char c=*argv[1];  // e - encode,  d-decode
    int number=toNumber(argv[2]);   //number to code


    if(c=='e')
    {
        unsigned k=*argv[3]-48;
        printf("\nLiczba  %d w zapisie binarnym to: ",number);
        print_bin(number);
        printf("\n\n");
        printf("Zakodowana kodem Rice'a dla k=%d wynosi: ",k);
        encode(number,k);
        printf("\n");
    }
    else if(c=='d')
    {
        unsigned q=countQ(argv[3]);
        unsigned k=countK(argv[3]);
        printf("\nOdkodowana liczba to: ");
        decode(number,k,q);
        printf("\n\n");
    }
    else
    {
        printf("\n\n BLEDNE WEJSCIE!\n\n");
        return 0;
    }


    return 0;
}
