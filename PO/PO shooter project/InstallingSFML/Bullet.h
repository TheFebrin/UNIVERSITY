#pragma once
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
    
    Vector2f GetEnemyPosition() { return shape.getPosition(); };
    Collider GetCollider() { return Collider(shape); }
    
public:
    int creationTime , lifeTime;
private:
    float maxspeed;
    bool destroy;
    
    
    
};

