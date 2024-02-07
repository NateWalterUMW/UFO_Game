//Nathan Walter
//CPSC 440
//Lab 6

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

#define MAXSPEED 3

class arrowClass
{
public:
	arrowClass();
	~arrowClass();
	void create_arrow_bitmap(ALLEGRO_DISPLAY* display);
	void erase_arrow();
	void move_arrow(int width, int height);
	void drawArrow();
	int getDirection();
	int getSpeed();
	int getX();
	int getY();
	void up();
	void down();
	void right();
	void left();
	void upLeft();
	void upRight();
	void downLeft();
	void downRight();
private:

	int x, y;
	int dir, speed;
	int color;
	int score;
	ALLEGRO_BITMAP* arrow_bmp[8];
};
