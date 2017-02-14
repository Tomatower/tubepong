#pragma once

#include <vector>

#include "gamestate.h"

namespace openage {
namespace tubepong {

class Physics {
public:
	void processInput(PongState &, PongPlayer &, std::vector<event> &events, const tube::tube_time_t &now);

};

}} // openage::tubepong
