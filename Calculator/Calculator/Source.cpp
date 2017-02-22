#include <iostream>
using namespace std;
int input;
int input2;
int num;
int num2;
int main(){
	cout << "Add, Subtract, Multiply, or Divide? (1), (2), (3), (4)." << endl;
	cin >> input;
	cout << "Give me two numbers" << endl;
	cin >> num;
	cin >> num2;
	if (input == 1) {
		cout <<"the answer is"<< num + num2 << endl;
	}
	if (input == 2) {
		cout << "the answer is" << num - num2 << endl;
	}
	if (input == 3) {
		cout << "the answer is" << num*num2 << endl;
	}
	if (input == 4) {
		cout << "the answer is" << num / num2 << endl;
	}
}