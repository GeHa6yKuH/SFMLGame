#include "aimItem.h"

sf::Texture aimItem::texture;

const sf::Color aimItem_color_first{ 192, 192, 192, 220 };
const sf::Color aimItem_color_second{ 192, 192, 192, 200 };  
const sf::Color aimItem_color_third{ 192, 192, 192, 150 };   
const sf::Color aimItem_color_fourth{ 192, 192, 192, 110 };  
const sf::Color aimItem_color_fifth{ 192, 192, 192, 80 };   

aimItem::aimItem(float x, float y) : entity()
{
    // Load the texture
    texture.loadFromFile("ball.png");
    sprite.setTexture(texture);

    // Set the initial position and velocity of the ball
    // Use (x, y) for the initial position of the ball

    xA = x;
    yA = y;

    sprite.setPosition(xA, yA);

    sprite.setOrigin(get_centre());
}

void aimItem::update(float DeltaTime) 
{
	switch (trInd) {
    case 0:
        sprite.setColor(aimItem_color_first);
		break;
    case 1:
        sprite.setColor(aimItem_color_second);
        break;
    case 2:
        sprite.setColor(aimItem_color_third);
        break;
    case 3:
        sprite.setColor(aimItem_color_fourth);
        break;
    case 4:
        sprite.setColor(aimItem_color_fifth);
        break;
	}

    sprite.setPosition(xA, yA);
}

void aimItem::draw(sf::RenderWindow& window) 
{
    window.draw(sprite);
}
