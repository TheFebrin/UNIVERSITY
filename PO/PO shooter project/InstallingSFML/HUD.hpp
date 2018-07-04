//
//  HUD.hpp
//  InstallingSFML
//
//  Created by Urszula Wiśniewska on 03/07/2018.
//  Copyright © 2018 Blank Blank. All rights reserved.
//

#ifndef HUD_hpp
#define HUD_hpp

#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>

#include "Entity.h"
#include "Player.h"
using namespace sf;

class HUD : public Entity
{
public:
    HUD();
    void Update(Player player, RenderWindow &win);
    
    Text score;
};

#endif /* HUD_hpp */
