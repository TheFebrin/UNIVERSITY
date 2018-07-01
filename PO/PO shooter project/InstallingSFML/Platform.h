#pragma once
#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>

#include "Collider.h"
#include "Entity.h"
using namespace sf;

class Platform : public Entity
{
public:
    Platform(Texture* texture, Vector2f size, Vector2f position);
    ~Platform();
    
    void Draw(RenderWindow& window);
    Collider GetCollider();
    RectangleShape GetBody();
};

