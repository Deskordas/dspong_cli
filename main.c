#include <ncurses.h> //basic lib for pg interface 

#include <stdio.h>
#include <stdlib.h> // basic std
#include <unistd.h>

#include <time.h>

char map[10][10];
bool run;

long frame_count;

char c;

void delay(unsigned ms) {
	clock_t pause, start;

	pause = ms * (CLOCKS_PER_SEC / 1000);
	start = clock();
	while( (clock() - start) < pause );
}

void mapInit(char filling_ch) {
	for (int i = 0; i < 10; i++) {
		for (int f = 0; f < 10; f++) {
			map[i][f] = filling_ch;
		}
	}
}

void mapDraw() {
	printw("\n");
	for (int i = 0; i < 10; i++) {
		for (int f = 0; f < 10; f++) {
			printw("%c", map[i][f]);
		}
		printw("\n");
	}
}

void start() {
	initscr();
	mapInit('.');
	frame_count = 0;
	run = true;
}

void gameLoop() {
	while(run) {
		frame_count++;

		// clear an old frame
		move(0,0);
		
		// draw a new frame
		printw("Hello, World!%d", frame_count);
		mapDraw();

		// flip
		refresh();

		delay(30);

	}
}

void stop() {
	run = false;
	endwin();
}

int main (int argc, char *argv[]) {
	start();
	
	gameLoop();

	stop();
	return 0;
}
