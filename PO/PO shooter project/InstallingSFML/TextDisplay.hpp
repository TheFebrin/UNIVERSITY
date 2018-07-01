//
//  TextDisplay.hpp
//  InstallingSFML
//
//  Created by Dawid Dieu on 01/07/2018.
//  Copyright © 2018 Blank Blank. All rights reserved.
//

#ifndef TextDisplay_hpp
#define TextDisplay_hpp

#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>


#include "Entity.h"

using namespace sf;

class TextDisplay : public Entity
{
public:
    TextDisplay();
    void Update();
    
public:
    std::string MyString = "Default";
    
private:
 
    
};



#endif /* TextDisplay_hpp */
