//
//  HUD.cpp
//  InstallingSFML
//
//  Created by Urszula Wiśniewska on 03/07/2018.
//  Copyright © 2018 Blank Blank. All rights reserved.
//

#include "HUD.hpp"

HUD::HUD()
{
    text.setColor(Color(255 , 120, 0));
    text.setCharacterSize(30);
    text.setString("100");
    text.setPosition(10, 10);
    
    score.setColor(Color(255 , 120, 0));
    score.setCharacterSize(30);
    score.setString("SCORE");
    score.setPosition(10, 10);
}

void HUD::Update(Player player, RenderWindow &win)
{
    Vector2f position = player.GetPlayerPosition();
    text.setPosition(position.x - player.GetPlayerSize().x / 2, position.y - player.GetPlayerSize().y / 1.5);
    text.setString(std::to_string(player.GetHealth()) + "hp");
}
