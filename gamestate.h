#pragma once


#include "tube/simple_continuous.h"
#include "tube/simple_discrete.h"
#include "tube/object.h"
#include "vertex.h"

namespace openage {
namespace tubepong {

struct event {
	int player;
	enum state_e {
		UP, DOWN, START, IDLE, LOST
	} state;
	event(int id, state_e s) : player(id), state(s) {}
	event() : player(0), state(IDLE) {}
};

class PongPlayer : public tube::TubeObject {
public:
	PongPlayer() {
		speed.set_drop(0, 1);
		position.set_drop(0, 0.5);
		lives.set_drop(0, 1);
		state.set_drop(0, event(0, event::IDLE));
		size.set_drop(0, 0.1);
		y = 0;
		id = 0;
	}

	tube::SimpleDiscrete<float> speed;
	tube::SimpleContinuous<float> position;
	tube::SimpleDiscrete<int> lives;
	tube::SimpleDiscrete<event> state;
	tube::SimpleDiscrete<float> size;
	float y;
	int id;
};

class PongBall : public tube::TubeObject {
public:
	tube::SimpleDiscrete<util::vertex<2, float> > speed;
	tube::SimpleContinuous<util::vertex<2, float> > position;
};

class PongState {
public:
	PongPlayer p1;
	PongPlayer p2;

	PongBall ball;

	util::vertex<2, int> resolution;
};

}} // openage::tubepong
