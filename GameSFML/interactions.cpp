#include "interactions.h"
#include "game.h"

bool is_interacting(const entity& e1, const entity& e2)
{
	auto box1 = e1.get_bounding_box();
	auto box2 = e2.get_bounding_box();
	return box1.intersects(box2);
}

bool handle_collisions(ball& b, paddle& p)
{
	if (is_interacting(b, p))
	{
		b.move_up();
		p.playSound();
		return true;
	}
	return false;
}

bool handle_collisions(ball& ball, brick& brick, bool& destroyedBrick)
{
	if (is_interacting(brick, ball))
	{
		brick.weaken();
		ball.playSound();

		if (brick.is_too_weak())
		{
			brick.playSound();
			destroyedBrick = true;
			brick.destroy();
		}

		float left_overlap = ball.right() - brick.left();
		float right_overlap = brick.right() - ball.left();
		float top_overlap = ball.bottom() - brick.top();
		float bottom_overlap = brick.bottom() - ball.top();

		bool from_left = std::abs(left_overlap) < std::abs(right_overlap);
		bool from_top = std::abs(top_overlap) < std::abs(bottom_overlap);

		float min_x_overlap = from_left ? left_overlap : right_overlap;
		float min_y_overlap = from_top ? top_overlap : bottom_overlap;

		if (std::abs(min_x_overlap) < std::abs(min_y_overlap))
		{
			if (from_left)
				ball.move_left();
			else
				ball.move_right();
		}
		else {
			if (from_top)
			{
				ball.move_up();
			}
			else {
				ball.move_down();
			}
		}
		return true;
	}
	return false;
}

bool handle_collisions(bonus& b, paddle& p)
{
	if (is_interacting(b, p))
	{
		p.playSound1();
		b.destroy();
		return true;
	}
	return false;
}
