#include <algorithm>
#include<cstdlib>
#include<iostream>

#include "game.h"
#include "interactions.h"

// Function to scan all entities and clean up the destroyed ones
void entity_manager::refresh() {
	// We must clean up the alias pointers first, to avoid dangling pointers
	// We simply remove them from their vector
	for (auto& [type, alias_vector] : grouped_entities) {
		// remove_if takes an iterator range and a predicate
		// All the elements for which the predicate is true are moved to the back
		// It returns an iterator to the first moved element
		// erase takes an iterator range and deletes all the elements in the range
		alias_vector.erase(remove_if(begin(alias_vector), end(alias_vector),
			[](const auto& p) { return p->is_destroyed(); }
		),
			end(alias_vector));
	}

	// Now we can safely destroy the objects, now that there are no aliases to them
	all_entities.erase(remove_if(begin(all_entities), end(all_entities),
		[](const auto& p) { return p->is_destroyed(); }
	),
		end(all_entities));
}

// Function to destroy all entities
void entity_manager::clear() {
	// Again, we must clean up the alias pointers first
	grouped_entities.clear();
	all_entities.clear();
}

// Function to update all the entities
void entity_manager::update(float DeltaTime) {
	for (auto& e : all_entities)
		e->update(DeltaTime);
}

// Function to update make all the entities draw themselves
void entity_manager::draw(sf::RenderWindow& window) {
	for (auto& e : all_entities)
		e->draw(window);
}

game::game() {
	game_window.setFramerateLimit(60);      // Max rate is 60 frames per second

	verdana.loadFromFile("C:/Windows/fonts/Verdana.ttf");

	// Configure our text objects
	text_state.setFont(verdana);
	text_state.setPosition(constants::window_width / 2.0f - 150.0f, constants::window_height / 2.0f - 100.0f);
	text_state.setCharacterSize(35);
	text_state.setFillColor(sf::Color::White);
	text_state.setString("Paused");

	text_lives.setFont(verdana);
	text_lives.setPosition(constants::window_width / 2.0f - 115.0f, constants::window_height / 2.0f - 50.0f);
	text_lives.setCharacterSize(35);
	text_lives.setFillColor(sf::Color::White);
	text_lives.setString("Lives: " + std::to_string(lives));

	text_points.setFont(verdana);
	text_points.setPosition( 30.f, constants::window_height - 30.f);
	text_points.setCharacterSize(15);
	text_points.setFillColor(sf::Color::White);
	text_points.setString("Points: " + std::to_string(points));

	text_instructions.setFont(verdana);
	text_instructions.setPosition(constants::window_width / 4, constants::window_height / 3);
	text_instructions.setCharacterSize(15);
	text_instructions.setFillColor(sf::Color::Cyan);
	text_instructions.setString("Aim and press Space to launch the ball!");

	text_pauseinstructions.setFont(verdana);
	text_pauseinstructions.setPosition(constants::window_width / 3.5f, constants::window_height / 1.4f);
	text_pauseinstructions.setCharacterSize(15);
	text_pauseinstructions.setFillColor(sf::Color::Cyan);
	text_pauseinstructions.setString("Press P to continue the game!");

	text_pointsstatement.setFont(verdana);
	text_pointsstatement.setPosition(constants::window_width / 2.0f - 115.0f, constants::window_height / 2.0f);
	text_pointsstatement.setCharacterSize(35);
	text_pointsstatement.setFillColor(sf::Color::White);
	text_pointsstatement.setString("Earned points: " + std::to_string(points));


	if (s_buffer.loadFromFile("game_won.wav"))
	{
		game_won_sound.setBuffer(s_buffer);
		game_won_sound.setVolume(25.f);
	}

	if (s_buffer_lose.loadFromFile("game_over.wav"))
	{
		game_lost_sound.setBuffer(s_buffer_lose);
	}

	if (bg_music.openFromFile("background_music.mp3"))
	{
		bg_music.play();
		bg_music.setVolume(10.f);
		bg_music.setLoop(true);
	}
}

