#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <curses.h>
#include <sys/un.h>
#include <string.h>


struct data{
		char out[256];
		char sin[256];
		char val[1024];
}

int main()
{
	int fd_socket; char buf[1536]; char word[256]; uint32_t hash;
	struct sockaddr_in s_addr;
	struct data *msg;

	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(5555);
	s_addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	fd_socket=socket(AF_INET, SOCK_DGRAM,0);

	if(connect(fd_socket,(struct sockaddr*)&s_addr,sizeof(s_addr))==-1){
		perror("connect");
		exit(-1);
	}
	while(1){
		hash=0;
		memset(buf,0, 800);
		memset(word,0,256);
		//bzero(&msg,sizeof(msg));

		scanf("%256.d",&word);
		hash=jenkins_hash(word,strlen(word));

		if(send(fd_socket,&hash,sizeof(hash),0)==-1){
			perror("send");
			exit(-1);
		}
		if(recv(fd_socket,buf,1536,0)==-1){
			perror("recv");
			exit(-1);
		}
		msg=(struct data*)buf;
		printf("%s\n", msg->out);
		printf("%s\n",msg->sin);
		printf("%s\n",msg->val);
	}
}
