#include <ncurses.h> //basic lib for pg interface 

#include <stdio.h>
#include <stdlib.h> // basic std
#include <unistd.h>

#include <time.h>

#include <sys/ioctl.h>

int mapx, mapy; // map size
char map[1000][1000]; // empty map

bool run; // Run a Game Loop?

long frame_count;

char c;

struct winsize w;
int winsizex, winsizey;


void delay(unsigned ms) {
	clock_t pause, start;

	pause = ms * (CLOCKS_PER_SEC / 1000);
	start = clock();
	while( (clock() - start) < pause );
}

void mapInit(char filling_ch) {
	for (int i = 0; i < mapy-1; i++) {
		for (int f = 0; f < mapx-1; f++) {
			map[i][f] = filling_ch;
		}
	}
}

void mapDraw() {
	printw("\n");
	for (int i = 0; i < mapy-1; i++) {
		for (int f = 0; f < mapx-1; f++) {
			printw("%c", map[i][f]);
		}
		printw("\n");
	}
}

void start() {
	initscr();

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	mapx = w.ws_col;
	mapy = w.ws_row;

	mapInit('.');
	frame_count = 0;
	run = true;
}

void FixedGameLoop() {
	while(run) {
		frame_count++;

		// get terminal window size
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		winsizey = mapy = w.ws_row;
		winsizex = mapx = w.ws_col;
		

		// clear an old frame
		move(0,0);
		
		mapInit('.');
		mapDraw();
		move (0,0);

		// draw a new frame
		printw("Hello, World!%d\n", frame_count);
		printw("X: %d Y: %d", w.ws_col, w.ws_row);

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
	
	FixedGameLoop();

	stop();
	return 0;
}
