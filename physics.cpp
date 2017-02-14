#include "physics.h"

namespace openage {
namespace tubepong {

const float extrapolating_time = 2.0f;

void Physics::processInput(PongState &state, PongPlayer &player, std::vector<event> &events, const tube::tube_time_t &now) {
	for (auto evnt : events) {
		//Process only if the future has changed 
		if (player.state.get(now).state != evnt.state) {
			player.state.set_drop(now, evnt);
			switch(evnt.state) {
			case event::UP:
				player.position.set_drop(now+extrapolating_time, 
						player.position.get(now) -
							(player.speed.get(now+extrapolating_time) - player.speed.get(now) / 2 + player.speed.get(now)));
				break;
			case event::DOWN:
					player.position.set_drop(now+extrapolating_time, 
						player.position.get(now) +
							(player.speed.get(now+extrapolating_time) - player.speed.get(now) / 2 + player.speed.get(now)));
				break;
			case event::IDLE:
					player.position.set_drop(now+extrapolating_time,
						player.position.get(now));
				break;
			case event::START:
				if (player.state.get(now).state == event::LOST) {
					state.ball.position.set_drop(now, util::vertex<2, float>(0.5, 0.5));
				}
				break;
			default:
				break;
			}
		}
		
		// TODO Paddle collission will be handled on-demand (framebased :) )
		

		// TODO Wall collission will be handled whenever a reflect is triggered


		// Game loose condition
		if (state.ball.position.get(now)[0] < 0) {
			state.p1.lives.set_drop(now, state.p1.lives.get(now) - 1);
		}
		if (state.ball.position.get(now)[0] > 1) {
			state.p2.lives.set_drop(now, state.p2.lives.get(now) - 1);
		}
	}
}

}} // openage::tubepong
