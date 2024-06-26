#pragma once

#ifndef BALL_H
#define BALL_H

#include "constants.h"
#include "entity.h"

// Class to represent the bouncing ball
// Inherits from moving_entity
class ball : public moving_entity {

private:

	static sf::Texture texture;

	bool isFixed = true;

	float xA, yA;

public:
	// Interface of the class

	// Constructor
	// Arguments are the initial coordinates of the centre of the ball
	// SFML uses the computer graphics convention
	// (0, 0) is the top left corner of the screen
	// x increases to the right
	// y increases downwards
	ball(float x, float y);

	// Implement the pure virtual functions
	void update(float DeltaTime) override;
	void draw(sf::RenderWindow& window) override;

	virtual void move_up() noexcept override;
	virtual void move_left() noexcept override;
	virtual void move_down() noexcept override;
	virtual void move_right() noexcept override;

	bool getIsFixed() const { return isFixed; }
	float getXA() const { return xA; }
	float getYA() const { return yA; }

	void setIsFixed(bool newf) { isFixed = newf; }
};

#endif // BALL_H
