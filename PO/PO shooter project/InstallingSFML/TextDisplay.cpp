//
//  TextDisplay.cpp
//  Shooter Game
//
//  Created by Dawid Dieu on 01/07/2018.
//  Copyright © 2018 Blank Blank. All rights reserved.
//

#include "TextDisplay.hpp"

TextDisplay::TextDisplay()
{
    timeCounter = 0;
    lifeTime = 30;
    text.setColor(Color::Red);
    text.setCharacterSize(30);
    text.setString(MyString);
}

void TextDisplay::Update()
{
    text.move(0, -2);
    
    timeCounter++;
    if (timeCounter >= lifeTime) destroy = true;
}

void TextDisplay::DrawText(RenderWindow &win){
    win.draw(text);
}

bool TextDisplay::ToDestroy(){
    return destroy;
}
