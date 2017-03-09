#include "allegro5/allegro_image.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include <iostream>
using namespace std;
int collision(int b1x, int b1y, int b1w, int b1h, int b2x, int b2y, int b2w, int b2h);
int main()
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *paddle = NULL;
	ALLEGRO_BITMAP *paddle2 = NULL;
	ALLEGRO_BITMAP *ball = NULL;
	ALLEGRO_FONT * font = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance3 = NULL;
	//these two variables hold the x and y positions of the square
	//initalize these variables to where you want your square to start
	float paddle_x = 30;
	float paddle_y = 160;
	float paddle_w = 32;
	float paddle_h = 75;

	float paddle2_x = 585;
	float paddle2_y = 160;
	float paddle2_w = 32;
	float paddle2_h = 75;

	float ball_x = 100;
	float ball_y = 100;
	float ball_w = 32;
	float ball_h = 32;

	int score = 0;
	int score2 = 0;

	int time = 1000;
	//here's our key states. they're all starting as "false" because nothing has been pressed yet.
	//the first slot represents "up", then "down", "left" and "right"
	float ball_dx = 4.0, ball_dy = -4.0;
	bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	//don't redraw until an event happens

	bool redraw = true;

	//this controls our game loop
	bool doexit = false;

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);
	al_init_image_addon();//added by mo

	//get the keyboard ready to use
	al_install_keyboard();

	sample2 = al_load_sample("ChillingMusic.wav");

	instance3 = al_create_sample_instance(sample2);

	al_set_sample_instance_playmode(instance3, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instance3, al_get_default_mixer());

	al_play_sample_instance(instance3);

	font = al_load_ttf_font("INVASION2000.ttf", 50, NULL);
	if (font == NULL)
		cout << "ooops" << endl;

	timer = al_create_timer(.02);

	display = al_create_display(640, 480);

	//ball = al_create_bitmap(32, 32);
	//al_set_target_bitmap(ball);
	//al_clear_to_color(al_map_rgb(137, 200, 5));
	ball = al_load_bitmap("Tennis_Ball_32x32.png");

	paddle = al_create_bitmap(32, 75);

	al_set_target_bitmap(paddle);

	al_clear_to_color(al_map_rgb(255, 255, 255));

	paddle2 = al_create_bitmap(32, 75);

	al_set_target_bitmap(paddle2);

	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}

	if (!al_reserve_samples(1)) {
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

	sample = al_load_sample("tennisserve.wav");

	if (!sample) {
		printf("Audio clip sample not loaded!\n");
		return -1;
	}

	//these lines tell teh event source what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//new! tell the event queue that it should take keyboard events, too 
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);


	al_draw_text(font, al_map_rgb(255, 0, 0), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "PONG!");
	

	al_flip_display();
	al_rest(1);

	//so the game loop is set to act on "ticks" of the timer OR keyboard presses 
	//OR the mouse closing the display
	while (!doexit)
	{
		time--;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the movement algorithm

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//if the up button is pressed AND we're still below the top wall,
			//move the box "up" by 4 pixels
			if (key[0] && paddle_y >= 0) {
				paddle_y -= 4.0;
			}

			if (key2[0] && paddle2_y >= 0) {
				paddle2_y -= 4.0;
			}
			//if the down button is pressed AND we're still above the bottom wall
			//move the box "down" by 4 pixels
			if (key[1] && paddle_y <= 480 - 75) {
				paddle_y += 4.0;
			}

			if (key2[1] && paddle2_y <= 480 - 75) {
				paddle2_y += 4.0;
			}
			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if (key[2] && paddle_x >= 0) {
				paddle_x -= 4.0;
			}

			if (key2[2] && paddle2_x >= 0) {
				paddle2_x -= 4.0;
			}
			//if the right button is pressed AND we're still left of the right wall
			//move the box right by 4 pixels
			if (key[3] && paddle_x <= 640 - 32) {
				paddle_x += 4.0;
			}

			if (key2[3] && paddle2_x <= 640 - 32) {
				paddle2_x += 4.0;
			}
			if (ball_x < 0 || ball_x > 640 - 32) {
				//flip the x direction
				ball_dx = -ball_dx;
			}
			//if the box hits the top wall OR the bottom wall
			if (ball_y < 0) {
				ball_dy = -ball_dy;
			}
				//redraw at every tick of the timer
			if (ball_y > 480 - 32) {
				ball_dy = -ball_dy;
			}

			if (ball_x == 0) {
				ball_dx = -ball_dx;
				score++;
			}
			if (ball_x == 640 - 32) {
				ball_dx = -ball_dx;
				score2++;
			}

			ball_x += ball_dx;
			ball_y -= ball_dy;


			if ((collision(paddle_x, paddle_y, paddle_w, paddle_h, ball_x, ball_y, ball_w, ball_h) == 1) ||
				(collision(paddle2_x, paddle2_y, paddle2_w, paddle2_h, ball_x, ball_y, ball_w, ball_h) == 1)) {
				ball_dx = -ball_dx;
				al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}

			redraw = true;
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
				key2[0] = true;
				break;

				//if the down key has been pressed
			case ALLEGRO_KEY_DOWN:
				key2[1] = true;
				break;

				//if the left key has been pressed

			case ALLEGRO_KEY_W:
				key[0] = true;
				break;

				//if the down key has been pressed
			case ALLEGRO_KEY_S:
				key[1] = true;
				break;

				//if the left key has been pressed
			}
		}
		//has something been released on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key2[0] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key2[1] = false;
				break;

				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			case ALLEGRO_KEY_W:
				key[0] = false;
				break;

			case ALLEGRO_KEY_S:
				key[1] = false;
				break;
			}
		}


		//RENDER SECTION
		//if the clock ticked but no other events happened, don't bother redrawing
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//paint black over the old screen, so the old square dissapears
			//al_clear_to_color(al_map_rgb(0, 0, 0));
			al_clear_to_color(al_map_rgb(0, 0, 0));


			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 10, ALLEGRO_ALIGN_CENTRE, "score = %i", score2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 10, ALLEGRO_ALIGN_CENTRE, "score = %i", score);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 400, ALLEGRO_ALIGN_CENTRE, "time = %i", time / 10);

			
			if (ball_y > paddle_y)
				paddle_y = paddle_y + 2;
			if (ball_y < paddle_y)
				paddle_y = paddle_y - 2;


			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			al_draw_bitmap(ball, ball_x, ball_y, 0);
			al_draw_bitmap(paddle, paddle_x, paddle_y, 0);
			al_draw_bitmap(paddle2, paddle2_x, paddle2_y, 0);
			if (time < 0 && score > score2) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_map_rgb(255, 0, 0), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "Player Wins!");
			}

			if (time < 0)
				break;
			
			al_convert_mask_to_alpha(ball, al_map_rgb(0, 0, 0));
			al_flip_display();
		}
	}//end game loop
	if (score > score2) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(font, al_map_rgb(255, 0, 0), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "Player Wins!");
	}

	if (score2 > score) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(font, al_map_rgb(255, 0, 0), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "CPU Wins!");

	}

	if (score2 == score) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(font, al_map_rgb(255, 0, 0), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "Tie!");
	}
	
	al_flip_display();
	al_rest(5);

	al_destroy_bitmap(ball);
	al_destroy_bitmap(paddle);
	al_destroy_bitmap(paddle2);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_sample(sample);

	return 0;
}

int collision(int b1x, int b1y, int b1w, int b1h, int b2x, int b2y, int b2w, int b2h) {
	if ((b2x > b1x + b1w) || //box2 is to the right of box1
		(b2x + b2w< b1x) ||//box2 is to the left of box1
		(b2y > b1y + b1h) || 
		(b2y + b2h< b1y) ||
		(b1y + b1h< b2y) ||
		(b1y > b2y + b2h))
		return 0;
	else
		return 1;
}