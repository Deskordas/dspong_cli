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

int currentScrSize[2];
int previousScrSize[2];

void delay(unsigned ms) {
	clock_t pause, start;

	pause = ms * (CLOCKS_PER_SEC / 1000);
	start = clock();
	while( (clock() - start) < pause );
}

void start() {

	previousScrSize[0] = 0;
	previousScrSize[1] = 0;

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
	
		// screen setting
		setScreenSize();
		setPixelSize();


		// clear an old frame
		move(0,0);

		// draw a new frame
		drawPixel(10,0,'.');

		move(0,0);

		printw("Hello, World!%d\n", frame_count);
		printw("Current: X: %d Y: %d \n", currentScrSize[1], currentScrSize[0]);
		printw("Previous: X: %d Y: %d \n", previousScrSize[1], previousScrSize[0]);
		printw("Pixel X size: %d Pixel Y size:%d\n", pixelsizex, pixelsizey);
		
		printw("%b", scrSizeWasChanged());

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
