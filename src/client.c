#include "../include/header.h"


struct data_c{
		char out[256];
		char sin[256];
		char val[1024];
};

int main()
{
	int fd_socket; char buf[1536]; char word[256]; uint32_t hash;
	struct sockaddr_in s_addr;
	struct data_c *msg;
	setlocale(LC_ALL, "Rus");
	socklen_t len=sizeof(struct sockaddr);
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(3451);
	s_addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	fd_socket=socket(AF_INET, SOCK_DGRAM,0);

	if(connect(fd_socket,(struct sockaddr*)&s_addr,sizeof(s_addr))==-1){
		perror("connect");
		exit(-1);
	}

	while(1){
		hash=0;
		memset(buf,0,1536);
		bzero(&word,256);
		//bzero(&msg,sizeof(msg));
		printf("Enter:");
		scanf("%s",&word);
//		printf("%d \n", strlen(word));
		hash=jenkins_hash(word,strlen(word));
//		printf("HASH: %d\n", hash);
		if(send(fd_socket,&hash,sizeof(uint32_t),0)==-1){
			perror("send");
			exit(-1);
		}
//		printf("Send...\n");
		if(recv(fd_socket,buf,1536,0)==-1){
			perror("recv");
			exit(-1);
		}
		msg=(struct data_c*)buf;
//		printf("BUF: %s\n", buf);
		printf("OUT: %s\n", msg->out);
		printf("SIN: %s\n",msg->sin);
		printf("VAL: %s\n",msg->val);
	}
}
