//Nathan Walter
//CPSC 440
//Lab 6

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <string>
#include "arrow.h";
#include "bullet.h"

int main(void)
{
	arrowClass arrow;
	bullet mybullet[10];
	int score = 0;
	bool redraw = true;
	const int FPS = 60;

	//variables
	int width = 640;
	int height = 520;	//was 480
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font24 = al_load_ttf_font("GROBOLD.ttf", 24, 0);

	arrow.create_arrow_bitmap(display);		//create the arrow bitmap
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();	//create the event queue
	timer = al_create_timer(1.0 / FPS);		//create the timer
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	arrow.drawArrow();
	al_flip_display();
	al_start_timer(timer);

	//display the controls
	std::cout << "Welcome to the UFO game! Hit as many apples as you can before the timer runs out.\n\n";
	std::cout << "-- Controls --\n\n";
	std::cout << "W -> up\n";
	std::cout << "S -> down\n";
	std::cout << "A -> left\n";
	std::cout << "D -> right\n";
	std::cout << "Q -> up-left\n";
	std::cout << "E -> up-right\n";
	std::cout << "Z -> down-left\n";
	std::cout << "C -> down-right\n";
	std::cout << "ESC -> exit the game\n\n";

	int msRemain = 30.0 * FPS;	//milliseconds remaining of countdown
	while (!done)	//game loop
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			for (int i = 0; i < 10; i++)
			{
				if (!mybullet[i].getStatus()) {
					mybullet[i].fire();
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:	//exit
				done = true;
				break;
			case ALLEGRO_KEY_W:		//up
				arrow.up();
				break;
			case ALLEGRO_KEY_S:		//down
				arrow.down();
				break;
			case ALLEGRO_KEY_A:		//left
				arrow.left();
				break;
			case ALLEGRO_KEY_D:		//right
				arrow.right();
				break;
			case ALLEGRO_KEY_Q:		//up-left
				arrow.upLeft();
				break;
			case ALLEGRO_KEY_E:		//up-right
				arrow.upRight();
				break;
			case ALLEGRO_KEY_Z:	//down-left
				arrow.downLeft();
				break;
			case ALLEGRO_KEY_C:		//down-right
				arrow.downRight();
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if (arrow.getSpeed() != 0) {
				arrow.erase_arrow();
				arrow.move_arrow(width, height);
			}
			arrow.drawArrow();
			for (int i = 0; i < 10; i++)
			{
				mybullet[i].erase_bullet();
				score += mybullet[i].move_bullet(arrow.getX(), arrow.getY(), 64, 64, height);

				al_draw_filled_rectangle(0, height - 40, width, height, al_map_rgb(15, 15, 15));	//draw box on bottom to display score and countdown, erase old text

				std::string scoreAsString = std::to_string(score);		//convert score to const char* so it can print to display
				const char* scoreAsChar = scoreAsString.c_str();
				al_draw_textf(font24, al_map_rgb(102, 255, 102), 8, height - 32, 0, "Score: %s", scoreAsChar);	//display the current score

				std::string countdown = std::to_string(msRemain / FPS);		//convert countdown to const char* so it can print to display
				const char* countdownChar = countdown.c_str();
				al_draw_textf(font24, al_map_rgb(102, 255, 102), width - 8, height - 32, ALLEGRO_ALIGN_RIGHT, "%s seconds", countdownChar);	//display the current countdown

				if (msRemain == 0)	//if countdown reaches 0
				{
					al_draw_filled_rectangle(width / 2, height - 40, width, height, al_map_rgb(15, 15, 15));
					al_draw_text(font24, al_map_rgb(102, 255, 102), width - 8, height - 32, ALLEGRO_ALIGN_RIGHT, "Time's up!");
				}
			}
		}
		if (msRemain == 0)	//if the timer reaches 0
		{
			done = true;
		}
		msRemain--;		//decrement the countdown each loop through
		al_flip_display();
	}
	al_rest(5.0);
	
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}
