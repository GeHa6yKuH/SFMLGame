#pragma once

#ifndef BONUS_H
#define BONUS_H

#include "constants.h"
#include "entity.h"

// Class to represent the bouncing ball
// Inherits from moving_entity
class bonus : public moving_entity {
	// Private data members
	static sf::Texture texture;

public:
	// Interface of the class

	// Constructor
	// Arguments are the initial coordinates of the centre of the ball
	// SFML uses the computer graphics convention
	// (0, 0) is the top left corner of the screen
	// x increases to the right
	// y increases downwards
	bonus(float x, float y);

	// Implement the pure virtual functions
	void update(float DeltaTime) override;
	void draw(sf::RenderWindow& window) override;

	virtual void move_down() noexcept override;
	virtual void move_up() noexcept override;
	virtual void move_right() noexcept override;
	virtual void move_left() noexcept override;
};

#endif // BALL_H
