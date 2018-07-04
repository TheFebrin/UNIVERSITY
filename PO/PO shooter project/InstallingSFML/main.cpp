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
#include "TextDisplay.hpp"
#include "HUD.hpp"

using namespace sf;

int ScreenX = 1200, ScreenY = 720;
static const float VIEW_HEIGHT = (float)ScreenY;
int MapHeight = 2120, MapWidth = 3800;

void ResizeView(const RenderWindow& window, View& view);

int main()
{
    int counter = 0;
    float deltaTime = 0.0f;
    Clock clock, BulletClock, EnemyAtackClock;
    
    //WINDOW
    RenderWindow window(VideoMode(ScreenX, ScreenY), "Shooter", Style::Close | Style::Resize);
    View view(Vector2f(0, 0), Vector2f((float)ScreenX, (float)ScreenY));
    window.setFramerateLimit(120);
    
    //HUD
    HUD hud;
    Font font; font.loadFromFile(resourcePath() + "Fonts/sansation.ttf"); //--- GAME FONT
    hud.text.setFont(font); hud.score.setFont(font);
    
    //MAP
    Texture mapTexture;
    mapTexture.loadFromFile(resourcePath() + "Images/map.jpg");
    Sprite Map(mapTexture);
    
    //DISPLAY TEXT
    TextDisplay PlayerHealthText, EnemyHealthText;
    PlayerHealthText.text.setFont(font);
    EnemyHealthText.text.setFont(font); EnemyHealthText.text.setColor(Color::Blue);
    std::vector<TextDisplay> TextToDisplay;
   
    //PLAYER
    Texture playerTexture; //-----------------------------------------------------------CREATING PLAYER
    playerTexture.loadFromFile(resourcePath() + "Images/PlayerSprite.png");
    Player player(&playerTexture, Vector2u(4, 4), 0.3f, 75.f, 45.f);
    
    //BORDERS
    Texture a; a.loadFromFile(resourcePath() + "Images/border.jpg");
    Platform LeftBorder(&a, Vector2f(100, MapHeight), Vector2f(-50, MapHeight / 2));
    Platform TopBorder(&a, Vector2f(MapWidth, 100), Vector2f(MapWidth / 2, -50));
    Platform Botborder(&a, Vector2f(MapWidth, 100), Vector2f(MapWidth / 2, MapHeight));
    Platform RightBorder(&a, Vector2f(100, MapHeight), Vector2f(MapWidth, MapHeight / 2));
    
    //ENEMIES
    Texture enemyTexture;
    enemyTexture.loadFromFile(resourcePath() + "Images/EnemySprite.png");
    std::vector<Enemy>Enemies;
    int enemySpawn = 100;
    
    //BULLETS
    std::vector<Bullet>Bullets;
    
    while (window.isOpen()) //--------- MAIN LOOP
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
        
        //GENERATING ENEMIES
        if (counter % enemySpawn == 0) {
            Enemy enemy(&enemyTexture, Vector2u(4, 4), 0.3f, MapWidth - 500, MapHeight - 500);
            Enemies.push_back(enemy);
            if(enemySpawn > 10)enemySpawn--;
        }
       
        //CREATING BULLETS
        Time BulletTimer = BulletClock.getElapsedTime();
        if (Keyboard::isKeyPressed(Keyboard::Space) and BulletTimer.asSeconds() >= player.GetBulletRelease()){
            Bullet bullet(10.0f, player.GetPlayerPosition().x, player.GetPlayerPosition().y, player.GetPlayerDir(), counter);
            Bullets.push_back(bullet);
            BulletClock.restart();
        }
        
        //UPDATES
        player.Update(deltaTime);
        hud.Update(player, window);
        srand(time(NULL));
        for(auto &e : Enemies)e.Update(deltaTime, player);
        for(auto &b : Bullets)b.Update(deltaTime);
        for(auto &t : TextToDisplay)t.Update();
        
        //COLLISION FOR PLAYER AND BORDERS
        Time EnemyAtacksPlayer = EnemyAtackClock.getElapsedTime();
        LeftBorder.GetCollider().CheckCollision(player.GetCollider(), 1.f);
        RightBorder.GetCollider().CheckCollision(player.GetCollider(), 1.f);
        Botborder.GetCollider().CheckCollision(player.GetCollider(), 1.f);
        TopBorder.GetCollider().CheckCollision(player.GetCollider(), 1.f);
        
        //COLLISION FOR ALL ENEMIES
        for(auto &e: Enemies){
            
            if(e.GetCollider().CheckCollision(player.GetCollider(), 0.5f) and EnemyAtacksPlayer.asSeconds() >= 0.6){
                player.LowerHealth(e.GetDamage());
                PlayerHealthText.text.setPosition(player.GetPlayerPosition().x - player.GetPlayerSize().x / 2, player.GetPlayerPosition().y - player.GetPlayerSize().y / 2);
                PlayerHealthText.text.setString(std::to_string(e.GetDamage()));
                TextToDisplay.push_back(PlayerHealthText);
                EnemyAtackClock.restart();
            }
            
            LeftBorder.GetCollider().CheckCollision(e.GetCollider(), 1.f);
            RightBorder.GetCollider().CheckCollision(e.GetCollider(), 1.f);
            TopBorder.GetCollider().CheckCollision(e.GetCollider(), 1.f);
            Botborder.GetCollider().CheckCollision(e.GetCollider(), 1.f);
            
            for(auto &ee : Enemies)e.GetCollider().CheckCollision(ee.GetCollider(), 0.5f);
        }
        
        //COLLISION FOR ALL BULLETS
        for (auto &b : Bullets) {
            for (auto &e : Enemies)
                if (b.GetCollider().CheckBulletCollision(e.GetCollider(), 0.5f)){
                    b.Destroy();
                    e.LowerHealth(player.GetDamage());
                    if(e.GetHealth() <= 0)e.Destroy();
                    EnemyHealthText.text.setString(std::to_string(player.GetDamage()));
                    EnemyHealthText.text.setPosition(e.GetEnemyPosition().x, e.GetEnemyPosition().y);
                    TextToDisplay.push_back(EnemyHealthText);
                }
        }
        
        //WINDOW SETTINGS
        view.setCenter(player.GetPlayerPosition());     //player is in the center
        window.clear(Color(38, 105, 62));
        window.setView(view);
        
        //DRAWING
        window.draw(Map);
        player.DrawPlayer(window);
        LeftBorder.Draw(window);  TopBorder.Draw(window); Botborder.Draw(window); RightBorder.Draw(window);
       
        for(unsigned int i = 0; i < Enemies.size(); i++){  //---------------------------------DRAW / ERASE ENEMIES
            if(Enemies[i].ToDestroy()) Enemies.erase(Enemies.begin() + i);
            else Enemies[i].Draw(window);
        }
        
        for (unsigned int i = 0; i < Bullets.size(); i++) {  //------------------DRAW / ERASE BULLETS
            if (Bullets[i].ToDestroy()) Bullets.erase(Bullets.begin() + i);
            else Bullets[i].DrawBullet(window);
        }
        for(unsigned int i = 0; i < TextToDisplay.size(); i++){ //-------------------------DRAW / ERASE TEXT
            if(TextToDisplay[i].ToDestroy()) TextToDisplay.erase(TextToDisplay.begin() + i);
            else TextToDisplay[i].DrawText(window);
        }
     
//        hud.score.setPosition(player.GetPlayerPosition().x , player.GetPlayerPosition().y + window.getSize().y / 3);
//        window.draw(hud.score);
        window.draw(hud.text);
        window.display();
        
        //GAME OVER CASE
        if(player.GetHealth() <= 0){  //PLAYER IS DEAD
            TextDisplay GameOver;
            GameOver.text.setFont(font);
            GameOver.text.setString("GAME OVER");
            GameOver.text.setCharacterSize(100);
            GameOver.text.setPosition(player.GetPlayerPosition().x - window.getSize().x / 10, player.GetPlayerPosition().y);
            window.draw(GameOver.text);
            window.display();
            sleep(seconds(3));
            window.close();
        }
    }
    return 0;
}

void ResizeView(const RenderWindow& window, View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
