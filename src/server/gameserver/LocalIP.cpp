/*
 * display info about network interfaces
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>

#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <arpa/inet.h>

#include <string>
#include <list>

#define inaddrr(x) (*(struct in_addr *) &ifr->x[sizeof sa.sin_port])
#define IFRSIZE   ((int)(size * sizeof (struct ifreq)))

#include "LocalIP.h"

list<string> getLocalIP()
{
//	unsigned char      *u;
	int                sockfd, size  = 1;
	struct ifreq       *ifr;
	struct ifconf      ifc;
	struct sockaddr_in sa;
	list<string> ret;

	if (0 > (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP))) {
		fprintf(stderr, "Cannot open socket.\n");
//		exit(EXIT_FAILURE);
		return ret;
	}

	ifc.ifc_len = IFRSIZE;
	ifc.ifc_req = NULL;

	do {
		++size;
		/* realloc buffer size until no overflow occurs  */
		if (NULL == (ifc.ifc_req = static_cast<struct ifreq*>(realloc(ifc.ifc_req, IFRSIZE)))) {
			fprintf(stderr, "Out of memory.\n");
//			exit(EXIT_FAILURE);
			return ret;
		}

		ifc.ifc_len = IFRSIZE;
		if (ioctl(sockfd, SIOCGIFCONF, &ifc)) {
			perror("ioctl SIOCFIFCONF");
//			exit(EXIT_FAILURE);
			return ret;
		}
	} while  (IFRSIZE <= ifc.ifc_len);


	ifr = ifc.ifc_req;
	for (;(char *) ifr < (char *) ifc.ifc_req + ifc.ifc_len; ++ifr) {

		if (ifr->ifr_addr.sa_data == (ifr+1)->ifr_addr.sa_data) {
			continue;  /* duplicate, skip it */
		}

		if (ioctl(sockfd, SIOCGIFFLAGS, ifr)) {
			continue;  /* failed to get flags, skip it */
		}

		//    printf("Interface:  %s\n", ifr->ifr_name);

		if ( strcmp( ifr->ifr_name, "lo" ) )
		{
			printf("IP Address: %s\n", inet_ntoa(inaddrr(ifr_addr.sa_data)));
			ret.push_back( inet_ntoa(inaddrr(ifr_addr.sa_data)) );
		}

	}

	close(sockfd);
	return ret;
}

