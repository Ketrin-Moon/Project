#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

struct descriptors{
        int  fd_request;
        int  fd_answer;
};

int main()
{
	key_t id;
struct descriptors des;

	id=ftok("server.c",'k');
        des.fd_request=msgget(id, IPC_CREAT|0666);
        id=ftok("client.c",'s');
        des.fd_answer=msgget(id,IPC_CREAT|0666);


	return 0;
}
