//
//  GameObject.cpp
//  game
//
//  Created by Dawid on 21/04/2018.
//  Copyright © 2018 game. All rights reserved.
//

#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"

GameObject::GameObject(const char* textsheet, int x, int y) //creating new object
{
    objTexture = TextureManager::LoadTexture(textsheet);
    
    xPosObj = x;
    yPosObj = y;
}

void GameObject::Update(Player *player) //position update for objects
{
    int PlayerXpos = player->GetPlayerXpos();
    int PlayerYpos = player->GetPlayerYpos();
    
    if(PlayerXpos > xPosObj)xPosObj++;
    else xPosObj--;
    
    if(PlayerYpos > yPosObj)yPosObj++;
    else yPosObj--;
    
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;
    
    destRect.x = xPosObj;
    destRect.y = yPosObj;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
