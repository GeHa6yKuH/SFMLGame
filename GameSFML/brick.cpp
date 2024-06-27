#include "brick.h"

sf::Texture brick::texture;

const sf::Color brick_color_hit1{ 0, 255, 0, 80 };
const sf::Color brick_color_hit2{0, 255, 0, 170};
const sf::Color brick_color_hit3{0, 255, 0, 255};

void brick::set_strength(int s) noexcept
{
	brick_HP = s;
}

void brick::weaken() noexcept
{
	--brick_HP;
}

bool brick::is_too_weak() const noexcept
{
	return brick_HP <= 0;
}

brick::brick(float x, float y)
{
	xA = x;
	yA = y;

	texture.loadFromFile("brick.png");
	sprite.setTexture(texture);

	/*if (s_buffer.loadFromFile("brick_destroyed.wav"))
	{
		sound.setBuffer(s_buffer);
	}*/

	sprite.setPosition(x, y);
	sprite.setOrigin(get_centre());
}

void brick::update(float DeltaTime)
{
	if (brick_HP == 1)
	{
		sprite.setColor(brick_color_hit1);
	} else if (brick_HP == 2)
	{
		sprite.setColor(brick_color_hit2);
	} else if (brick_HP == 3)
	{
		sprite.setColor(brick_color_hit3);
	}
}

void brick::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
