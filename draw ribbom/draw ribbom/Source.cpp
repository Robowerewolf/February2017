#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
int main() {
	ALLEGRO_DISPLAY*display = NULL;
	al_init();
	al_init_primitives_addon();
	display = al_create_display(1000, 800);
	float ribbon[5][5] = {{400,200},{800,200},{600,400}, {200,300},{400,200}};
	al_draw_ribbon(*ribbon, sizeof(*ribbon), al_map_rgb(210, 20, 130), 5, 5);

		al_flip_display();
		al_rest(20);
}