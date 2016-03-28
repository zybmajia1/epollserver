#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define MAXLINE 5
#define OPEN_MAX 5000
#define LISTENQ 20
#define SERVER_PORT 5000
#define INFTIM 1000

//set O_NONBLOCK
void setnonblocking(int sockfd)
{
	int opts;
	int iret=0;
	opts = fcntl(sockfd, F_GETFL);
	if(opts<0)
	{
		perror("GETFL ERROR");
		exit(0);
	}

	iret = fcntl(sockfd, F_SETFL, opts);
	if(iret<0)
	{
		perror("SETFL ERROR");
		exit(0);
	}
}

//close fd
void closeAndDisable(int sockfd, epoll_event ee)
{
	close(sockfd);
	ee.data.fd = -1;
}

int main()
{
	int iret=0;
	//create socket
	struct sockaddr_in clientaddr, serveraddr;
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//bind soketfd
	memset(&clientaddr, 0x00, sizeof(clientaddr));
	memset(&serveraddr, 0x00, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(5000);
	iret = bind(listenfd, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if(iret<0)
	{
		perror("bind server error");
		exit(0);
	}
	listen(listenfd, 20);
	
	//create epollfd
	int epfd = epoll_create(5000);	
	
	//epollctl register event
	epoll_event ev;
	ev.data.fd = listenfd;
	ev.events = EPOLLIN|EPOLLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, &ev);
	
	int maxi = 0;
	int sumfds = 0;
	epoll_event events[20] = {0}
	for(;;)
	{
		sumfds = epoll_wait(epfd, &events, 20, -1);
		
	}
	
	return 0;
}





















