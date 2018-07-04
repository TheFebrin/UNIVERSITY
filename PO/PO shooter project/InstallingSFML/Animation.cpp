#include "Animation.h"


Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    
    textureRect.width = texture->getSize().x / float(imageCount.x);
    textureRect.height = texture->getSize().y / float(imageCount.y);
}


Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;
    
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;
        currentImage.x %= 4;
    }
    textureRect.left = currentImage.x * textureRect.width;
    textureRect.top = currentImage.y * textureRect.height;
}
