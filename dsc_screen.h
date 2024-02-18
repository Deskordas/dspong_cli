#ifndef DSC_SCREEN_H
#define DSC_SCREEN_H

#include <math.h>
#include <ncurses.h>


extern struct winsize w;
extern int winsizex, winsizey;

extern int screensizey, screensizex;
extern int pixelsizex, pixelsizey;

extern int currentScrSize[2];
extern int previousScrSize[2];

// getting current tty windows size
void getWinSize() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
}

//set pixel size
void setPixelSize() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	// in 50 x 50 screen pixel size must 1 x 1 be
	if (screensizey < 50) {pixelsizey = 1;} else {pixelsizey = ceil(screensizey / 50);}
	if (screensizex < 50) {pixelsizex = 1;} else {pixelsizex = ceil(screensizex / 50);}
}

//set screen size
void setScreenSize() {	
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	screensizey = w.ws_row - 1;
	screensizex = w.ws_col - 1;
	
	previousScrSize[0] = currentScrSize[0];
	previousScrSize[1] = currentScrSize[1];
	
	currentScrSize[0] = screensizey;
	currentScrSize[1] = screensizex;
}

void drawPixel(int x, int y, char c) {
	move(x,y);
	for (int i = 0; i < pixelsizex; i++) {
		for (int f = 0; f < pixelsizey; f++) {
		move(x+f,y+i);
		printw("%c", c);
		}
	}
}

bool scrSizeWasChanged() {
	if (currentScrSize[0] != previousScrSize[0]) {
		clear();
		refresh();
		return true;
	} else if (currentScrSize[1] != previousScrSize[1]) {
		clear();
		refresh();
		return true;
	} else {
		return false;
	} 
}

// draw a screen 
//void showScreen() {
//	
//}

#endif
