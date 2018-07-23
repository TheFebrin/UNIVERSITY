
//  Projekt C
//
//  Created by Dawid Dieu on 14/01/2018.
/*
 .___  ___.      ___       ________   _______
 |   \/   |     /   \     |       /  |   ____|
 |  \  /  |    /  ^  \    `---/  /   |  |__
 |  |\/|  |   /  /_\  \      /  /    |   __|
 |  |  |  |  /  _____  \    /  /----.|  |____
 |__|  |__| /__/     \__\  /________||_______|
 
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <signal.h>



#include "funkcje.h"

//----------------------------------FUNKCJE DO GENEROWANIA LABIRYNTU--------------------------------------------------------


Node *nodes;
int width=0;
int height=0;//rozmiary labiryntu

char MAZE[1000][1000];

int init( void);
Node *linkk( Node *n );
void draw(void);

int BFS(int x, int y, WINDOW*w, int hh, int ww);

int main(void)
{
    // ///--------------------------------------------------------------------START NCURSES---------------------
    initscr();
    cbreak();
    noecho();
    start: //start label
    
    
    if(has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n click to continue\n");
        getch();
    }
    
    WINDOW *tytul=newwin(LINES-5, COLS-5, 1, 1);
    box(tytul, 0, 0);
    wrefresh(tytul);
    
    start_color();            /* Start color             */
    init_pair(1, COLOR_BLUE, COLOR_YELLOW);
    
    wattron(tytul,COLOR_PAIR(1));
    print_in_middle(tytul, LINES / 2-2, 0, 0, "THE MAZE GAME");
    wattroff(tytul, COLOR_PAIR(1));
    mvwprintw(tytul,LINES/2, COLS/3, "Press a key to continue.");
    wgetch(tytul);
    
 
    
    int xMax,yMax; //rozmiary ekranu
    yMax = (LINES - 5) ;
    xMax = (COLS - 5) ;
    
    WINDOW *menu=newwin(yMax, xMax, 1, 1);
    box(menu, 0, 0);
    wrefresh(menu);
    keypad(menu, true);
    
    //NAGLOWEK
    
    SIGWINCH;
    
    mvwprintw(menu,2,xMax/5, ".___  ___.      ___       ________   _______");
    mvwprintw(menu,3,xMax/5, "|   \\/   |     /   \\     |       /  |   ____|");
    mvwprintw(menu,4,xMax/5, "|  \\  /  |    /  ^  \\    `---/  /   |  |__");
    mvwprintw(menu,5,xMax/5, "|  |\\/|  |   /  /_\\  \\      /  /    |   __|");
    mvwprintw(menu,6,xMax/5, "|  |  |  |  /  _____  \\    /  /----.|  |___");
    mvwprintw(menu,7,xMax/5, "|__|  |__| /__/     \\__\\  /________||_______|");
    
    char *wyboryMenu[3][10];
    wyboryMenu[0][0]="1.START";
    wyboryMenu[1][0]="2.HELP";
    wyboryMenu[2][0]="3.EXIT";
    
    int wybor;
    int aktWybor=0;
    
    
    while (1)
    {
        for(int i=0;i<3;i++)    //------------------------------------------------------------WYSWIETLANIE MENU
        {
            if(i==aktWybor)wattron(menu, A_REVERSE);
            mvwprintw(menu, i+(yMax/2), xMax/2-5, *wyboryMenu[i]);
            wattroff(menu, A_REVERSE);
        }
        wybor=wgetch(menu);
        switch (wybor)
        {
            case KEY_UP:
                aktWybor--;
                if(aktWybor<0)aktWybor=2;
                break;
             case KEY_DOWN:
                aktWybor++;
                if(aktWybor>2)aktWybor=0;
                break;
            default:
                break;
        }
        if(wybor== 10) //wcisniecie ENTER
        {
            delwin(menu);
            break;
        }
    }
    
    switch (aktWybor)
    {
            ///-------------------------------------------------------CASE:  START--------------------------------------------------
        case 0:
        {
            echo();
            WINDOW*maze=newwin(yMax, xMax, 1, 1); //nowe okno do labiryntu
            box(maze, 0, 0);
            wrefresh(maze);
            
            Node *start, *last;
            
        again:
            mvwprintw(maze,yMax/2-5,xMax/3,"SELECT SIZE OF YOUR MAZE");
            mvwprintw(maze, yMax/2+2, xMax/3, "HIT ENTER TO CONFIRM");
            mvwprintw(maze, yMax/2+5, xMax/4, "NUMBERS HAVE TO BE GREATER THAN 4");
            mvwprintw(maze, yMax/2-3, xMax/3, "HEIGHT: ");
            wscanw(maze, "%d",&height);
            mvwprintw(maze, yMax/2-1, xMax/3, "WIDTH: ");
            wscanw(maze, "%d",&width);
            
            if (height%2==0) height++;
            if (width%2==0)width++;
            if (height<5 || width<5)//wrong input
            {
                wclear(maze);
                  mvwprintw(maze, yMax/2+7, xMax/4, "WRONG INPUT  FOLLOW THE INSTRUCTIONS");
                goto again;
            }
            
            
            srand( time( NULL ) );
            init();//inicjalizacja labiryntu
            start = nodes + 1 + width;
            start->parent = start;
            last = start;
            while ( ( last = linkk( last ) ) != start );
            draw( ); //rysuje labirynt
            
            
            s.tv_sec =0;
            s.tv_nsec = 50000000L;
            
            for(int i=0;i<101;i+=2) //---------------------------------   ---------ladowanie paska
            {
                mvwprintw(maze, yMax/2+7, 2, "LOADING %d %%",i);
                mvwprintw(maze, yMax/2+7, 15+i/2, "|");
                wrefresh(maze);
                nanosleep(&s, NULL);
            }
            s.tv_sec =1;
            nanosleep(&s, NULL);
            
            delwin(maze);
            
            
 ///--------------------------------------------PRINT MAZE, PORUSZANIE SIE PO LABIRYNCIE--------------------------------
            s.tv_sec=0;
            s.tv_nsec = 50000L;
            
            pair pozycja;
            pozycja.first=1; pozycja.second=1;
            pair meta;
            meta.first=height-2; meta.second=width-2;
            MAZE[meta.first][meta.second]='M';
            
            WINDOW* PrintMaze=newwin(yMax, 2*xMax/3, 1, 1);
            box(PrintMaze, 0, 0);
            wrefresh(PrintMaze);
            
            WINDOW*pasekBoczny=newwin(yMax, xMax-2, 1, 2*xMax/3);
            box(pasekBoczny, 0, 0);
            wrefresh(pasekBoczny);
            
            wmove(PrintMaze, 2, 2);
            //RYSOWANKO LABIRYNTU
            
            int hh = height;
            int ww = width;
            if(hh > yMax-3) hh = yMax-3;
            if(ww > 2*xMax/3-3) ww = 2*xMax/3-3;
            init_pair(1, COLOR_RED, COLOR_BLACK);
            for (int i = 0; i < hh; i++ )
            {
                for (int j = 0; j < ww; j++ )
                {
                    if(MAZE[i][j]=='#')wattron(PrintMaze,COLOR_PAIR(1));
                    else wattroff(PrintMaze,COLOR_PAIR(1));
                    
                    mvwprintw(PrintMaze,i+2,j+2,"%c",MAZE[i][j]);
                    wrefresh(PrintMaze);
                    nanosleep(&s, NULL);
                }
            }
            wattroff(PrintMaze,COLOR_PAIR(1));
            
            noecho();
            keypad(PrintMaze, true);
            
            int ruchy=0;
            
            mvwprintw(pasekBoczny, 2, 2, "M is your goal!");
            mvwprintw(pasekBoczny, 6, 2, "hit 'd' to run autosolve");
            mvwprintw(pasekBoczny, yMax-2, 2, "Use arrows to move");
            
            bool doszedlDoMety=false;
            init_pair(2, COLOR_BLUE, COLOR_BLACK);
            MAZE[1][1]='X';
            
            while (pozycja.first!=meta.first || pozycja.second!=meta.second) //---------------------------poruszanie sie U po labiryncie
            {
                mvwprintw(pasekBoczny, 4, 2, "Your moves: %d",ruchy);
                mvwprintw(PrintMaze, 1, 2, "Position x: %d   y: %d  ",pozycja.second,pozycja.first);
              //  mvwprintw(PrintMaze, pozycja.first+2, pozycja.second+2, "X");
                
                if(pozycja.first <= yMax-5 && pozycja.second <= 2*xMax/3-5)  //----pozycja miesci sie na ekranie
                    for (int i = 0; i < hh; i++ )
                        {
                            for (int j = 0; j < ww; j++ )
                                {
                                    wattroff(PrintMaze,COLOR_PAIR(1));
                                    wattroff(PrintMaze,COLOR_PAIR(2));
                      
                                    if(i == pozycja.first && j == pozycja.second) wattron(PrintMaze,COLOR_PAIR(2));
                    
                                    if(MAZE[i][j]=='#') wattron(PrintMaze,COLOR_PAIR(1));
                    
                                    mvwprintw(PrintMaze,i+2,j+2,"%c",MAZE[i][j]);
                                }
                        }
                wattroff(PrintMaze,COLOR_PAIR(1));
                wattroff(PrintMaze,COLOR_PAIR(2));
                
                
                wrefresh(pasekBoczny);
                wybor=wgetch(PrintMaze);
                
                switch (wybor)
                {
                    case KEY_UP:
                        if (pozycja.first>1 && MAZE[pozycja.first-1][pozycja.second]!='#')
                        {
                            pozycja.first--;
                            ruchy++;
                        }
                        break;
                    case KEY_DOWN:
                        if (pozycja.first<height && MAZE[pozycja.first+1][pozycja.second]!='#')
                        {
                            pozycja.first++;
                            ruchy++;
                        }
                        break;
                    case KEY_LEFT:
                        if (pozycja.second>1 && MAZE[pozycja.first][pozycja.second-1]!='#')
                        {
                            pozycja.second--;
                            ruchy++;
                        }
                        break;
                    case KEY_RIGHT:
                        if (pozycja.second<width && MAZE[pozycja.first][pozycja.second+1]!='#')
                        {
                            pozycja.second++;
                            ruchy++;
                        }
                        break;
                        
                    case 100://d to autorun
                    {
                        goto koniec;
                    }
                    default:
                        break;
                }
                MAZE[pozycja.first][ pozycja.second]='X';
                
                if(pozycja.first==meta.first && pozycja.second==meta.second)//doszedl do mety
                    {
                            doszedlDoMety=true;
                    }
                
        
                if(pozycja.first > yMax-5 || pozycja.second > 2*xMax/3-5) // ------pozycja wychodzi poza okno
                    {
                        for (int i = 0; i < hh; i++ )
                            {
                                for (int j = 0; j < ww; j++ )
                                    {
                                        wattroff(PrintMaze,COLOR_PAIR(1));
                                        wattroff(PrintMaze,COLOR_PAIR(2));
                        
                                        if(pozycja.first > yMax-5 && pozycja.second > 2*xMax/3-5) //obie wspolrzedne wyszly
                                            {
                                                if(MAZE[i+pozycja.first-yMax+5][j+pozycja.second-2*xMax/3+5]=='#')
                                                wattron(PrintMaze,COLOR_PAIR(1));
                            
                                                if(i+pozycja.first-yMax+5==pozycja.first && j+pozycja.second-2*xMax/3+5==pozycja.second)
                                                    wattron(PrintMaze,COLOR_PAIR(2));
                            
                                                mvwprintw(PrintMaze,i+2,j+2,"%c",MAZE[i+pozycja.first-yMax+5][j+pozycja.second-2*xMax/3+5]);
                                            }
                        
                                        else if(pozycja.first > yMax-5) //wysokosc za duza
                                            {
                                                if(MAZE[i+pozycja.first-yMax+5][j]=='#')wattron(PrintMaze,COLOR_PAIR(1));
                                                if(i+pozycja.first-yMax+5 == pozycja.first && j == pozycja.second)
                                                    wattron(PrintMaze,COLOR_PAIR(2));
                            
                                                mvwprintw(PrintMaze,i+2,j+2,"%c",MAZE[i+pozycja.first-yMax+5][j]);
                                            }
                                        
                                        else if (pozycja.second > 2*xMax/3-5) //szerokosc za duza
                                            {
                                                if(MAZE[i][j+pozycja.second-2*xMax/3+5]=='#')wattron(PrintMaze,COLOR_PAIR(1));
                                                if(j+pozycja.second-2*xMax/3+5 == pozycja.second && i == pozycja.first)
                                                    wattron(PrintMaze,COLOR_PAIR(2));
                            
                                                mvwprintw(PrintMaze,i+2,j+2,"%c",MAZE[i][j+pozycja.second-2*xMax/3+5]);
                                            }
                                    }
                                wrefresh(PrintMaze);
                            }
                        wattroff(PrintMaze,COLOR_PAIR(1));
                        wattroff(PrintMaze,COLOR_PAIR(2));
                    }
            }
       koniec:
            //-----------------------------------------UZYTKOWNIK DOSZEDL DO METY
            
            for (int i = 0; i < 0; i++ ){}  //zeby etykieta dla goto dzialala
            
            int bestMoves = BFS(1, 1, PrintMaze, hh , ww);
            mvwprintw(pasekBoczny, 6, 2, "Best moves: %d                    ",bestMoves);
            mvwprintw(pasekBoczny, yMax-2, 2, "Press a key to continue                   ");
            
            double score=0;
            if(doszedlDoMety) score = bestMoves*10000/ruchy;
            
            mvwprintw(pasekBoczny, 10, 2, "YOUR SCORE IS: %g / 10000",score);
            
            wrefresh(pasekBoczny);
            
            wgetch(PrintMaze);
            wclear(PrintMaze);
            wclear(pasekBoczny);
            wrefresh(PrintMaze);
            wrefresh(pasekBoczny);
    
            delwin(PrintMaze);
            delwin(pasekBoczny);
            refresh();
            
            WINDOW*wyjscie=newwin(yMax, xMax, 1, 1);
            box(wyjscie, 0, 0);
            wrefresh(wyjscie);
            
            wattron(wyjscie,COLOR_PAIR(1));
            print_in_middle(wyjscie, yMax/2, -5, 0, "GOOD BYE!");
            wattroff(wyjscie,COLOR_PAIR(1));
            wgetch(wyjscie);
            //KONIEC CASE 2
        }
            break;
            
        case 1://--------------------------------------------------------------------------------------HELP
        {
            WINDOW* help = newwin(yMax, xMax, 1, 1);
            box(help, 0, 0);
            wrefresh(help);
            mvwprintw(help, 2, xMax/2-5, "HELP");
            mvwprintw(help, 4, 2, "Program automatycznie generuje losowy labirynt o podanych wymiarach.");
            mvwprintw(help, 5, 2, "Wymiary musza byc nieparzyste i mniejsze od okreslonej pozniej liczby");
            mvwprintw(help, 6, 2, "Naszym zadaniem jest dojsc do konca, ktory oznaczony jest");
            mvwprintw(help, 7, 2, "znakiem 'M'.");
            mvwprintw(help, 8, 2, "Poruszamy sie za pomoca strzalek.");
            mvwprintw(help, 9, 2, "W kazdej chwili uzutkownik moze uruchomic autosolve'a.");
            mvwprintw(help, 10, 2, "Wynik po uruchomieniu autosolve'a bedzie wynosil 0, bo");
            mvwprintw(help, 11, 2, "uzytkownik w ogole nie przeszedl labiryntu.");
            
            mvwprintw(help, yMax-2, xMax/3, "Press a key to continue.");
            
            wgetch(help);
            wclear(help);
            delwin(help);
            goto start;
        }
            break;
            
        case 2://EXIT
        {
            WINDOW*wyjscie=newwin(yMax, xMax, 1, 1);
            box(wyjscie, 0, 0);
            wrefresh(wyjscie);
            
            wattron(wyjscie,COLOR_PAIR(1));
            print_in_middle(wyjscie, yMax/2, -5, 0, "GOOD BYE!");
            wattroff(wyjscie,COLOR_PAIR(1));
            wgetch(wyjscie);
        }
            break;
            
        default:
            break;
    }
    
    endwin();
