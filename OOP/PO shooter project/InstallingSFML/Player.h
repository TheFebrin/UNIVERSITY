#pragma once
#ifndef Player_h

#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>

#include "Animation.h"
#include "Collider.h"
#include "Bullet.h"

using namespace sf;
class Player
{
public:
    Player (Texture* texture, Vector2u imageCount, float switchTime, float height, float width);
    ~Player();
    void Update(float deltaTime);
    void DrawPlayer(RenderWindow &win);
    
    Vector2f GetPlayerPosition();
    Vector2f GetPlayerSize();
    Collider GetCollider();
    
    int GetPlayerDir();
    void LowerHealth(int n); int GetHealth();
    int GetDamage();
    float GetBulletRelease();
    
private:
    int Health, Damage;
    float PlayerSpeed, BulletRelease;
    int direction;
    
    
    Vector2f PlayerSize;
    RectangleShape body;
    Animation animation;
    Texture PlayerTexture;
    
    unsigned int row;
    
};

#endif
