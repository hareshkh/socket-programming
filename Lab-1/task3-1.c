#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int pid_t;
	pid_t = fork();
	if (pid_t == 0) printf("Child PID %d\n", getpid());
	else printf("Parent PID %d\n", getpid());
}