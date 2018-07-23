
//  Projekt C
//  modul struktury
//  Created by Dawid Dieu on 14/01/2018.
/*
 .___  ___.      ___       ________   _______
 |   \/   |     /   \     |       /  |   ____|
 |  \  /  |    /  ^  \    `---/  /   |  |__
 |  |\/|  |   /  /_\  \      /  /    |   __|
 |  |  |  |  /  _____  \    /  /----.|  |____
 |__|  |__| /__/     \__\  /________||_______|

 */

//int BFS(int x, int y, WINDOW*w, int hh, int ww);


typedef struct
{
    int x, y;
    void *parent;
    char c;
    char dirs;
} Node;

typedef struct
{
    int first;
    int second;
} pair;

 struct timespec s; //czekanie
