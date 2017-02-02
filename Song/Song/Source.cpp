#include <iostream>
using namespace std;
int input;
int main() {
	while (input != 'q') {
		cout << "What song would you like to play?" << endl;
		cout << "Takin' Care of Business, By Randy Bachman(1), War pigs, By Black Sabbath(2),    Hotel California, By The Eagles(3), or press q to quit." << endl;
		cin >> input;
		if (input == 1) {
			cout << " And I'll be taking care of business (every day) / Taking care of business      (every way)!" << endl;
		}
		if (input == 2) {
			cout << "Generals gather in their masses! Just like witches at black masses!" << endl;
		}
		if (input == 3) {
			cout << "Were living it up at the hotel california!" << endl;
		}
		}
	}