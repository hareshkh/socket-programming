#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <strings.h>
#include <sys/time.h>
#include <errno.h>
using namespace std;

pid_t pid;
int nsent;
int sockfd;
struct sockaddr_in sasend;

int checksum_calc(char *buf, int count) {
	int sum = 0;
	for (int i = 0; i < count - 1; i++) {
		sum += (buf[i] << 8) + buf[i+1];
		sum = ((sum%(1<<16)) + sum/16);
	}
	if(count % 2) {
		sum += buf[count - 1];
		sum = ((sum%(1<<16)) + sum/16);
	}
	return ~sum;
}

void tv_sub(struct timeval *recv, struct timeval *send) {
	recv->tv_sec = recv->tv_sec - send->tv_sec;
	recv->tv_usec = recv->tv_usec - send->tv_usec;
	return;
}

void sendicmp() {
	char sendbuf[32];
	int len = 32;
	struct icmp *icmp_packet = (struct icmp *) sendbuf;
	icmp_packet -> icmp_type = ICMP_ECHO;
	icmp_packet -> icmp_code = 0;
	icmp_packet -> icmp_id = pid;
	icmp_packet -> icmp_seq = ++nsent;
	gettimeofday((struct timeval *) icmp_packet -> icmp_data, NULL);
	icmp_packet -> icmp_cksum = 0;
	icmp_packet -> icmp_cksum  = checksum_calc(sendbuf, len);

	sendto(sockfd, sendbuf, len, 0, (struct sockaddr *) &sasend, sizeof(sasend));
	printf("Sent\n");
}

static void alarm_handler(int signo) {
	sendicmp();
	alarm(1);
	return;
}

void process(char *recvbuf, int size, timeval *trecv, char *host) {
	struct ip *ip_packet = (struct ip *) recvbuf;
	int hlen1 = ip_packet->ip_hl << 2;

	struct icmp *icmp_packet = (struct icmp *) (recvbuf + hlen1);
	int icmplen = size - hlen1;
	if(icmplen < 8) {
		printf("icmplen < 8\n");
		return;
	}

	if(icmp_packet -> icmp_type == ICMP_ECHOREPLY) {
		if(icmp_packet -> icmp_id != pid) {
			printf("pid did not match\n");
			return;
		}

		if(icmplen < 16) {
			printf("icmplen < 16\n");
			return;
		}

		struct timeval *tsend = (struct timeval *) icmp_packet -> icmp_data;
		tv_sub(trecv, tsend);

		float rtt = trecv -> tv_sec * 1000 + trecv -> tv_usec / 1000;
		printf("%d bytes from %s : seq=%u, ttl=%d, rtt=%.3fms\n", icmplen, host, icmp_packet->icmp_seq, ip_packet->ip_ttl, rtt);
	}

}

void readloop(char *host) {
	char recvbuf[512];
	struct sockaddr_in sarecv;
	bzero(&sarecv, sizeof(sarecv));

	alarm_handler(SIGALRM);

	while(1) {
		unsigned int len = sizeof(sarecv);
		int n = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *) &sarecv, &len);
		if(n < 0) {
			if (errno == EINTR) continue; // alarm went off
			else printf("Recvfrom error\n");
		}
		struct timeval tval;
		gettimeofday(&tval, NULL); //timezone parameter is null

		process(recvbuf, n, &tval, host);
	}
}

int main(int argc, char **argv) {
	struct sigaction act;
	bzero(&act, sizeof(act));
	act.sa_handler = alarm_handler;
	if(act.sa_flags & SA_RESTART) {
		act.sa_flags = act.sa_flags ^ SA_RESTART; // Do not restart the stopped syscall
	}

	sigaction(SIGALRM, &act, NULL);

	if (argc < 2) {
		printf("More arguments required\n");
		return -1;
	}
	char *host = argv[1];
	pid = getpid();

	printf("Ping host : %s\n", host);
	bzero(&sasend, sizeof(sasend));
	sasend.sin_family = AF_INET;
	inet_aton(host, &sasend.sin_addr);

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	setuid(getuid());

	readloop(argv[1]);
	return 0;
}