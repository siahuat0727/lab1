#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(){
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
	portno = 8740;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname("127.0.0.1");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	while(1){
		puts("(a)list all process ids");
		puts("(b)thread's IDs");
		puts("(c)child's PIDs");
		puts("(d)process name");
		puts("(e)state of process(D,R,DS,T,t,W,X,Z)");
		puts("(f)command line of executing process(cmdline)");
		puts("(g)parent's PID");
		puts("(h)all ancients of PIDs");
		puts("(i)virtual memory size(VMSize)");
		puts("(j)physical memory size(VmRSS)");
		puts("(k)exit");
		char func;
		int pid;
		do{
			printf("which? ");
			scanf("%c", &func);
		}while(func > 'k' || func < 'a');
		if(func != 'a'){
			printf("pid? ");
			scanf("%d", &pid);
		}
		bzero(buffer,256);
		buffer[0] = func;
		snprintf(buffer+1, sizeof(buffer), "%d", pid);
		printf("buffer = %s\n", buffer);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0)
			error("ERROR writing to socket");
	}




	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if (n < 0)
		error("ERROR reading from socket");
	printf("%s\n",buffer);
	close(sockfd);
	return 0;
}
