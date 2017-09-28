#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getmac(char *iface)
{
#define MAC_STRING_LENGTH 13
  char *ret = malloc(MAC_STRING_LENGTH);
  struct ifreq s;
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

  strcpy(s.ifr_name, iface);
  if (fd >= 0 && ret && 0 == ioctl(fd, SIOCGIFHWADDR, &s))
  {
    int i;
    for (i = 0; i < 6; ++i)
      snprintf(ret+i*2,MAC_STRING_LENGTH-i*2,"%02x",(unsigned char) s.ifr_addr.sa_data[i]);
  }
  else
  {
    perror("malloc/socket/ioctl failed");
    exit(1);
  }
  return(ret);
}

int main()
{
  char *mac = getmac("eth0");
  printf("%s\n",mac);
  free(mac);
}