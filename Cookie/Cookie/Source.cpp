#include <iostream>
using namespace std;
int input;
int main() {
	cout << "What kind of cookie would you like? 1,2, or 3" << endl;
	cin >> input;
	switch (input) {
	case 1: cout << "Chocolate chip" << endl;
		break;
	case 2: cout << "Oatmeal" << endl;
		break;
	case 3: cout << "Macadamia white chip" << endl;
		break;
	}
}