#pragma once

#ifndef CONSTANTS_H
#define CONSTANTS_H

struct constants {
	static constexpr int window_width{ 520 };
	static constexpr int window_height{ 450 };
	static constexpr int aim_items_count{ 5 };
	static constexpr float aim_offset{ 5.f };
	static constexpr float ball_speed{ 6.0f };
	static constexpr float bonus_speed{ 4.0f };
	static constexpr float paddle_width{ 60.f };
	static constexpr float paddle_heigh{ 20.f };
	static constexpr float brick_width{ 43.f };
	static constexpr float brick_height{ 20.f };
	static constexpr float brick_offset{ brick_width / 2.f };
	static constexpr int brick_HP{ 3 };
	static constexpr int brick_columns{10};
	static constexpr int brick_raws{4};
	static constexpr int player_lives{3};
};

#endif // !CONSTANTS_H
