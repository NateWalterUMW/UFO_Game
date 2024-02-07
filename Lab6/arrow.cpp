//Nathan Walter
//CPSC 440
//Lab 6

#include "arrow.h"

arrowClass::arrowClass()
{
	speed = 0;
	x = 100;
	y = 100;
	dir = 1;
	score = 0;
	for (int i = 0; i < 8; i++)
	{
		arrow_bmp[i] = NULL;
	}
}

arrowClass::~arrowClass()
{
	for (int i = 0; i < 8; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
}

void arrowClass::drawArrow()
{
	al_draw_bitmap(arrow_bmp[getDirection()], getX(), getY(), 0);
}

void arrowClass::create_arrow_bitmap(ALLEGRO_DISPLAY* display)
{
	for (int i = 0; i < 8; i++)
	{
		arrow_bmp[i] = al_create_bitmap(64, 64);
		if (!arrow_bmp[i]) {
			exit(1);
			al_destroy_display(display);
		}
		al_set_target_bitmap(arrow_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		int x = 32;
		int y = 32;

		//switch statements to draw different varients based on direction of movement
		switch (i)
		{
		case 0:	//up
			al_draw_filled_triangle(x - 27, y, x, y + 18, x + 27, y, al_map_rgb(255, 255, 0));
			break;
		case 1:	//right
			al_draw_filled_triangle(x - 27, y, x - 27, y + 12, x + 27, y, al_map_rgb(255, 255, 0));
			break;
		case 2:	//down
			al_draw_line(x - 27, y - 16, x - 27, y - 27, al_map_rgb(255, 255, 255), 2);
			al_draw_line(x + 27, y - 16, x + 27, y - 27, al_map_rgb(255, 255, 255), 2);
			break;
		case 3:	//left
			al_draw_filled_triangle(x + 27, y, x + 27, y + 12, x - 27, y, al_map_rgb(255, 255, 0));
			break;
		case 4:	//up-left
			al_draw_filled_triangle(x - 27, y, x + 15, y + 18, x + 20, y, al_map_rgb(255, 255, 0));
			break;
		case 5:	//up-right
			al_draw_filled_triangle(x - 20, y, x - 15, y + 18, x + 27, y, al_map_rgb(255, 255, 0));
			break;
		case 6:	//down-left
			al_draw_line(x - 27, y - 16, x - 16, y - 27, al_map_rgb(255, 255, 255), 2);
			al_draw_line(x + 21, y - 21, x + 27, y - 27, al_map_rgb(255, 255, 255), 2);
			break;
		case 7:	//down-right
			al_draw_line(x + 27, y - 16, x + 16, y - 27, al_map_rgb(255, 255, 255), 2);
			al_draw_line(x - 21, y - 21, x - 27, y - 27, al_map_rgb(255, 255, 255), 2);
			break;
		}

		//this draws the default ufo bitmap
		al_draw_filled_circle(x, y - 10, 15, al_map_rgb(255, 255, 255));
		al_draw_filled_circle(x, y - 10, 13, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x, y - 10, 7, al_map_rgb(0, 255, 0));
		al_draw_filled_circle(x - 3, y - 11, 2, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x + 3, y - 11, 2, al_map_rgb(0, 0, 0));
		al_draw_filled_ellipse(x, y + 2, x - 3, 8, al_map_rgb(255, 92, 51));
		al_draw_filled_ellipse(x, y, x - 3, 8, al_map_rgb(50, 50, 50));
		al_draw_filled_circle(x, y + 3, 2, al_map_rgb(255, 255, 0));
		al_draw_filled_circle(x + 20, y, 2, al_map_rgb(255, 255, 0));
		al_draw_filled_circle(x - 20, y, 2, al_map_rgb(255, 255, 0));
	}
}

void arrowClass::erase_arrow()
{
	int left = x;
	int top = y;
	int right = x + 32;
	int bottom = y + 32;

	al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void arrowClass::up()
{
	dir = 0;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::down()
{
	dir = 2;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::left()
{
	dir = 3;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::right()
{
	dir = 1;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::upLeft()
{
	dir = 4;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::upRight()
{
	dir = 5;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::downLeft()
{
	dir = 6;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::downRight()
{
	dir = 7;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

int arrowClass::getDirection()
{
	return dir;
}

int arrowClass::getSpeed()
{
	return speed;
}

int arrowClass::getX()
{
	return x;
}

int arrowClass::getY()
{
	return y;
}

void arrowClass::move_arrow(int width, int height)
{
	//update arrow position based on direction
	switch (dir)
	{
	case 0:	//up
		y -= speed;
		break;
	case 1:	//right
		x += speed;
		break;
	case 2:	//down
		y += speed;
		break;
	case 3:	//left
		x -= speed;
		break;
	case 4:	//up-left
		x -= speed;
		y -= speed;
		break;
	case 5:	//up-right
		x += speed;
		y -= speed;
		break;
	case 6:	//down-left
		x -= speed;
		y += speed;
		break;
	case 7:	//down-right
		x += speed;
		y += speed;
		break;
	}

	//keep arrow inside the screen (collision detection)
	if (x > width - 64)	//right
	{
		x = width - 64;
		speed = 0;
	}

	if (x < 0)	//left
	{
		x = 0;
		speed = 0;
	}

	if (y > height - 83)	//bottom	//was - 43
	{
		y = height - 83;
		speed = 0;
	}

	if (y < -5)	//top
	{
		y = -5;
		speed = 0;
	}
}
