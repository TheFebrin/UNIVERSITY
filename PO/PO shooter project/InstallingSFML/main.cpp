#include<iostream>
#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>

#include "ResourcePath.hpp"
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Entity.h"
#include "Bullet.h"

using namespace sf;

int ScreenX = 1200, ScreenY = 720;
static const float VIEW_HEIGHT = (float)ScreenY;
int MapHeight = 2084, MapWidth = 3840;

void ResizeView(const RenderWindow& window, View& view);

int main()
{
    int counter = 0;
    float deltaTime = 0.0f;
    Clock clock;
    
    //WINDOW
    RenderWindow window(VideoMode(ScreenX, ScreenY), "Shooter", Style::Close | Style::Resize);
    View view(Vector2f(0, 0), Vector2f((float)ScreenX, (float)ScreenY));
    window.setFramerateLimit(120);
    
    //MAP
    Texture mapTexture;
    mapTexture.loadFromFile(resourcePath() + "Images/map.jpg");
    Sprite Map(mapTexture);
    
    //PLAYER
    Texture playerTexture; //-----------------------------------------------------------CREATING PLAYER
    playerTexture.loadFromFile(resourcePath() + "Images/PlayerSprite.png");
    Player player(&playerTexture, Vector2u(4, 4), 0.3f, 75.f, 45.f);
    
    //SHIT
    Texture a; a.loadFromFile(resourcePath() + "Images/a.jpg");
    Texture b; b.loadFromFile(resourcePath() + "Images/b.jpg");
    Platform p1(&a, Vector2f(200, 150), Vector2f(200, 100));
    Platform p2(&b, Vector2f(200, 150), Vector2f(500, 0));
    
    //ENEMIES
    Texture enemyTexture;
    enemyTexture.loadFromFile(resourcePath() + "Images/EnemySprite.png");
    std::vector<Enemy>Enemies;
    int enemySpawn = 100;
    
    //BULLET
    std::vector<Bullet>Bullets;
    int bulletShot = 0;
    
    
    while (window.isOpen())
    {
        std::cout << player.GetPlayerPosition().x<<"  " << player.GetPlayerPosition().y << "  Enemies:  "<<Enemies.size()<<"\n";
        counter++;
        deltaTime = clock.restart().asSeconds();
        
        Event Myevent;
        while(window.pollEvent(Myevent))
        {
            switch(Myevent.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                    
                case Event::Resized:
                    ResizeView(window, view);
                    break;
                    
                default:
                    break;
            }
        }
        
        //GENERATING
        if (counter % enemySpawn == 0) {
            Enemy enemy(&enemyTexture, Vector2u(4, 4), 0.3f, MapWidth, MapHeight);
            Enemies.push_back(enemy);
            if(enemySpawn > 10)enemySpawn--;
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Space) and bulletShot > 100){ //--------------CREATING BULLETS
            Bullet bullet(10.0f, player.GetPlayerPosition().x, player.GetPlayerPosition().y, player.GetPlayerDir(), counter);
            Bullets.push_back(bullet);
            bulletShot = 0;
        }bulletShot++;
        
        //UPDATE
        player.Update(deltaTime);
        srand(time(NULL));
        for(auto &e : Enemies)e.Update(deltaTime, player);
        for(auto &b : Bullets)b.Update(deltaTime);
        
        //COLLISION
        p1.GetCollider().CheckCollision(player.GetCollider(), 0.3f);
        p2.GetCollider().CheckCollision(player.GetCollider(), 0.8f);
        for(auto &e: Enemies)e.GetCollider().CheckCollision(player.GetCollider(), 0.5f);   //-------COLLISION FOR ALL ENEMIES
        for(auto &e: Enemies) for(auto &ee : Enemies)e.GetCollider().CheckCollision(ee.GetCollider(), 0.5f);
        for (auto &b : Bullets) {
            for (unsigned int i = 0; i < Enemies.size(); i++)
                if (b.GetCollider().CheckBulletCollision(Enemies[i].GetCollider(), 0.5f)) Enemies.erase(Enemies.begin() + i);
        }
        
        //WINDOW SETTINGS
        view.setCenter(player.GetPlayerPosition());     //player is in the center
        window.clear(Color(38, 105, 62));
        window.setView(view);
        
        //DRAWING
        window.draw(Map);
        player.DrawPlayer(window);
        p1.Draw(window);
        p2.Draw(window);
        for(auto &e : Enemies)e.DrawEnemy(window); //-------------------DRAW ENEMIES
        for (unsigned int i = 0; i < Bullets.size(); i++) {  //------------------DRAW BULLETS
            if (Bullets[i].creationTime + Bullets[i].lifeTime < counter)Bullets.erase(Bullets.begin() + i);
            else Bullets[i].DrawBullet(window);
        }
        
        window.display();
    }
    
    return 0;
}

void ResizeView(const RenderWindow& window, View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
