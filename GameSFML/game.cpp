#include "game.h"
#include "interactions.h"

game::game() {
    for (size_t i = 0; i < constants::brick_columns; i++)
    {
        for (size_t j = 0; j < constants::brick_raws; j++)
        {
            float x = constants::brick_offset + (i + 1) * constants::brick_width;
            float y = (j + 1) * constants::brick_height;

            bricks.emplace_back(x, y);
        }
    }

    game_window.setFramerateLimit(60);
}

void game::reset()
{
    for (size_t i = 0; i < constants::brick_columns; i++)
    {
        for (size_t j = 0; j < constants::brick_raws; j++)
        {
            float x = constants::brick_offset + (i + 1) * constants::brick_width;
            float y = (j + 1) * constants::brick_height;

            bricks.emplace_back(x, y);
        }
    }
}

void game::run()
{
    bool pause_key_active{ false };

    while (game_window.isOpen()) {
        // Clear the screen
        game_window.clear(sf::Color::Black);

        sf::Event event;

        while (game_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game_window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        {
            if (!pause_key_active)
            {
                if (state == game_state::paused)
                {
                    state = game_state::running;
                }
                else
                {
                    state = game_state::paused;
                }
            }
            pause_key_active = true;
        }
        else
        {
            pause_key_active = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
        {
            reset();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            game_window.close();


        if (state != game_state::paused)
        {
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
        }
        game_window.display();
    }
}

