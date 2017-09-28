#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAC_STRING_LENGTH 13

char *getmac(char *iface) {
	char *ret = malloc(MAC_STRING_LENGTH);
	struct ifreq s;
	int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

	strcpy(s.ifr_name, iface);
	if (fd >= 0 && ret && 0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
		int i;
		for (i = 0; i < 6; ++i)
			snprintf(ret+i*2,MAC_STRING_LENGTH-i*2,"%02x",(unsigned char) s.ifr_addr.sa_data[i]);
	}
	else {
		perror("malloc/socket/ioctl failed");
		exit(1);
	}
	return(ret);
}

int main(int argc, char ** argv) {
	char *usage = "Pass arguments for device names seperated by space. Eg : eth0 or enp2s0 or wlp3s0 as per your system.";
	if (argc < 2) printf("%s\n", usage);
	for (int i = 1; i < argc; i++) {
		char *mac = getmac(argv[i]);
		printf("Mac address for %s : %s\n",argv[i], mac);
		free(mac);
	}
	return 0;
}