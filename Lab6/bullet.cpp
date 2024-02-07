//Nathan Walter
//CPSC 440
//Lab 6

#include "bullet.h"

bullet::bullet()
{
	alive = false;;
	srand(time(0));
}
bool bullet::getStatus()
{
	return alive;
}

void bullet::fire()
{
	x = rand() % 615 + 10;
	y = 10;
	alive = true;
}

void bullet::erase_bullet()
{
	//draw a black bullet
	al_draw_filled_circle(x, y, 8, al_map_rgb(0, 0, 0));
	al_draw_line(x, y, x - 4, y - 6, al_map_rgb(0, 0, 0), 4);
}

int bullet::move_bullet(int arrowX, int arrowY, int width, int length, int height)
{
	y++;
	//draw the bullet
	al_draw_filled_circle(x, y, 7, al_map_rgb(255, 80, 80));	//note: I was having trouble drawing a bitmap for the bullet,
	al_draw_line(x, y, x - 4, y - 6, al_map_rgb(0, 255, 0), 4);	//so I just used primitives. (still 2 primitives + 2 colors)

	if (x > arrowX && x < arrowX + width && y > arrowY && y < arrowY + length) {
		al_draw_filled_circle(x, y, 8, al_map_rgb(0, 0, 0));	//draw black to erase the bullet
		al_draw_line(x, y, x - 4, y - 6, al_map_rgb(0, 0, 0), 4);
		alive = false;
		return 1;
	}
	if (y > height - 33)	//was + 5
		alive = false;
	
	return 0;
}

