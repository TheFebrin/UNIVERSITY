#pragma once
#ifndef Animation_h

#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>

using namespace sf;

class Animation
{
public:
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    ~Animation();
    
    void Update(int row, float deltaTime);
    
public:
    IntRect textureRect;
    
private:
    Vector2u imageCount;
    Vector2u currentImage;
    
    float totalTime;
    float switchTime;
};

#endif
