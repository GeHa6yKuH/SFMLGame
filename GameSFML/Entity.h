#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Abstract base class to represent any graphical entity on the screen
class entity {
protected:

	sf::Sprite sprite;

	sf::Sound sound;
	sf::Sound sound1;
	sf::Sound sound2;

	sf::SoundBuffer s_buffer;
	sf::SoundBuffer s_buffer1;
	sf::SoundBuffer s_buffer2;

	bool destroyed{ false };

public:
	// Pure virtual functions
	// Concrete graphical entities must implement these functions
	// The update member function will compute the new position, appearance, etc of the object
	// The draw member function will cause the updated object to be displayed in the game window
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	// Helper function to get the bounding box of a sprite
	sf::FloatRect get_bounding_box() const noexcept;

	// Helper function to get the centre of a sprite
	sf::Vector2f get_centre() const noexcept;

	// Helper functions to get the position of the sprite
	float x() const noexcept;
	float y() const noexcept;

	float left() const noexcept;
	float right() const noexcept;
	float bottom() const noexcept;
	float top() const noexcept;

	void destroy() noexcept;
	bool is_destroyed() const noexcept;

	// Virtual destructor
	virtual ~entity() {}

	sf::Sprite* getSprite() { return &sprite; }

	void playSound() { sound.play(); }
	void playSound1() { sound1.play(); }
	void playSound2() { sound2.play(); }
};

// Abstract base class to represent graphical entities which can move around the screen
class moving_entity : public entity {
protected:
	// SFML vector to store the object's velocity
	// This is the distance the ball moves between screen updates
	sf::Vector2f velocity;
public:
	// Helper functions inherited from parent class

	virtual void move_up() noexcept = 0;
	virtual void move_down() noexcept = 0;
	virtual void move_left() noexcept = 0;
	virtual void move_right() noexcept = 0;

	sf::Vector2f getVelocity() const { return velocity; }

	void setVelocity(sf::Vector2f newVel) { velocity = newVel; }
	
};

#endif // ENTITY_H
