#ifndef DSC_SCREEN_H
#define DSC_SCREEN_H

#include <math.h>

extern struct winsize w;
extern int winsizex, winsizey;

extern int screensizey, screensizex;
extern int pixelsizex, pixelsizey;


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
}

// draw a screen 
//void showScreen() {
//	
//}

#endif
