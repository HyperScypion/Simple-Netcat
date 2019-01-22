#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int client(int port, char *addr)
{
	struct sockaddr_in server_info;
	struct hostent *host;
	char send_data[1024], recv_data[1024];
	
	if (host = gethostbyname(add) == NULL) {
		fprintf(stderr, "Cannot get host name\n");
		exit(1);
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(port);
	server_info.sin_addr = *((struct in_addr *)host->h_addr);
	if (connect(sock, (struct sockaddr *)&server_info,
				sizeof(struct sockaddr)) = 1) {
		perror("Connect");
		exit(1);
	}
	/*	while (1) {
		
	}
	*/
}
