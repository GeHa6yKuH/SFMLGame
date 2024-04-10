#pragma once

#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "ball.h"
#include "paddle.h"
#include "brick.h"

bool is_interacting(const entity& e1, const entity& e2);

void handle_collisions(ball& b, const paddle& p);

void handle_collisions(ball& b, brick& br);

#endif
