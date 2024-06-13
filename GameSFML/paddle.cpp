#include "paddle.h"

sf::Texture paddle::texture;

paddle::paddle(float x, float y) : moving_entity() {
    // Load the texture
    texture.loadFromFile("paddle.png");
    sprite.setTexture(texture);

    xA = x;
    yA = y;

    // Set the initial position and velocity of the ball
    // Use (x, y) for the initial position of the ball
    sprite.setPosition(xA, yA);
    /*velocity = { constants::ball_speed, constants::ball_speed };*/
}

void paddle::update() {
    // Move the position of the ball
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
    {
        velocity = x() >= 0 ? sf::Vector2f(-6.f, 0.f) : sf::Vector2f(0.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
    {
        velocity = x() <= constants::window_width - 70.f ? sf::Vector2f(6.f, 0.f) : sf::Vector2f(0.f, 0.f);
    }
    else
    {
        velocity = { 0.f, 0.f };
    }

    if (!isFixed)
    {
        sprite.move(velocity);
    }
}

void paddle::draw(sf::RenderWindow& window) {
    // Ask the window to draw the sprite for us
    window.draw(sprite);
}

void paddle::move_up() noexcept {
}

void paddle::move_down() noexcept {
}

void paddle::move_right() noexcept {
    velocity.x = 3;
}

void paddle::move_left() noexcept {
    velocity.x = -3;
}
