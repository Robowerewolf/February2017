#include <iostream>
using namespace std;
double height;
double radius;
double rsq;
double volume;
double pi = 3.14;
int main() {
	cout << "Enter Height of Cone." << endl;
	cin >> height;
	cout << "Enter Radius of Cone." << endl;
	cin >> radius;
	rsq = (radius * radius);
	volume = ((pi * rsq * height) / 3);
	cout << "The volume of the cone is" << volume << endl;
}