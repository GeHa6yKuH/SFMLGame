#include <SFML/Graphics.hpp>
#include <vector>

#include "background.h"
#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include "interactions.h"
#include "constants.h"
#include "game.h"

using namespace std::literals;

int main()
{
	game the_game;
	the_game.reset();
	the_game.run();
}