// Ncurses header. The Base of pseudographic output
#include <ncurses.h> //basic lib for pg interface 

// std headers
#include <stdio.h>
#include <stdlib.h> // basic std
#include <unistd.h>

// system and time headers
#include <time.h>
#include <sys/ioctl.h>

// custom headers files
#include"map.h"
#include"dsc_screen.h"

bool run; // Run a Game Loop?

long frame_count;

char c;

struct winsize w;
int winsizex, winsizey;

int screensizey, screensizex;
int pixelsizey, pixelsizex;

int mapy;
int mapx;
char map[20][20];

void delay(unsigned ms) {
	clock_t pause, start;

	pause = ms * (CLOCKS_PER_SEC / 1000);
	start = clock();
	while( (clock() - start) < pause );
}

void start() {
	initscr();

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	mapx = 40;
	mapy = 20;

	map[mapy][mapx];

	mapInit('.');
	frame_count = 0;
	run = true;
}

void FixedGameLoop() {
	while(run) {
		frame_count++;

		// get terminal window size
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		winsizey = w.ws_row;
		winsizex = w.ws_col;
	
		// set screen size
		setScreenSize();
		setPixelSize();

		// clear an old frame
		move(0,0);

		// draw a new frame
		mapDraw();

		move(0,0);

		printw("Hello, World!%d\n", frame_count);
		printw("X: %d Y: %d \n", w.ws_col, w.ws_row);	
		printw("Pixel X size: %d Pixel Y size:%d\n", pixelsizex, pixelsizey);
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
