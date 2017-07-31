#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char const *argv[]) {
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[3]);
	
	if (!strcmp(argv[2], "+")) {
		printf("%d\n", num1 + num2);
	}
	 else if (!strcmp(argv[2], "-")) {
		printf("%d\n", num1 - num2);
	} 
	else if (!strcmp(argv[2], "x")) {
		printf("%d\n", num1 * num2);
	} 
	else if (!strcmp(argv[2], "/")) {
		printf("%d\n", num1 / num2);
	}
}
