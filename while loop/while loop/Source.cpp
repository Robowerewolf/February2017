#include <iostream>
using namespace std;
char input;
int main() {
	while (input != 'n') {
	cout << "Would you like a cookie? y or n" << endl;
	cin >> input;
	if (input == 'y'); {
		cout << "Here's a cookie" << endl;
	}
	if (input == 'n')
		cout << "Go away, then!" << endl;
	}
}