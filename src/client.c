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
	struct win interface=create_interface();
	struct data_c *msg;
	setlocale(LC_ALL, "");
	socklen_t len=sizeof(struct sockaddr);
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(3452);
	s_addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	fd_socket=socket(AF_INET, SOCK_DGRAM,0);

	if(connect(fd_socket,(struct sockaddr*)&s_addr,sizeof(s_addr))==-1){
		perror("connect");
		exit(-1);
	}
	wprintw(interface.subwnd,"Введите слово:");
	while(1){
		hash=0;
		memset(buf,0,1536);
		bzero(&word,256);
		wrefresh(interface.subwnd);
		wgetstr(interface.subwnd,word);
		wclear(interface.subwnd);
		hash=jenkins_hash(word,strlen(word));
		if(send(fd_socket,&hash,sizeof(uint32_t),0)==-1){
			perror("send");
			exit(-1);
		}
		if(recv(fd_socket,buf,1536,0)==-1){
			perror("recv");
			exit(-1);
		}
		msg=(struct data_c*)buf;
		wclear(interface.subwnd2);
		wclear(interface.subwnd3);
		wclear(interface.subwnd4);
		wprintw(interface.subwnd2,"Перевод: %s", msg->out);
		wprintw(interface.subwnd3,"Синонимы\n %s",msg->sin);
		wprintw(interface.subwnd4,"Значение слова\n%s",msg->val);
		wrefresh(interface.subwnd2);
		wrefresh(interface.subwnd3);
		wrefresh(interface.subwnd4);
	}
	del_interface(&interface);
}
