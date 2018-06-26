//
//  Game.cpp
//  game
//
//  Created by Dawid on 21/04/2018.
//  Copyright © 2018 game. All rights reserved.
//

#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "bullet.hpp"
using namespace std;


#define SIZE 1000
Player* player;
GameObject* Enemies[1000]; int enemiesSize;  //enemies array with number of enemies
Map* WorldMap;
Bullet* Bullets[SIZE]; int bulletsSize;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game()
{}
Game::~Game()
{}

void Game::NewEnemy()  //creates new enemy
{
    if(enemiesSize >= SIZE)enemiesSize = 0;
    Enemies[enemiesSize] = new GameObject("/Users/dejw/Desktop/Moja Gra/game/game/images/racket.jpg",0,0);
    enemiesSize++;
}
void Game::NewBullet(double xB, double yB, double mouseX, double mouseY)
{
    if(bulletsSize >= SIZE) bulletsSize = 0;
    Bullets[bulletsSize] = new Bullet("/Users/dejw/Desktop/Moja Gra/game/game/images/bullet.jpg",xB,yB, mouseX, mouseY);
    bulletsSize++;
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)  //initializing game screen
{   
    int flags = 0;
    if(fullscreen) flags = SDL_WINDOW_FULLSCREEN;  //jezeli FS to ustawiam flage
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout<<"Subsystems Initialised!!!\n";
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            cout<<"Window created!\n";
        }
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout<<"Renderer created!\n";
        }
        
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    
    player = new Player("/Users/dejw/Desktop/Moja Gra/game/game/images/kacper.jpg");
    WorldMap = new Map();

}


bool leftt = 0, rightt = 0, up = 0, down = 0; //player movement dir
void Game::HandleEvents()  //user interaction
{
    SDL_PollEvent(&event);
    
    switch (event.type) //menu events
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
    
    if(event.type == SDL_KEYDOWN) // if key is pressed
    {
        switch (event.key.keysym.sym) // player movement
        {
            case SDLK_w:
                up = true;
                break;
            
            case SDLK_s:
                down = true;
                break;
            
            case SDLK_a:
                leftt = true;
                break;
            
            case SDLK_d:
                rightt = true;
                break;
                
            default:
                break;
        }
    }
    
    if(event.type == SDL_KEYUP) //key is released
    {
        switch (event.key.keysym.sym) // we stop player movement if user releases the key
        {
            case SDLK_w:
                up = false;
                break;

            case SDLK_s:
                down = false;
                break;

            case SDLK_a:
                leftt = false;
                break;

            case SDLK_d:
                rightt = false;
                break;

            default:
                break;
        }
    }
    
    if(event.type == SDL_MOUSEBUTTONDOWN) //mouse clicked
    {
        int a,b;
        SDL_GetMouseState(&a, &b);
        if(bulletsSize < SIZE) NewBullet(player->GetPlayerXpos(),player->GetPlayerYpos(),a,b);
    }
    
    if(event.type == SDL_MOUSEBUTTONUP) //mouse released
    {
        
    }
}

void Game::Update() // updating all objects in game
{
    if(count % 100 == 0 and enemiesSize < SIZE)NewEnemy(); //creating new enemy if their number is less than 1000
    for(int i=0; i < enemiesSize; i++) Enemies[i]->Update(player);
    for(int i=0; i < bulletsSize; i++) Bullets[i]->Update();

    player->Update(up,down,leftt,rightt);
    count++;
    cout<<count<<endl;
}

void Game::Render() // renders stuff on window
{
    SDL_RenderClear(renderer);
    //now we can add stuff to render
    
    WorldMap->DrawMap();     //first draw map
    player->Render();        //render player
    for(int i=0; i < enemiesSize; i++) Enemies[i]->Render(); //render enemies
    for(int i=0; i < bulletsSize; i++) Bullets[i]->Render(); //render bullets
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout<<"Game cleaned.\n";
}




