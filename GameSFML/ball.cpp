#include "ball.h"

// Initialize static data
sf::Texture ball::texture;

ball::ball(float x, float y) : moving_entity() {
    // Load the texture
    texture.loadFromFile("ball.png");
    sprite.setTexture(texture);

    // Set the initial position and velocity of the ball
    // Use (x, y) for the initial position of the ball

    xA = x;
    yA = y;

    sprite.setPosition(xA, yA);

    if (s_buffer.loadFromFile("ball_bounces_paddle.wav"))
    {
        sound.setBuffer(s_buffer);
        sound.setVolume(constants::preferable_sounds_volume);
    }

    // set initial velocity of the ball
    velocity = { 0.f , -constants::ball_speed };

    sprite.setOrigin(get_centre());
}

void ball::move_up() noexcept {
    velocity.y = -constants::ball_speed;
}

void ball::move_right() noexcept {
    velocity.x = constants::ball_speed;
}

void ball::move_left() noexcept {
    velocity.x = -constants::ball_speed;
}

void ball::move_down() noexcept {
    velocity.y = constants::ball_speed;
}

// Compute the ball's new position
void ball::update(float DeltaTime) {
    // Move the position of the ball

    if (isFixed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) && velocity.x > -constants::ball_maxX_velocity)
        {
            velocity.x -= 0.5f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) && velocity.x < constants::ball_maxX_velocity)
        {
            velocity.x += 0.5f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isFixed) 
    {
        isFixed = false;
    }

    // We check if the ball has moved off the left hand side of the window
    // If so, we change sign of the x-component of the velocity
    // This will make it move at the same speed, but to the right
    // The ball will appear to bounce back into the window
    if (x() < 0)
        velocity.x = -velocity.x;
    // And similarly for the right hand side of the screen
    if (x() > constants::window_width)
        velocity.x = -velocity.x;

    // We can also do this for the top and bottom of the screen
    if (y() < 0)
        velocity.y = -velocity.y;
    if (y() > constants::window_height)
        destroy();

    if (!isFixed)
    {
        sprite.move(velocity * DeltaTime * constants::delta_time_multiplier);
    }
}

void ball::draw(sf::RenderWindow& window) {
    // Ask the window to draw the sprite for us
    window.draw(sprite);
}
