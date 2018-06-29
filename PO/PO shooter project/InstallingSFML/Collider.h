#pragma once
#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>

using namespace sf;


class Collider
{
public:
    Collider(RectangleShape& body);
    Collider(CircleShape& shape);
    ~Collider();
    
    void Move(float dx, float dy) { body.move(dx, dy); }
    bool CheckCollision(Collider other, float push);
    Vector2f GetPosition() { return body.getPosition(); }
    Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
    
    bool CheckBulletCollision(Collider other, float push);
    Vector2f GetBulletPosition() { return shape.getPosition(); }
    FloatRect GetRectBounds() { return body.getGlobalBounds(); }
    FloatRect GetCircleBounds() { return shape.getGlobalBounds(); }
private:
    RectangleShape& body;
    CircleShape& shape;
};

