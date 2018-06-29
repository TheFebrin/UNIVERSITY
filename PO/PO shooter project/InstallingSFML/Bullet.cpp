#include "Bullet.h"



Bullet::Bullet(float radius, int xPos, int yPos, int dir, int creationTime)
{
    maxspeed = 8.f;
    currvelocity.x = 0; currvelocity.y = 0;
    if (dir == 0)currvelocity.y = -1 * maxspeed;
    else if (dir == 1)currvelocity.y = 1 * maxspeed;
    else if (dir == 2)currvelocity.x = -1 * maxspeed;
    else if (dir == 3)currvelocity.x = 1 * maxspeed;
    
    shape.setPosition(xPos, yPos);
    this->shape.setRadius(radius);
    this->shape.setFillColor(Color::Red);
    this->shape.setRadius(radius);
    
    this->creationTime = creationTime;
    lifeTime = 30; //bullet lasting
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
   // currvelocity.x += maxspeed * deltaTime;
   // currvelocity.y += maxspeed * deltaTime;
    shape.move(currvelocity);
}

void Bullet::DrawBullet(RenderWindow & win)
{
    win.draw(shape);
}
