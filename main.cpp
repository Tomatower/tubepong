#include <chrono>

#include <unistd.h>

#include "gamestate.h"
#include "physics.h"
#include "gui.h"
#include "aicontroller.h"

using namespace openage;

typedef std::chrono::high_resolution_clock Clock;

int main() {
	// Restart forever
	tubepong::Gui gui;
	tubepong::Physics phys;
	tubepong::AIInput ai;
	//TODO KI
	while (1) {
		tubepong::PongState state;
		tube::tube_time_t now = 1;
		
		state.p1.lives.set_drop(0, 3);
		state.p1.id = 0;
		state.p1.y = 0;
		state.p2.lives.set_drop(0, 3);
		state.p2.id = 1;
		state.p2.y = gui.resolution.x-1;
		auto loop_start = Clock::now();
//		std::cout << "1" << std::endl;
		while (state.p1.lives.get(now) > 0 && state.p2.lives.get(now) > 0) {
			phys.processInput(
				state,
				state.p1,
				gui.getInputs(state.p1), 
				now
			);
			
			phys.processInput(
				state,
				state.p2,
				ai.getInputs(state.p2, state.ball, now),
				now
			);

			gui.draw(state, now);
			usleep(10000);	
			
			now += std::chrono::duration_cast<std::chrono::milliseconds>((Clock::now() - loop_start)).count();
			loop_start = Clock::now();
		}
	}
}
