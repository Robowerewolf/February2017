#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
	al_init();
	al_init_font_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	ALLEGRO_DISPLAY*display = al_create_display(640, 480);
	ALLEGRO_BITMAP*picture1 = NULL;
	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("WORDSOFLOVE.ttf", 72, 0);
	if (font == NULL)
		cout << "font didn't load" << endl;
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_text(font, al_map_rgb(255, 20, 147), 640 / 2, (480 / 4), ALLEGRO_ALIGN_CENTRE, "Happy Valentines Day!");
	picture1 = al_load_bitmap("heartpizza.jpg");
	al_convert_mask_to_alpha(picture1, al_map_rgb(255, 255, 255));
	al_draw_bitmap(picture1, 450, 150, 0);
	al_flip_display();
	al_rest(10);
	al_destroy_display(display);
	return 0;
}