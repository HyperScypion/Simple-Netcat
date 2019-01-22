#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "server.h"
#include "client.h"

int main(int argc, char *argv[])
{
	int iter = 0;
	if (argc >= 2 && argc <= 3) {
		for (iter; iter < argc; iter++) {
			/* printf("%s\n", argv[iter]); */
			if (*argv[iter] == '-') {
				if (argv[iter][1] == '4') {
					printf("Option -4\n");
				}
				else if (argv[iter][1] == '6') {
					printf("Option -6\n");
				}
				else if (argv[iter][1] == 'u') {
					printf("UDP\n");
				}
				else if (argv[iter][1] == 'l') {
					printf("Server Mode\n");
				}
				else {
					printf("Error: Usage nc [-option] [destination] [port]\n");
					exit(1);
				}
			}
			else {
				
			}
		}
	}
	else {
		(argc < 2)?printf("Za malo argumentow\n"):printf("Za duzo argumentow\n");
		exit(1);
	}

	return 0;
}
