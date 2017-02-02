#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
int main(int argc, char **argv) {
	ALLEGRO_DISPLAY*display = NULL;
	al_init();
	al_init_primitives_addon();
	display = al_create_display(1200, 1050);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_triangle(600, 500, 425, 475, 200, 75, al_map_rgb(255, 0, 255), 3);
	al_draw_filled_triangle(450, 250, 550, 250, 200, 350, al_map_rgb(0, 0, 0));
	al_draw_triangle(300, 200, 400, 700, 800, 0, al_map_rgb(0, 200, 0), 6);
	al_flip_display();
	al_rest(20);
	al_destroy_display(display);
}