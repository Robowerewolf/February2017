#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <fstream>
#include <iostream>
using namespace std;

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
const int BOUNCER2_SIZE = 32;
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYKEYS2 {
	KEY_W, KEY_S, KEY_A, KEY_D
};
bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int main()
//matt wuz here
{
	int player1 = 0;
	int player2 = 0;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *bouncer2 = NULL;
	ALLEGRO_BITMAP *bouncer3 = NULL;
	ALLEGRO_BITMAP *bouncer4 = NULL;
	ALLEGRO_BITMAP *bouncer5 = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_FONT *font = NULL;

	float bouncer_x = 550;
	float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer2_x = 50;
	float bouncer2_y = SCREEN_H / 2.0 - BOUNCER2_SIZE / 2.0;
	float bouncer3_x = 200;
	float bouncer3_y = 200;
	float bouncer3_dx = -4.0, bouncer3_dy = 4.0;
	float bouncer4_x = 320;
	float bouncer4_y = 50;
	float bouncer5_x = 320;
	float bouncer5_y = 440;
	bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_ttf_addon();
	al_init_font_addon();
	al_install_keyboard();
	timer = al_create_timer(1.0 / FPS);

	font = al_load_ttf_font("font.ttf", 50, 0);

	display = al_create_display(SCREEN_W, SCREEN_H);

	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE + 100);

	bouncer2 = al_create_bitmap(BOUNCER2_SIZE, BOUNCER2_SIZE + 100);

	bouncer4 = al_create_bitmap(BOUNCER_SIZE + 100, BOUNCER_SIZE);

	bouncer5 = al_create_bitmap(BOUNCER2_SIZE + 100, BOUNCER2_SIZE );

	bouncer3 = al_create_bitmap(32, 32);

	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(bouncer2);

	al_clear_to_color(al_map_rgb(100, 0, 35));
	al_set_target_bitmap(bouncer3);

	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(bouncer4);
	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(bouncer5);
	al_clear_to_color(al_map_rgb(255, 0, 255));//this sets the BOUNCER's color!
	al_set_target_bitmap(al_get_backbuffer(display));

	

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);
	al_reserve_samples(2);

	sample = al_load_sample("ness.wav");

	sample2 = al_load_sample("cloud.wav");

	int topscores[5];
	int temp;
	ifstream inFILE;
	inFILE.open("save.txt");

	for (int i = 0; i<5; i++)
		inFILE >> topscores[i];

	for (int i = 0; i < 5; i++)
		inFILE >> topscores[i];

	al_draw_text(font,al_map_rgb(250, 250, 250), 450, 10, ALLEGRO_ALIGN_CENTER, "TOP SCORES");
	for (int i = 0; i < 5; i++)
		al_draw_textf(font, al_map_rgb(250, 250, 250), 450, 60 + i * 50, ALLEGRO_ALIGN_CENTER, "%d", topscores[i]);
	al_flip_display();
	al_rest(5);

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && bouncer_y >= 4.0) {
				bouncer_y -= 5.0;
			}

			if (key[KEY_DOWN] && bouncer_y <= SCREEN_H - 132 - 4.0) {
				bouncer_y += 5.0;
			}

			if (key[KEY_LEFT] && bouncer4_x >= 4.0) {
				bouncer4_x -= 4.0;
			}

			if (key[KEY_RIGHT] && bouncer4_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
				bouncer4_x += 4.0;
			}
			 if(key2[KEY_W] && bouncer2_y >= 4.0) {
				bouncer2_y -= 5.0;
			}

			if (key2[KEY_S] && bouncer2_y <= SCREEN_H - 132 - 4.0) {
				bouncer2_y += 5.0;
			}

			if (key2[KEY_A] && bouncer5_x >= 4.0) {
				bouncer5_x -= 4.0;
			}

			if (key2[KEY_D] && bouncer5_x <= SCREEN_W - BOUNCER2_SIZE - 4.0) {
				bouncer5_x += 4.0;
			}
			if (bouncer3_x < 0 || bouncer3_x > 640 - 32) {
				bouncer3_dx = -bouncer3_dx;
			}
			if (bouncer3_x <= 0) {
				player2++;
			}
			if(bouncer3_x >= 640 - 32){
				player1++;
			}
				if (bouncer3_y < 0 || bouncer3_y > 480 - 32) {
					bouncer3_dy = -bouncer3_dy;
				}

			
				bouncer3_x += bouncer3_dx;
				bouncer3_y += bouncer3_dy;

				if (collision(bouncer3_x, bouncer3_y, 32, 32, bouncer_x, bouncer_y, 32, 132) == true) {
					bouncer3_dx = -bouncer3_dx;
					bouncer3_dy = -bouncer3_dy;
					al_play_sample(sample, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				if (collision(bouncer3_x, bouncer3_y, 32, 32, bouncer2_x, bouncer2_y, 32, 132) == true) {
					bouncer3_dx = -bouncer3_dx;
					bouncer3_dy = -bouncer3_dy;
					al_play_sample(sample2, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				if (collision(bouncer3_x, bouncer3_y, 32, 32, bouncer4_x, bouncer4_y, 132, 32) == true) {
					bouncer3_dx = -bouncer3_dx;
					bouncer3_dy = -bouncer3_dy;
					al_play_sample(sample, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				if (collision(bouncer3_x, bouncer3_y, 32, 32, bouncer5_x, bouncer5_y, 132, 32) == true) {
					bouncer3_dx = -bouncer3_dx;
					bouncer3_dy = -bouncer3_dy;
					al_play_sample(sample2, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				redraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode) { //controls
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;
				case ALLEGRO_KEY_W:
					key2[KEY_W] = true;
					break;

				case ALLEGRO_KEY_S:
					key2[KEY_S] = true;
					break;

				case ALLEGRO_KEY_A:
					key2[KEY_A] = true;
					break;

				case ALLEGRO_KEY_D:
					key2[KEY_D] = true;
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_W:
				key2[KEY_W] = false;
				break;

				case ALLEGRO_KEY_S:
					key2[KEY_S] = false;
					break;

				case ALLEGRO_KEY_A:
				key2[KEY_A] = false;
				break;

				case ALLEGRO_KEY_D:
					key2[KEY_D] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
				}
			}

			if (redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;

				al_clear_to_color(al_map_rgb(0, 0, 0));

				al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);


				al_draw_bitmap(bouncer2, bouncer2_x, bouncer2_y, 0);

				al_draw_bitmap(bouncer4, bouncer4_x, bouncer4_y, 0);


				al_draw_bitmap(bouncer5, bouncer5_x, bouncer5_y, 0);

				al_draw_bitmap(bouncer3, bouncer3_x, bouncer3_y, 0);
				al_draw_textf(font, al_map_rgb(250, 250, 250), 160, 10, ALLEGRO_ALIGN_CENTRE, "%d", player1);
				al_draw_textf(font, al_map_rgb(250, 250, 250), 560, 10, ALLEGRO_ALIGN_CENTRE, "%d", player2);
				al_flip_display();
			
		}
	}

	ofstream myfile;
	myfile.open("save.txt");

	//this part walks through the array holding scores
	//and puts the current highest score into the array
	//and moves everything else down
	for (int i = 0; i < 5; i++) {
		cout << "highscore is " << topscores[i];
		if (player1 > topscores[i]) {
			temp = topscores[i];
			topscores[i] = player1;
			player1 = temp;
			cout << "replacing score" << endl;
		}
	}
	//this part actually writes to the file
	for (int i = 0; i < 5; i++) {
		myfile << topscores[i] << endl;
	}
	al_rest(2);
	myfile.close();


	al_destroy_bitmap(bouncer);
	al_destroy_bitmap(bouncer2);
	al_destroy_bitmap(bouncer3);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}


bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	if ((x1 + w1 > x2) && (x1 < x2 + w2) && (y1 + h1 > y2) && (y1 < h2 + y2))
		return true;
	else
		return false;
}
