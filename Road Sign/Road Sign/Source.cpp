#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "allegro5/allegro_primitives.h"
int main(int argc, char **argv) {
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	ALLEGRO_DISPLAY*display = NULL;
	ALLEGRO_FONT*font = al_create_builtin_font();
	display = al_create_display(1300, 1100);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(200, 350, 900, 500, al_map_rgb(0, 100, 0));
	al_draw_text(font, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "Milwaukee St." );
	al_flip_display(); 
	al_rest(20);
	return 0;
}