#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;


int main()
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *player = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *font2 = NULL;
	ALLEGRO_FONT *font3 = NULL;

	int lives = 3;
	int time = 9000;
	int speed = 2;
	bool collect = false;

	//these two variables hold the x and y positions of the player
	//initalize these variables to where you want your player to start
	float player_x = 50;
	float player_y = 50;

	//here's our key states. they're all starting as "false" because nothing has been pressed yet.
	//the first slot represents "up", then "down", "left" and "right"
	bool key[4] = { false, false, false, false };

	//don't redraw until an event happens
	bool redraw = true;

	//this controls our game loop
	bool doexit = false;

	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//get the keyboard ready to use
	al_install_keyboard();

	font = al_load_ttf_font("digital-7.ttf", 50, NULL);
	if (font == NULL)
		cout << "ooops" << endl;

	timer = al_create_timer(.02);

	display = al_create_display(640, 480);

	player = al_create_bitmap(32, 32);

	al_set_target_bitmap(player);

	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	//these lines tell teh event source what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//new! tell the event queue that it should take keyboard events, too
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	//so the game loop is set to act on "ticks" of the timer OR keyboard presses
	//OR the mouse closing the display
	while (!doexit)
	{
		time--;
		//prints out player's coordinates
		cout << player_x << " , " << player_y << endl;

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the movement algorithm

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//if the up button is pressed AND we're still below the top wall,
			//move the box "up" by 4 pixels
			if ((key[0] && player_y >= 2) &&
				!(player_x > 70 && player_x < 298 && player_y < 202 && player_y>194) &&
				!(player_x > 366 && player_x < 600 && player_y < 402 && player_y>394) &&
				!(player_x > 70 && player_x < 298 && player_y < 402 && player_y>394) &&
				!(player_x > -2 && player_x < 360 && player_y < 262 && player_y>258))

			{
				player_y -= speed;
			}

			//if the down button is pressed AND we're still above the bottom wall
			//move the box "down" by 4 pixels
			if ((key[1] && player_y <= 478 - 32) &&
				!(player_x > 66 && player_x < 298 && player_y >66 && player_y < 80) &&//ORANGE WALL
				!(player_x > 368 && player_x < 602 && player_y >66 && player_y < 80) &&//GREEN WALL
				!(player_x > 68 && player_x < 302 && player_y >266 && player_y < 270) &&
				!(player_x > -2 && player_x < 360 && player_y >206 && player_y < 212))
			{
				player_y += speed;
			}
			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if ((key[2] && player_x >= 2) &&
				!(player_y > 70 && player_y < 200 && player_x >294 && player_x < 302) &&
				!(player_y > 68 && player_y < 402 && player_x >598 && player_x < 602) &&
				!(player_y > 268 && player_y < 400 && player_x >294 && player_x < 302) &&
				!(player_y > 208 && player_y < 260 && player_x >358 && player_x < 362))
			{
				player_x -= speed;
			}

			//if the right button is pressed AND we're still left of the right wall
			//move the box right by 4 pixels
			if ((key[3] && player_x <= 638 - 32) &&
				!(player_x > 66 && player_x < 78 && player_y >66 && player_y < 198) &&
				!(player_x > 366 && player_x < 378 && player_y >66 && player_y < 402) &&
				!(player_x > 66 && player_x < 72 && player_y >266 && player_y < 402))
			{
				player_x += speed;
			}

			//DEATH WALL
			if (player_x > 302 && player_x < 360 && player_y >212 && player_y < 444) {
				player_x = 50;
				player_y = 50;
				//play devestating sound effect
				//print a nasty message, flip display,pause for a second or two 
				al_draw_text(font, al_map_rgb(255, 0, 0), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "Watch out for the death wall!");
				al_flip_display();
				lives--;


			}

			//put speed bumps here! check for position and
	//		if (player_x > 350 && player_x < 370 && player_y >166 && player_y < 170) {
	//			al_flip_display();
			//play sound
			//and increase speed
	//		speed++;
			//erase speed bumps! (maybe have a boolean to turn it off and on)

			//check for collect here!
			//collect =true;
			//redraw at every tick of the timer
			redraw = true;
	//	}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the algorithm that turns key presses into events
		//a "key down" event is when a key is pushed
		//while a "key up" event is when a key is released

		//has something been pressed on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			//"keycode" holds all the different keys on the keyboard
			switch (ev.keyboard.keycode) {

				//if the up key has been pressed
			case ALLEGRO_KEY_UP:
				key[0] = true;
				break;

				//if the down key has been pressed
			case ALLEGRO_KEY_DOWN:
				key[1] = true;
				break;

				//if the left key has been pressed
			case ALLEGRO_KEY_LEFT:
				key[2] = true;
				break;

				//if the right key has been pressed
			case ALLEGRO_KEY_RIGHT:
				key[3] = true;
				break;
			}
		}
		//has something been released on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[0] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[1] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[2] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[3] = false;
				break;

				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		//RENDER SECTION
		//if the clock ticked but no other events happened, don't bother redrawing
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//paint black over the old screen, so the old player dissapears
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			al_draw_bitmap(player, player_x, player_y, 0);

			//wall 1
			al_draw_filled_rectangle(335, 240, 360, 444, al_map_rgb(20, 245, 227));//death wall!
			al_draw_filled_rectangle(100, 100, 300, 200, al_map_rgb(200, 100, 0));
			al_draw_filled_rectangle(400, 100, 600, 400, al_map_rgb(120, 200, 17));
			al_draw_filled_rectangle(100, 300, 300, 400, al_map_rgb(20, 45, 227));
			al_draw_filled_rectangle(0, 240, 360, 260, al_map_rgb(220, 45, 27));

			//speed bumps!
			al_draw_filled_rectangle(350, 200, 370, 220, al_map_rgb(200, 100, 200));
			al_draw_filled_rectangle(450, 420, 470, 440, al_map_rgb(200, 100, 200));
			//collect!
			al_draw_filled_rectangle(50, 400, 70, 420, al_map_rgb(250, 0, 0));

			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 10, ALLEGRO_ALIGN_CENTRE, "lives = %i", lives);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 10, ALLEGRO_ALIGN_CENTRE, "time = %i", time / 10);


			//kill game if lives is less than zero
			if (lives <= 0 || time<0) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_map_rgb(255, 0, 0), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "YOU SUCK! TRY AGAIN");
			}

			if (collect == true) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_map_rgb(255, 0, 255), 350, 300, 0, "Secret Collect!");

			}

			al_flip_display();
		}
	}

	al_destroy_bitmap(player);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}