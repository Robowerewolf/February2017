#include <stdio.h>
int main() {
	char string[64];
	printf("Would you tell me your full name?\n");
	fgets(string, 64, stdin);
	printf("Hello, %s! Nice to meet you!\n", string);
	return 0;

}