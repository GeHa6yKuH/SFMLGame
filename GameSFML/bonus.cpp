#include "bonus.h"

sf::Texture bonus::texture;

const sf::Color lightGreen{ 128, 255, 128, 255 };

bonus::bonus(float x, float y) : moving_entity() {
    // Load the texture
    texture.loadFromFile("bonus.png");
    sprite.setTexture(texture);

    // Set the initial position and velocity of the ball
    // Use (x, y) for the initial position of the ball
    sprite.setPosition(x, y);
    sprite.setColor(lightGreen);
    sprite.setScale(0.8f, 0.8f);
    velocity = { 0.f , constants::bonus_speed };

    sprite.setOrigin(get_centre());
}

void bonus::move_down() noexcept {
    velocity.y = constants::ball_speed;
}

void bonus::move_up() noexcept {
    velocity.y = constants::ball_speed;
}

void bonus::move_right() noexcept {
    velocity.y = constants::ball_speed;
}

void bonus::move_left() noexcept {
    velocity.y = constants::ball_speed;
}

void bonus::update(float DeltaTime) {
    // Move the position of the ball

    if (y() < 0)
        velocity.y = -velocity.y;
    if (y() > constants::window_height)
        destroy();

    sprite.move(velocity * DeltaTime * constants::delta_time_multiplier);
}

void bonus::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