//-------------------------------------------------------------------------------------------NCURSES END//
    return 0;
}
Node *linkk( Node *n )
{
    int x=0;
    int y=0;
    char dir;
    Node *dest;
    if ( n == NULL ) return NULL;
    while ( n->dirs )
    {
        dir = ( 1 << ( rand( ) % 4 ) );
        if ( ~n->dirs & dir ) continue;
        n->dirs &= ~dir;
        switch ( dir )
        {
            case 1:
                if ( n->x + 2 < width )
                {
                    x = n->x + 2;
                    y = n->y;
                }
                else continue;
                break;
            case 2:
                if ( n->y + 2 < height )
                {
                    x = n->x;
                    y = n->y + 2;
                }
                else continue;
                break;
            case 4:
                if ( n->x - 2 >= 0 )
                {
                    x = n->x - 2;
                    y = n->y;
                }
                else continue;
                break;
            case 8:
                if ( n->y - 2 >= 0 )
                {
                    x = n->x;
                    y = n->y - 2;
                }
                else continue;
                break;
        }
        dest = nodes + x + y * width;
        if ( dest->c == ' ' )
        {
            if ( dest->parent != NULL ) continue;
            dest->parent = n;
            nodes[n->x + ( x - n->x ) / 2 + ( n->y + ( y - n->y ) / 2 ) * width].c = ' ';
            return dest;
        }
    }
    return n->parent;
}


