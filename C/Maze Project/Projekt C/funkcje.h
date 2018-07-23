
//  Projekt C
//  modul funkcje
//  Created by Dawid Dieu on 14/01/2018.
/*
 .___  ___.      ___       ________   _______
 |   \/   |     /   \     |       /  |   ____|
 |  \  /  |    /  ^  \    `---/  /   |  |__
 |  |\/|  |   /  /_\  \      /  /    |   __|
 |  |  |  |  /  _____  \    /  /----.|  |____
 |__|  |__| /__/     \__\  /________||_______|

 */

#include "struktury.h"
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string) //print napisu glownego
{
    int length, x, y;
    float temp;
    
    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;
    
    length = strlen(string);
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    mvwprintw(win, y, x, "%s", string);
    refresh();
}

pair kolejka[10000000];
int p=0; //poczatek kolejki
int k=0; //koniec kolejki

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

pair przodek[100000][100000];

void push( int m, int n ) //dodaje pare do kolejki
{
    pair para;
    para.first = m;
    para.second = n;
    kolejka[k] = para;
    k = ( k + 1 ) % 10000000;
    //k++;
}

pair front()  //zwraca i usuwa pierwsza pare z kolejki
{
    pair ret = kolejka[p];
    p = ( p + 1 ) % 10000000;
    return ret;
}

bool notEmpty() //sprawdza czy kolejka jest pusta czy pelna
{
    if( p < k ) return true;
    else return false;
}
