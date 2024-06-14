#pragma once

#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "bonus.h"

bool is_interacting(const entity& e1, const entity& e2);

bool handle_collisions(ball& b, paddle& p);

bool handle_collisions(ball& b, brick& br, bool& destroyedBrick);

bool handle_collisions(bonus& b, paddle& p);

#endif
