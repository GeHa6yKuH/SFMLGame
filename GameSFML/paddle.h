#pragma once

#pragma once

#ifndef PADDLE_H
#define PADDLE_H

#include "constants.h"
#include "entity.h"

// Class to represent the bouncing ball
// Inherits from moving_entity
class paddle : public moving_entity {
	// Private data members

private:

	bool isFixed = true;

	float xA, yA;

public:
	static sf::Texture texture;
	// Interface of the class

	// Constructor
	// Arguments are the initial coordinates of the centre of the ball
	// SFML uses the computer graphics convention
	// (0, 0) is the top left corner of the screen
	// x increases to the right
	// y increases downwards
	paddle(float x, float y);

	// Implement the pure virtual functions
	void update(float DeltaTime) override;
	void draw(sf::RenderWindow& window) override;

	virtual void move_up() noexcept override;
	virtual void move_down() noexcept override;
	virtual void move_left() noexcept override;
	virtual void move_right() noexcept override;

	bool getIsFixed() const { return isFixed; }
	void setIsFixed(bool newIsFixed) { isFixed = newIsFixed; }

	void setXA(float newX) { xA = newX; }
	void setYA(float newY) { yA = newY; }
};

#endif // PADDLE_H