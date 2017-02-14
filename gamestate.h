#pragma once

#include "tube/simple_continuous.h"
#include "tube/simple_discrete.h"
#include "tube/object.h"
#include "vertex.h"

namespace openage {
namespace tubepong {

struct event {
	int player;
	enum {
		UP, DOWN, START, IDLE, LOST
	} state;
};

class PongPlayer : public tube::TubeObject {
public:
	tube::SimpleDiscrete<float> speed;
	tube::SimpleContinuous<float> position;
	tube::SimpleDiscrete<int> lives;
	tube::SimpleDiscrete<event> state;
	float y;
	int id;
};

class PongBall : public tube::TubeObject {
public:
	tube::SimpleContinuous<util::vertex<2, float> > speed;
	tube::SimpleContinuous<util::vertex<2, float> > position;
};

class PongState {
public:
	tube::SimpleDiscrete<float> ballspeed;

	PongPlayer p1;
	PongPlayer p2;

	PongBall ball;
};

}} // openage::tubepong
