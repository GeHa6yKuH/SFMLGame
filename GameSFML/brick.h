#pragma once

#ifndef BRICK_H
#define BRICK_H

#include "Entity.h"
#include "constants.h"

class brick : public entity
{
	static sf::Texture texture;

private:

	int brick_HP = constants::brick_HP;

public:

	brick(float x, float y);

	void set_strength(int s) noexcept;
	void weaken() noexcept;
	bool is_too_weak() const noexcept;

	void update() override;
	void draw(sf::RenderWindow& window) override;
};

#endif // !BRICK_H
