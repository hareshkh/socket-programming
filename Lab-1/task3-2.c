#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
	for(int i = 1; i<=5; i++)
		fork();
	printf("here\n");
	sleep(10);
	return 0;
}