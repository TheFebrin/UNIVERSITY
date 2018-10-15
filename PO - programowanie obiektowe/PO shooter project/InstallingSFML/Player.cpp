#include "Player.h"

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float height, float width)
:animation(texture, imageCount, switchTime)
{
    Health = 100; Damage = 2;
    BulletRelease = 0.5f;
    PlayerSpeed = 980.f;
    row = 0;
    
    PlayerSize.x = width; PlayerSize.y = height;
    body.setSize(Vector2f(width, height));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(1500.f, 1000.f);
    body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        movement.y -= PlayerSpeed * deltaTime;
        row = 3; //setting 4th row in the player sprite walking sheet
        direction = 0;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        movement.y += PlayerSpeed * deltaTime;
        row = 0;
        direction = 1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::A))
    {
        movement.x -= PlayerSpeed * deltaTime;
        row = 1;
        direction = 2;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        movement.x += PlayerSpeed * deltaTime;
        row = 2;
        direction = 3;
    }
    
    //if (movement.x == 0 and movement.y == 0) row = 0;
    
    animation.Update(row, deltaTime);
    body.setTextureRect(animation.textureRect);
    body.move(movement);
}

void Player::DrawPlayer(RenderWindow &win){
    win.draw(body);
}

Vector2f Player::GetPlayerPosition() {
    return body.getPosition();
}

Collider Player::GetCollider(){
    return Collider(body);
}

int Player::GetPlayerDir(){
    return direction;
}

void Player::LowerHealth(int n){
    Health -= n;
}

int Player::GetHealth(){
    return Health;
}

Vector2f Player::GetPlayerSize(){
    return PlayerSize;
}

int Player::GetDamage(){
    return Damage;
}
float Player::GetBulletRelease(){
    return BulletRelease;
}
