#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include "server.h"
#include "client.h"

int main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s;
	int iter = 1;
	if (argc >= 2) {
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		/*for (iter; iter < argc; iter++){ 
			 printf("kk%s\n", argv[iter]); 
			if (argv[iter][0] == '-') {
				if (argv[iter][1] == '4') {
					printf("Option -4\n");
					hints.ai_family = AF_INET;
				}
				else if (argv[iter][1] == '6') {
					printf("Option -6\n");
					hints.ai_family = AF_INET6;
				}
				else if (argv[iter][1] == 'u') {
					printf("UDP\n");
					hints.ai_socktype = SOCK_DGRAM;
				}
				else if (argv[iter][1] == 'l') {
					printf("Server Mode\n");
					int number;
					number = atoi(argv[2]);
					printf("%d", number);
				//	server_tcp(number);
				}
				else {
					printf("Error: Usage nc [-option] [destination] [port]\n");
					exit(1);
				}
			}
			else {*/
				printf("DEBUG\n");
				s = getaddrinfo(argv[iter], argv[iter + 1], &hints, &result);
				if (s != 0) {
					fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
					exit(EXIT_FAILURE);
				}
				int number = atoi(argv[2]);
				client_tcp(result);	
			/*/
		}*/
	}
	else {
		(argc < 2)?printf("Za malo argumentow\n"):printf("Za duzo argumentow\n");
		exit(1);
	}

	return 0;
}
