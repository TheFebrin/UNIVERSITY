#pragma once
#ifndef Entity_h

#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>

#include "Animation.h"

using namespace sf;

class Entity
{
public:
    
    RectangleShape body;
    Sprite sprite;
    Text text;
    CircleShape shape;
    
public:
    void Draw(RenderWindow &win);
    
private:
    
};

#endif
