#include <SFML/Graphics.hpp>
#include <vector>

#include "background.h"
#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include "interactions.h"
#include "constants.h"

using namespace std::literals;

//class creature {
//
//    static std::mt19937 mt;
//    static std::bernoulli_distribution bd;
//
//    float vx{ 4.0f };
//    float vy{ 4.0f };
//    sf::Vector2f velocity;
//
//    sf::CircleShape circle;
//public:
//    
//    creature(float x, float y) {
//        velocity = { vx, vy };
//        circle.setPosition(x, y);
//
//        circle.setRadius(5.0f);
//        circle.setFillColor(sf::Color::Red);
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(circle);
//    }
//
//    void update() {
//        vx = bd(mt) ? vx : -vx;
//        vy = bd(mt) ? vy : -vy;
//
//        circle.move({ vx, vy });
//    }
//};
//
//std::mt19937 creature::mt;
//std::bernoulli_distribution creature::bd;

int main()
{

    /*creature the_creature(constants::window_width / 2.0,
        constants::window_height / 2.0);*/

    background the_background(0.0f, 0.0f);

    ball the_ball(constants::window_width / 2.0f, constants::window_height / 2.0f);

    std::vector<brick> bricks;

    for (size_t i = 0; i < constants::brick_columns; i++)
    {
        for (size_t j = 0; j < constants::brick_raws; j++)
        {
            float x = constants::brick_offset + (i + 1) * constants::brick_width;
            float y = (j + 1) * constants::brick_height;

            bricks.emplace_back(x, y);
        }
    }

    paddle the_paddle(constants::window_width / 2.0f, constants::window_height - constants::paddle_heigh);

    sf::RenderWindow game_window{ {constants::window_width, constants::window_height},
                   "Simple Breakout Game Version 1"s, };

    game_window.setFramerateLimit(60);

    the_paddle.draw(game_window);


    while (game_window.isOpen()) {
        // Clear the screen
        game_window.clear(sf::Color::Black);

        sf::Event event;

        while (game_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game_window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            game_window.close();

        /*the_creature.update();
        the_creature.draw(game_window);*/

        the_background.update();
        the_ball.update();
        the_paddle.update();

        for (auto& b : bricks)
        {
            b.update();
        }

        handle_collisions(the_ball, the_paddle);

        for (auto& b : bricks)
        {
            handle_collisions(the_ball, b);
        }

        bricks.erase(std::remove_if(
            std::begin(bricks),
            std::end(bricks),
            [](const brick& b) { return b.is_destroyed(); }),
            std::end(bricks));

        the_background.draw(game_window);
        the_ball.draw(game_window);
        the_paddle.draw(game_window);

        for (auto& i : bricks)
        {
            i.draw(game_window);
        }

        game_window.display();
    }
}