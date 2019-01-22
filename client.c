#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "client.h"

int client_tcp(int port, char *addr)
{
	int pid, bytes_recieved, sock;
	struct sockaddr_in server_info;
	struct hostent *host;
	char send_data[1024], recv_data[1024];
	
	if (host = gethostbyname(addr) == NULL) {
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
	bzero(&(server_info.sin_zero), 8);

	if (connect(sock, (struct sockaddr *)&server_info,
				sizeof(struct sockaddr)) == -1) {
		
		perror("Connect");
		exit(1);
	}
	if ((pid = fork()) == 0) {
		while(1) {
			fgets(send_data, 1024, stdin);
			if (send(sock, send_data, sizeof(send_data) - 1, 0) == -1) {
				perror("Send");
			}	
			exit(0);
		}
	}
	else {
		while(1) {
			if ((bytes_recieved = recv(sock, recv_data, 1024, 0) == -1)) {
				perror("Recv");
				exit(1);	
			}
			recv_data[bytes_recieved] = '\0';
			printf("%s", recv_data);
		}
		close(sock);
	}
		while(1) {
			if ((bytes_recieved = recv(sock, recv_data, 1024 - 1, 0)) == -1) {
				perror("Recv");
				exit(1);
			}
			recv_data[bytes_recieved] = '\0';
			printf("%s", recv_data);
		}
		close(sock);
}	

