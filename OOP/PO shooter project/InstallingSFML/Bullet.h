#pragma once
#ifndef Bullet_h

#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>


#include "Entity.h"
#include "Collider.h"
#include "Player.h"
using namespace sf;

class Bullet : public Entity
{
public:
    Bullet(float radius, int xPos, int yPos, int dir, int creationTime);
    ~Bullet();
    
    //CircleShape shape;
    Vector2f currvelocity;
    void Update(float deltaTime);
    void DrawBullet(RenderWindow &win);
    bool ToDestroy();
    void Destroy();
    
    Collider GetCollider() { return Collider(shape); }
    
public:
    int timeCounter , lifeTime;
private:
    float maxspeed;
    bool destroy;
    
};

#endif