int init( )
{
    int i, j;
    Node *n;
    
    nodes = calloc( width * height, sizeof( Node ) );
    if ( nodes == NULL ) return 1;
    
    for ( i = 0; i < width; i++ )
    {
        for ( j = 0; j < height; j++ )
        {
            n = nodes + i + j * width;
            if ( i * j % 2 )
            {
                n->x = i;
                n->y = j;
                n->dirs = 15;
                n->c = ' ';
            }
            else n->c = '#';
        }
    }
    return 0;
}


void draw( )
{
    int i, j;
    for ( i = 0; i < height; i++ )
    {
        for ( j = 0; j < width; j++ )
        {
            MAZE[i][j]= nodes[j + i * width].c ;
        }
        
    }
}

int BFS(int x, int y, WINDOW* w, int hh, int ww)
{
    int nj, ni;
    int ile=0;
    push(x,y);
    MAZE[x][y] = '#';
        while (notEmpty()) //dopoki cos jest w kolejce
        {
            /* biore pierwsza pare z kolejki*/
            pair para = front();
            int a = para.first;
            int b = para.second;
      
            
            for(int k = 0 ; k < 4 ; k++)
            {
                ni = a+dx[k];
                nj = b+dy[k];
                if(MAZE[ni][nj]!='#')
                {
                    push(ni,nj);
                    MAZE[ni][nj] ='#';
                    przodek[ni][nj] =para;
                }
            }
        }
    
    pair end;
    end.first = height-2; end.second = width-2;
    while(przodek[end.first][end.second].first != x || przodek[end.first][end.second].second != y )
    {
        if(przodek[end.first][end.second].first  < hh  && przodek[end.first][end.second].second  < ww)
            mvwprintw(w,przodek[end.first][end.second].first + 2, przodek[end.first][end.second].second + 2 , "X");
        end = przodek[end.first][end.second];
        ile++;
    }
    mvwprintw(w,x + 2,y+ 2 , "X");
    return ile;
}

/*
 void DFS(int x, int y,WINDOW *PrintMaze)
 {
 odwiedzone[x][y]=true;
 
 //mvwprintw(PrintMaze, x+2, y+2, "X");
 if(MAZE[x][y]=='M')dist[x][y]='X';//jak dotarlem do mety
 else
 for(int i=0;i<4;i++)
 {
 int ws1=x+dx[i];
 int ws2=y+dy[i];
 if(odwiedzone[ws1][ws2]==false && MAZE[ws1][ws2]!='#')
 {
 (DFS(ws1, ws2, PrintMaze));
 }
 odwiedzone[ws1][ws2]=false;
 }
 }
 */
