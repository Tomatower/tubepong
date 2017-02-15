#include "physics.h"

#include <ncurses.h>

namespace openage {
namespace tubepong {

const float extrapolating_time = 200.0f;
const int init_recursion_limit = 3;

void Physics::processInput(PongState &state, PongPlayer &player, std::vector<event> &events, const tube::tube_time_t &now) {
	update_ball(state.ball, now, init_recursion_limit);

	for (auto evnt : events) {
		//Process only if the future has changed 
		if (player.state.get(now).state != evnt.state) {
			player.state.set_drop(now, evnt);
			switch(evnt.state) {
			case event::UP:
				player.speed.set_drop(now + extrapolating_time, 0);
				player.speed.set_insert(now, -1);
				player.position.set_drop(now+extrapolating_time, 
						player.position.get(now) +
							(player.speed.get(now+extrapolating_time) - player.speed.get(now) / 2 + player.speed.get(now)));
				evnt.state = event::IDLE;
				player.state.set_drop(now + extrapolating_time, evnt);
				break;
			case event::DOWN:
				player.speed.set_drop(now + extrapolating_time, 0);
				player.speed.set_insert(now, 1);
				player.position.set_drop(now+extrapolating_time, 
						player.position.get(now) +
							(player.speed.get(now+extrapolating_time) - player.speed.get(now) / 2 + player.speed.get(now)));
				evnt.state = event::IDLE;
				player.state.set_drop(now + extrapolating_time, evnt);
				break;
			case event::IDLE:
					player.position.set_drop(now+extrapolating_time,
						player.position.get(now));
				break;
			case event::START:
				if (player.state.get(now).state == event::LOST) {
					state.ball.position.set_drop(now, util::vertex<2, float>(0.5, 0.5));
				}
				update_ball(state.ball, now, init_recursion_limit);
				break;
			default:
				break;
			}
		}
	}

	// TODO Paddle collission will be handled on-demand (framebased :) )
	auto ball = state.ball.position.get(now);
	if (ball[0] <=2
			&& ball[0] > state.p1.position.get(now) - state.p1.size.get(now) / 2
			&& ball[0] < state.p1.position.get(now) + state.p1.size.get(now) / 2
			&& state.ball.speed.get(now)[0] < 0) {
		//Ball hit the paddel in this frame
		auto s = state.ball.speed.get(now);
		s[0] *= -1.0;
		state.ball.speed.set_drop(now, s);
		
		update_ball(state.ball, now, init_recursion_limit);

	}
	if (state.ball.position.get(now)[0] > 1) {
		state.p2.lives.set_drop(now, state.p2.lives.get(now) - 1);
	}

	// Game loose condition
	if (state.ball.position.get(now)[0] < 0) {
		state.p1.lives.set_drop(now, state.p1.lives.get(now) - 1);
	}
	if (state.ball.position.get(now)[0] > 1) {
		state.p2.lives.set_drop(now, state.p2.lives.get(now) - 1);
	}
}

void Physics::update_ball(PongBall &ball, const tube::tube_time_t &now, int recursion_limit) {
	//calculate the ball takes to hit a wall.
	auto speed = ball.speed.get(now);
	auto pos = ball.position.get(now);

	float ty = 0;
	if (speed[1] > 0) { //the ball is travelling downwards
		ty = (1 - pos[1]) / speed[1];
	} else {
		ty = (pos[1] - 1) / speed[1];
	}
	mvprintw(10, 0, "TY: %f", ty);
	auto hit_pos = pos + speed * ty;
	ball.position.set_drop(now + ty, hit_pos);
	speed[1] *= -1;
	ball.speed.set_drop(now + ty, speed);
	
	if (recursion_limit > 1) {
		update_ball(ball, now + ty, recursion_limit - 1);
	}
}

}} // openage::tubepong
