#pragma once
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
    Collider GetCollider();
    
    int GetPlayerDir();
    void LowerHealth(int n); int GetHealth();
    
private:
    int Health, Armor;
    float PlayerSpeed;
    int direction;
    
    RectangleShape body;
    Animation animation;
    Texture PlayerTexture;
    
    unsigned int row;
    
};

