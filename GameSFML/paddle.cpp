#include "paddle.h"

#include <iostream>

sf::Texture paddle::texture;

paddle::paddle(float x, float y) : moving_entity() {
    // Load the texture
    texture.loadFromFile("paddle.png");
    sprite.setTexture(texture);

    if (s_buffer.loadFromFile("ball_bounces_paddle.wav"))
    {
        sound.setBuffer(s_buffer);
    }

    if (s_buffer1.loadFromFile("catch_bonus.wav"))
    {
        sound1.setBuffer(s_buffer1);
    }

    xA = x;
    yA = y;

    sprite.setScale(1.2f, 1.f);

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
        velocity = x() <= constants::window_width - constants::paddle_width ? sf::Vector2f(6.f, 0.f) : sf::Vector2f(0.f, 0.f);
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
