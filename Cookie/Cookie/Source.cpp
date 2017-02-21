#include <iostream>
using namespace std;
char input;
int main() {
	cout << "What kind of cookie would you like?" << endl;
	cin >> input;
	switch (input) {
	case 'c': cout << "Chocolate chip" << endl;
		break;
	case 'o': cout << "Oatmeal" << endl;
		break;
	case 'm': cout << "Macadamia white chip" << endl;
		break;
	}
}