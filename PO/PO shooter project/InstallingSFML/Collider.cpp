#include "Collider.h"



Collider::Collider(RectangleShape& body)
:body(body)
,shape(shape)
{
    
}
Collider::Collider(CircleShape& shape)
: body(body)
, shape(shape)
{
    
}

Collider::~Collider()
{
}
bool Collider::CheckBulletCollision(Collider other, float push)
{
    FloatRect enemy = other.GetRectBounds();
    FloatRect bullet = GetCircleBounds();
    if (bullet.intersects(enemy))return true;
    else return false;
}
bool Collider::CheckCollision(Collider other, float push)
{
    Vector2f otherPosition = other.GetPosition();
    Vector2f otherHalfSize = other.GetHalfSize();
    
    Vector2f thisPosition = GetPosition();
    Vector2f thisHalfSize = GetHalfSize();
    
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (thisHalfSize.y + thisHalfSize.y);
    
    if (intersectX < 0 and intersectY < 0)
    {
        push = std::min(std::max(push, 0.0f), 1.0f); //clumping betwween 0 and 1
        if (intersectX > intersectY)
        {
            if (deltaX > 0)
            {
                Move(intersectX * (1.0f - push), 0.0f);
                other.Move(-intersectX * push, 0.0f);
            }
            else
            {
                Move(-intersectX * (1.0f - push), 0.0f);
                other.Move(intersectX * push, 0.0f);
            }
        }
        else
        {
            if (deltaY > 0)
            {
                Move(0.0f, intersectY * (1.0f - push));
                other.Move(0.0f , -intersectY * push);
            }
            else
            {
                Move(0.0f, -intersectY * (1.0f - push));
                other.Move(0.0f, intersectY * push);
            }
        }
        return true;
    }
    
    return false;
}
