#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define N_BUFFER 256 // TO CHECK

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void *func_for_client(void * dest_client){
	char buffer[N_BUFFER];
	bzero(buffer, N_BUFFER);
	int sock_client = *(int *)dest_client;
	int n = read(sock_client, buffer, N_BUFFER-1);
	if (n < 0) error("ERROR reading from socket");
	printf("receive: %s\n", buffer);
	char oprt = buffer[0];
	int pid;
	sscanf(buffer+1, "%d", &pid);
	printf("oprt = %c\n", oprt);
	printf("pid = %d\n", pid);
}

int main(){
	pthread_t thread1, thread2;
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = 8740;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	int num_ac = 5;
	while(num_ac--){
		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
		if (newsockfd < 0)
			error("ERROR on accept");
		int* new_sock = (int*)malloc(1);
		*new_sock = newsockfd;
		pthread_create(&thread1, NULL, func_for_client, (void*)new_sock);
	}
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	printf("after read\n");
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);
	n = write(newsockfd,"I got your message",18);
	if (n < 0) error("ERROR writing to socket");
	close(newsockfd);
	close(sockfd);

	// rmb to pthread_join
	return 0;
}