// (Re)initialize the game
void game::reset() {
	lives = constants::player_lives;
	points = 0;

	state = game_state::running;

	// Destroy all the entities and re-create them
	manager.clear();

	soundPlayed = false;

	gameBackground = manager.create<background>(0.0f, 0.0f);
	gameBall = manager.create<ball>(constants::window_width / 2.0f, constants::window_height - 50.f);
	gamePaddle = manager.create<paddle>(constants::window_width / 2.f - constants::paddle_width / 2.f, constants::window_height - constants::paddle_heigh);

	for (int i = 0; i < constants::brick_columns; ++i) {
		for (int j = 0; j < constants::brick_raws; ++j) {
			// Calculate the brick's position
			float x = constants::brick_offset + (i + 1) * constants::brick_width;
			float y = (j + 1) * constants::brick_height;

			// Create the brick object
			manager.create<brick>(x, y);
		}
	}

	createAimingItems();
	
	// Limit the framerate
	game_window.setFramerateLimit(60);      // Max rate is 60 frames per second
}

void game::createAimingItems() 
{
	for (size_t i = 0; i < constants::aim_items_count; i++)
	{

		float time = (i + 1) * constants::aim_offset;

		float x = gameBall.getXA() + gameBall.getVelocity().x * time;
		float y = gameBall.getYA() + gameBall.getVelocity().y * time;

		manager.create<aimItem>(x, y);
	}

	manager.apply_all<aimItem>([this](auto& the_aimItem, size_t index) {
			the_aimItem.setTransparencyIndex(static_cast<transparencyIndex>(index));
		});
}

void game::looseLife() {
	gameBall = manager.create<ball>(constants::window_width / 2.0f, constants::window_height - 50.f);
	manager.apply_all<paddle>([this](auto& the_paddle, size_t index) {
			the_paddle.getSprite()->setPosition(constants::window_width / 2.0f - constants::paddle_width / 2.f, constants::window_height - constants::paddle_heigh);
		});
	gameBall.setIsFixed(true);
	--lives;

	state = game_state::paused;
}

void game::setAndDrawResetWindow() {
	text_pointsstatement.setString("Earned points: " + std::to_string(points));
	text_pauseinstructions.setString("Press R to reset the game!");
	game_window.draw(text_state);
	game_window.draw(text_lives);
	game_window.draw(text_pauseinstructions);
	game_window.draw(text_pointsstatement);
}

