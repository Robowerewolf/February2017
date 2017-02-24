#include <iostream>
using namespace std;
int main(void) {
	int num; 

	for (num = 1; num <= 100000000; num = num * 10)
		cout << num * 10 << endl;
	return 0;
}