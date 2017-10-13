#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getmac(char *iface) {
	#define MAC_STRING_LENGTH 13
	char *ret = (char *)malloc(MAC_STRING_LENGTH);
	struct ifreq s;
	int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

	strcpy(s.ifr_name, iface);
	if (fd >= 0 && ret && 0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
		int i;
		for (i = 0; i < 6; ++i)
			printf("%02x",(unsigned char) s.ifr_addr.sa_data[i]);
	}
	else {
		perror("malloc/socket/ioctl failed");
		exit(1);
	}
}

int main() {
	getmac("enp2s0");
	return 0;
}