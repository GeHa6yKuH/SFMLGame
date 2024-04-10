#pragma once

#ifndef GAME_H
#define GAME_H

#include "background.h"
#include "ball.h"
#include "brick.h"
#include "constants.h"
#include "paddle.h"
#include <vector>

class game {
	sf::RenderWindow game_window{ {constants::window_width, constants::window_height},
				   "Simple Breakout Game Version 9", };

	background the_background{0.f, 0.f};

	ball the_ball{ constants::window_width / 2.0f, constants::window_height / 2.0f };

	paddle the_paddle{ constants::window_width / 2.0f, constants::window_height - constants::paddle_heigh };

    std::vector<brick> bricks;

    enum class game_state {paused, running};

	game_state state{ game_state::running };

public:

	game();

	void reset();

	void run();
};

#endif // !GAME_H
