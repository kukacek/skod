/* tcp.c - TCP/IP stuff */

#include "tcp.h"

/* Connect to TCP/IP socket */
FILE * tcp_connect(char *server, char *port, char *mode) {
	struct addrinfo ai, *srv = NULL, *p = NULL;

	memset(&ai, 0, sizeof(struct addrinfo));
	if (( getaddrinfo(server, port, &ai, &srv)) != 0 ) {
		die("Cannot resolve %s - (%s)", server,gai_strerror(1));
	}

	ai.ai_family = AF_UNSPEC;
	ai.ai_socktype = SOCK_STREAM;
	ai.ai_protocol = IPPROTO_TCP;

	p = srv;
	if (( getnameinfo((struct sockaddr *)p->ai_addr,
					p->ai_addrlen, 
					ip, sizeof(ip),
					NULL, (socklen_t) 0U, 
					NI_NUMERICHOST)) != 0)
		die("Cannot resolve %s- (%s).", server,gai_strerror(1));

	/* skod.h //int fd */
	if (( fd = socket(p->ai_family, p->ai_socktype, 0)) < 0 )
		die("Failed to create socket.");

	if ( connect(fd, p->ai_addr, p->ai_addrlen) < 0 )
		die("Failed to connect.");
	freeaddrinfo(srv);

	/* call to fdopen to return FILE */
	return (fdopen(fd, mode));
}

