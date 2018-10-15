#include "Bullet.h"



Bullet::Bullet(float radius, int xPos, int yPos, int dir, int creationTime)
{
    timeCounter = 0;
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
    
    lifeTime = 40; //bullet lasting
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
   // currvelocity.x += maxspeed * deltaTime;
   // currvelocity.y += maxspeed * deltaTime;
    shape.move(currvelocity);
    timeCounter++;
    if (timeCounter >= lifeTime) destroy = true;
}

void Bullet::DrawBullet(RenderWindow & win)
{
    win.draw(shape);
}

bool Bullet::ToDestroy(){
    return destroy;
}

void Bullet::Destroy(){
    destroy = true;
}
