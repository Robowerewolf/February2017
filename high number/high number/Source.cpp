#include <iostream>
using namespace std;
int main(void) {
	double num; 

	for (num = 1; num <= 1000000000; num = num * 10)
		cout << num * 10 << endl;
	return 0;
}