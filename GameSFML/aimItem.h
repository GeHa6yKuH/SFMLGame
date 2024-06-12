#pragma once

#include "Entity.h"

enum transparencyIndex { first, second, third, fourth, fifth };

class aimItem : public entity
{
private:

	static sf::Texture texture;

	float xA, yA;

	transparencyIndex trInd;

public:

	aimItem(float x, float y);

	// Implement the pure virtual functions
	void update() override;
	void draw(sf::RenderWindow& window) override;

	float getXA() const { return xA; }
	float getYA() const { return yA; }

	void setXA(float newX) { xA = newX; }
	void setYA(float newY) { yA = newY; }

	void setTransparencyIndex(transparencyIndex trn) { trInd = trn; }
};

