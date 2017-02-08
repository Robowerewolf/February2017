#include <Windows.h>
#include <string>
#include <ctime>
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
using namespace std;
void Monster();//Declaring function called monster
int main(int argc, char **argv) {
	al_init();
	al_init_image_addon();
	ALLEGRO_DISPLAY*screen = NULL;
	ALLEGRO_BITMAP*picture1 = NULL;
	ALLEGRO_BITMAP*picture2 = NULL;
	ALLEGRO_BITMAP*picture3 = NULL;
	ALLEGRO_BITMAP*picture4 = NULL;
	ALLEGRO_BITMAP*picture5 = NULL;
	ALLEGRO_BITMAP*picture6 = NULL;
	ALLEGRO_BITMAP*picture7 = NULL;
	ALLEGRO_BITMAP*picture8 = NULL;
	ALLEGRO_BITMAP*picture9 = NULL;
	screen = al_create_display(1200, 1050);
	srand(static_cast<unsigned int>(time(0)));//uses the time on the computer to generate a random number
	string inv[10];//declares array of strings called inv
	int room = 1;
	string input;
	string input2;
	int health = 100;
	int health2 = 100;
	int damage = health;
	int damage2 = health2;
	cout << "You have been abducted by mostly peaceful aliens. They are having trouble with a corrupt president named Boogie Barker. Their economy is one that trades instead of using currency. You must stop Barker, and save this strange planet to avoid them destorying yours." << endl;//intro
	while (1 && health>0) {//while loop that keeps the game open as long as user's health is above 0
		cout << "Your health is " << ": " << health << endl;
		switch (room) {//switches rooms
		case 1: system("Color 8A");
			picture1 = al_load_bitmap("bedroom.jpg");
			al_draw_bitmap(picture1, 500, 200, 0);
			al_flip_display();
			cout << "You are in a bedroom on the spaceship. There is just a bed and a futuristic looking tv here." << endl;
			if (inv[0].compare("hat") != 0)
				cout << "There is a hat hanging from the door" << endl;
			cout << "You can go East" << endl;
			getline(cin, input);
			if (input.compare("east") == 0)
				room = 2;
			else if (input.compare("get hat") == 0) {
				inv[0] = "hat";
				cout << "You got the hat" << endl;
			}
			break;
			al_destroy_bitmap(picture1);
		case 2:system("Color E0");
			picture2 = al_load_bitmap("Hall.jpg");
			al_draw_bitmap(picture2, 50, 200, 0);
			al_flip_display();
			cout << "You are in a hallway." << endl;
			if (inv[1].compare("hoodie") != 0)
				cout << "There is a hoodie on the floor" << endl;
			cout << "You can go West, or East" << endl;
			getline(cin, input);
			if (input.compare("west") == 0)
				room = 1;
			else if (input.compare("east") == 0)
				room = 3;
			else if (input.compare("get hoodie") == 0) {
				inv[1] = "hoodie";
				cout << "You got the hoodie" << endl;
			}
			break;
		case 3:system("Color FB");
			picture3 = al_load_bitmap("Bathroom.jpg");
			al_draw_bitmap(picture3, 25, 50, 0);
			al_flip_display();
			al_destroy_bitmap(picture3);
			cout << "You are in a bathroom. It is a white porcelain room with a normal looking toilet and sink." << endl;
			if (inv[2].compare("hairbrush") != 0)
				cout << "There is a hairbrush on the toilet" << endl;
			cout << "You can go North, or West" << endl;
			getline(cin, input);
			if (input.compare("west") == 0)
				room = 2;
			else if (input.compare("north") == 0)
				room = 4;
			else if (input.compare("get hairbrush") == 0) {
				inv[2] = "hairbrush";
				cout << "You got the hairbrush" << endl;
			}
			break;
		case 4:system("Color 4F");
			picture4 = al_load_bitmap("bar.jpg");
			al_draw_bitmap(picture4, 500, 200, 0);
			al_flip_display();
			al_destroy_bitmap(picture4);
			cout << "You are in a cantina. It is a big room with aliens all over and a band playing a song on repeat.(Haven't you seen Star Wars?) There is a bartender behind the counter." << endl;
			if (inv[3].compare("bottle") != 0)
				cout << "There is a bottle of alcohol on the table." << endl;
			cout << "You can go West, North, or South" << endl;
			getline(cin, input);
			if (input.compare("west") == 0)
				room = 5;
			else if (input.compare("north") == 0)
				room = 8;
			else if (input.compare("south") == 0)
				room = 3;
			else if (input.compare("get bottle") == 0) {
				inv[3] = "bottle";
				cout << "You got the bottle" << endl;
			}
			break;
		case 5: system("Color 20");
			picture5 = al_load_bitmap("game room.jpg");
			al_draw_bitmap(picture5, 500, 200, 0);
			al_flip_display();
			Monster();
			al_destroy_bitmap(picture5);
			cout << "You are in a game room. There are scattered arcade games, old and new. There is a large pool table in the center of the room." << endl;
			if (inv[4].compare("sword") != 0)
				cout << "There is a sword underneath the pool table" << endl;
			cout << "You can go North(n), or East(e)" << endl;
			getline(cin, input);
			if (input.compare("north") == 0)
				room = 7;
			else if (input.compare("east") == 0)
				room = 4;
			else if (input.compare("get sword") == 0) {
				inv[4] = "sword";
				cout << "You got the sword" << endl;
			}
			break;
		case 6:system("Color 5F");
			picture6 = al_load_bitmap("turret.jpg");
			al_draw_bitmap(picture6, 500, 200, 0);
			al_flip_display();
			al_destroy_bitmap(picture6);
			Monster();
			cout << "You are in the gun room. There is a huge gun with the barrel pointed toward the window with the barrel of the gun outside of the ship." << endl;
			cout << "You can go South(s), or East(e)." << endl;
			getline(cin, input);
			if (input.compare("north") == 0 && inv[4].compare("sword") == 0)
				room = 10;
			else if (input.compare("east") == 0)
				room = 7;
			break;
		case 7: system("Color 0F");
			picture7 = al_load_bitmap("control room.jpg");
			al_draw_bitmap(picture7, 500, 200, 0);
			al_flip_display();
			al_destroy_bitmap(picture7);
			Monster();
			cout << "You are in the flight deck of the ship. It is a fairly big room with nothing but an empty chair and a huge panel of controls in front of it. Outside of the window, you see a distant, alien looking planet, and nothing else but stars." << endl;
			cout << "You can go South(s), East(e), or West(w)." << endl;
			getline(cin, input);
			if (input.compare("west") == 0)
				room = 6;
			else if (input.compare("south") == 0)
				room = 5;
			else if (input.compare("east") == 0)
				room = 8;
			break;
		case 8:system("Color 1A");
			picture8 = al_load_bitmap("Armory.jpg");
			al_draw_bitmap(picture8, 500, 200, 0);
			al_flip_display();
			al_destroy_bitmap(picture8);
			Monster();
			cout << "You are in an armory. There is nothing here but big black crates." << endl;
			if (inv[5].compare("gun") != 0)
				cout << "The crates are filled with alien guns." << endl;
			cout << "You can go North(n),West(w), or South(s)." << endl;
			getline(cin, input);
			if (input.compare("west") == 0)
				room = 7;
			else if (input.compare("north") == 0)
				room = 9;
			else if (input.compare("south") == 0)
				room = 4;
			else if (input.compare("get gun") == 0 && inv[3].compare("bottle") == 0) {
				inv[5] = "gun";
				cout << "You got a gun" << endl;
			}
			break;
		case 9:system("Color FC");
			picture9 = al_load_bitmap("Alucard.jpg");
			al_draw_bitmap(picture9, 500, 200, 0);
			al_flip_display();
			al_destroy_bitmap(picture9);
			cout << "You walk into a huge room. At the other end of it, you see a huge throne facing away from you, out a window. When the person in the throne gets out of the chair, you see that it is Boogie Barker. Before your eyes, he changes into a demon-like montser with a horn broken off. He calls himself Alucard." << endl;
			if (health2 <= 0)
				cout << "You kill alucard in his steps, and Corcraan is saved!" << endl;
			break;
		case 10:system("Color 2");
			Monster();
			cout << "You are in a room that is empty except for something hanging on the wall." << endl;
			if (inv[6].compare("rocket launcher") != 0)
				cout << "It's a rocket launcher" << endl;
			else if (inv[6].compare("rocket launcher") == 0)
				cout << "Nevermind, the room's empty!" << endl;
			cout << "You can go South" << endl;
			getline(cin, input);
			if (input.compare("south") == 0)
				room = 6;
			else if (input.compare("rocket launcher") == 0 && inv[1].compare("hoodie") == 0) {
				inv[6] = "rocket launcher";
				cout << "You got the rocket launcher" << endl;
			}
			break;
		}
	}
}
void Monster() {
	int num = rand() % 100 + 1;
	if (num >= 50) {
		cout << "It's one of Boogie's goons!" << endl;
	}
	else {
		cout << "You have escaped this room without being atacked" << endl;
	}
}