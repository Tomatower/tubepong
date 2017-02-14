#include "aicontroller.h"

namespace openage {
namespace tubepong {

std::vector<event> &AIInput::getInputs(
		const PongPlayer &player,
		const PongBall &ball,
		const tube::tube_time_t &now) {
	this->event_cache.clear();

	if (ball.position.get(now)[0] > player.position.get(now)) {
		event evnt;
		evnt.player = player.id;
		evnt.state = event::UP;
		event_cache.push_back(evnt);
	} else {
		event evnt;
		evnt.player = player.id;
		evnt.state = event::DOWN;
		event_cache.push_back(evnt);
	}

	return this->event_cache;
}

}} // openage::tubepong
