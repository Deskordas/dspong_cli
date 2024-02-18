#ifndef MAP_H
#define MAP_H
extern int mapy;
extern int mapx;
extern char map[20][20];

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

void setCell(char c, int x, int y) {
	map[y][x] = c;
}

#endif