// (Re)start the game
void game::run() {
	// Was the pause key pressed in the last frame?
	bool pause_key_active{ false };

	sf::Clock gameFramesClock;

	while (game_window.isOpen()) {
		// Clear the screen
		game_window.clear(sf::Color::Black);

		// Check for any events since the last loop iteration
		sf::Event event;

		CurrentTime = gameFramesClock.getElapsedTime().asSeconds();
		TimeSinceLastFrame = CurrentTime - LastTime;
		LastTime = CurrentTime;

		// If the user pressed "Escape", or clicked on "close", we close the window
		// This will terminate the program
		while (game_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				game_window.close();
		}

		// Check for user input
		// If the user presses "Escape", we jump out of the loop
		// This will terminate the program
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			break;

		// If the user presses "P", we pause/unpause the game
		// To prevent repeated use, we ignore it if it was pressed on the last iteration
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && state != game_state::game_over && state != game_state::player_wins) {
			// If it was not pressed on the last iteration, toggle the status
			if (!pause_key_active) {
				if (state == game_state::paused)
					state = game_state::running;
				else
					state = game_state::paused;
			}
			pause_key_active = true;
		}
		else
			pause_key_active = false;

		// If the user presses "R", we reset the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
			reset();
		}

		if (state != game_state::running)
		{
			switch (state) {
			case game_state::paused:
				text_state.setString("   Paused   ");
				text_pauseinstructions.setString("Press P to continue the game!");
				game_window.draw(text_state);
				game_window.draw(text_lives);
				game_window.draw(text_pauseinstructions);
				break;
			case game_state::game_over:
				if (!soundPlayed)
				{
					game_lost_sound.play();
					soundPlayed = true;
				}
				text_state.setString("   Game over!   ");
				setAndDrawResetWindow();
				break;
			case game_state::player_wins:
				if (!soundPlayed)
				{
					game_won_sound.play();
					soundPlayed = true;
				}
				text_state.setString("   You won!   ");
				setAndDrawResetWindow();
				break;
			default:
				break;
			}
		}
		else {
			// If there are no remaining balls on the screen

			if (manager.get_all<ball>().empty()) {
				looseLife();
			}

			// If there are no remaining bricks on the screen, the player has won!
			if (manager.get_all<brick>().empty())
				state = game_state::player_wins;

			// If the player has used up all their lives, the game is over!
			if (lives <= 0)
				state = game_state::game_over;

			auto aimingItems = manager.get_all<aimItem>();

			// Update the text for the number of remaining lives
			text_lives.setString("Lives: " + std::to_string(lives));

			text_points.setString("Points: " + std::to_string(points));


			// In the paused state, the entities are not updated, only redrawn
				// Calculate the updated graphics
			manager.update(TimeSinceLastFrame);

			/*float ball_x = gameBall.getXA();
			float ball_y = gameBall.getYA();
			auto ball_velocity = gameBall.getVelocity();
			std::cout << "Ball Position: (" << ball_x << ", " << ball_y << ") Velocity: (" << ball_velocity.x << ", " << ball_velocity.y << ")\n";*/

			gameBall.update(TimeSinceLastFrame);

			// For every ball, call a function which
			//    For every brick, call a function which
			//         Calls handle_collision with the ball and the brick as arguments
			manager.apply_all<ball>([this](auto& the_ball, size_t index) {
				manager.apply_all<brick>([&the_ball, this](auto& the_brick, size_t index) {
						bool applyPoints = false;
						bool collide = handle_collisions(the_ball, the_brick, applyPoints);
						if (collide && applyPoints)
						{
							points++;
							int bonusrandomizeInt = rand() % 2;
							if (bonusrandomizeInt == 1)
							{
								manager.create<bonus>(the_brick.GetxA(), the_brick.GetyA());
							}
						}
					});
				});

			// Paddle interaction
			manager.apply_all<ball>([this](auto& the_ball, size_t index) {
				manager.apply_all<paddle>([&the_ball](auto& the_paddle, size_t index) {
						handle_collisions(the_ball, the_paddle);
					});
				});


			// bonus getting collisions with the panel
			manager.apply_all<bonus>([this](auto& the_bonus, size_t index) {
				manager.apply_all<paddle>([&the_bonus, this](auto& the_paddle, size_t index) {
						bool collide = handle_collisions(the_bonus, the_paddle);
						if (collide)
						{
							points++;
						}
					});
				});


			manager.apply_all<paddle>([this](paddle& this_paddle, size_t index) {
					this_paddle.setIsFixed(gameBall.getIsFixed());
				});

			if (gameBall.getIsFixed())
			{
				if (areAimingItemsDestroyed)
				{
					createAimingItems();
					areAimingItemsDestroyed = false;
				}
				manager.apply_all<aimItem>([this](aimItem& the_aimItem, size_t index) {

						float time = (index + 1) * constants::aim_offset;

						float x = gameBall.getXA() + gameBall.getVelocity().x * time;
						float y = gameBall.getYA() + gameBall.getVelocity().y * time;

						the_aimItem.setXA(x);
						the_aimItem.setYA(y);

					});
			}
			else if (!manager.get_all<aimItem>().empty())
			{
				manager.apply_all<aimItem>([this](aimItem& the_aimItem, size_t index) {
						the_aimItem.destroy();
					});
				areAimingItemsDestroyed = true;
			}

			manager.refresh();

			// Display the updated graphics
			manager.draw(game_window);

			if (gameBall.getIsFixed())
			{
				game_window.draw(text_instructions);
			}
		}
		game_window.draw(text_points);
		game_window.display();
	}
}

