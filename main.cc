Kevin
Noah
Luis
//What bullet points did you do:
//Delete this next line to let the code compile
//#error Delete This!
#include "map.h"
#include <unistd.h>

const int MAX_FPS = 90; //Cap frame rate 
const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

//Turns on full screen text mode
void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
	clear();
	endwin(); // End curses mode
	system("clear");
}

int main() {
	turn_on_ncurses();
	Map::createmap();
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	int old_x = -1, old_y = -1;
	int money;
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
	char right = Map::currmap->getTile(x+1,y);
	char left =  Map::currmap->getTile(x-1,y);
	char up =  Map::currmap->getTile(x,y - 1);
	char down =  Map::currmap->getTile(x,y + 1);

		if (ch == 'q' || ch == 'Q') break;

		else if (ch == RIGHT and right != '#' and right != '~') {
			//if money-move and add. 
			x++;
			if (x >= Map::SIZE) x = Map::SIZE - 1; //Clamp value
		}

		else if (ch == LEFT and left != '#' and left != '~') {
			x--;
			if (x < 0) x = 0;
		}
		else if (ch == UP and up != '#' and up != '~') {
			y--;
			if (y < 0) y = 0;
		}
		else if (ch == DOWN and down != '#' and down != '~') {
			y++;
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		}
		if(Map::currmap->getTile(x,y) == Map::TREASURE){
			Map::currmap->setTile(x,y, Map::OPEN);
			money++; 

		}
		//Stop flickering by only redrawing on a change
		if (x != old_x or y != old_y) {
			//clear(); //Put this in if the screen is getting corrupted
			Map::currmap->draw(x,y); 
			mvprintw(Map::DISPLAY+1,0,"X: %i Y: %i\n",x,y);
			mvprintw(Map::DISPLAY+2,0,"Money: %i\n",money);
			refresh();
		}
		old_x = x;
		old_y = y;
		usleep(1'000'000/MAX_FPS);
	}
	turn_off_ncurses();
}

