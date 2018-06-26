//
//  Game.hpp
//  game
//
//  Created by Dawid on 21/04/2018.
//  Copyright © 2018 game. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "SDL_image.h"
using namespace std;

class Game
{
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void Update();
    void Render();
    void Clean();
    void HandleEvents();
    static SDL_Event event;
    void NewEnemy();
    void NewBullet(double x, double y, double mouseX, double mouseY);
    
    
    bool running()
    {
        return isRunning;
    }
    
    static SDL_Renderer* renderer;
    
private:
    int count = 0;
    bool isRunning;
    SDL_Window *window;
    
};

#endif /* Game_hpp */
