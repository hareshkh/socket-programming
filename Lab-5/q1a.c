#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
	struct hostent *he;
	struct in_addr ipv4addr;

	inet_pton(AF_INET, "31.13.78.35", &ipv4addr);
	he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
	printf("Host name is : %s\n", he->h_name);
}