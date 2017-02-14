#include "gui.h"

#include <ncurses.h>
#include <stdio.h>

namespace openage {
namespace tubepong {

std::vector<event> &Gui::getInputs(const PongPlayer &player) {
	input_cache.clear();
	event evnt;
	evnt.player = player.id;
	evnt.state = event::IDLE;
	timeout(0);
	int c = getch();
	//mvprintw(0,1, "IN: %i", c);
	switch (c) {
	case KEY_DOWN:
		evnt.state = event::DOWN;
		input_cache.push_back(evnt);
		mvprintw(1,1, "DOWN");
		break;
	case KEY_UP:
		evnt.state = event::UP;
		input_cache.push_back(evnt);
		mvprintw(1,1, "UP");
		break;
	case ' ':
		evnt.state = event::START;
		break;
	default:
		break;
	}

	return input_cache;
}

enum {
	COLOR_PLAYER1 = 1,
	COLOR_PLAYER2 = 2,
	COLOR_BALL = 3,
};

Gui::Gui() {
	initscr();
	start_color();
	init_pair(COLOR_PLAYER1, COLOR_BLUE,COLOR_BLACK);
	init_pair(COLOR_PLAYER2, COLOR_RED,COLOR_BLACK);
	init_pair(COLOR_BALL   , COLOR_BLUE,COLOR_WHITE);

	keypad(stdscr,true);
	noecho();
	curs_set(0);
	getmaxyx(stdscr,resolution.y,resolution.x);

	mvprintw(4,5,"          oooooooooo                                  ");
	mvprintw(5,5,"          888    888  ooooooo    ooooooo    oooooooo8 ");
	mvprintw(6,5,"          888oooo88 888     888 888   888  888    88o ");
	mvprintw(7,5,"          888       888     888 888   888   888oo888o ");
	mvprintw(8,5,"         o888o        88ooo88  o888o o888o     88 888");
	mvprintw(9,5,"                                            888ooo888 ");

	getch();
}

void Gui::draw(PongState &state, const tube::tube_time_t &now) {
	erase();
	//Print Score
	mvprintw(2, resolution.x/2-2, "%i | %i",
			state.p1.lives.get(now),
			state.p2.lives.get(now));

	mvvline(0, resolution.x/2, ACS_VLINE, resolution.y);
	mvprintw(0, 1, "NOW:  %f", now);
	mvprintw(1, 1, "BALL: %i, %i", state.ball.position.get(now)[0],
	         state.ball.position.get(now)[1]);
	mvprintw(2, 1, "P1:   %f, %f, %i", state.p1.position.get(now), state.p1.y, state.p1.state.get(now).state);
	mvprintw(3, 1, "P2:   %f, %f, %i", state.p2.position.get(now), state.p2.y, state.p2.state.get(now).state);


	for(int i=-1; i<2; i++) {

		attron(COLOR_PAIR(COLOR_PLAYER1));
		mvprintw(state.p1.position.get(now)+i,
				 state.p1.y,"|");
		attroff(COLOR_PAIR(COLOR_PLAYER1));
		attron(COLOR_PAIR(COLOR_PLAYER2));
		mvprintw(state.p2.position.get(now)+i,
				 state.p2.y,"|");
		attroff(COLOR_PAIR(COLOR_PLAYER2));
	}
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(COLOR_BALL));

	mvprintw(state.ball.position.get(now)[0],
	         state.ball.position.get(now)[1],
	         "o");
	attroff(COLOR_PAIR(COLOR_BALL));
}

}} // openage::tubepong
