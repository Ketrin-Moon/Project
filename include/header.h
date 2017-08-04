#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <locale.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <ncurses.h>
#include <termios.h>
#include <wchar.h>

#define HASHTAB_SIZE 201

struct msgvar{
	int request;
	int reply;
};

struct for_func_table{
	char name[256];
	char hashtable[HASHTAB_SIZE][256];
};

struct data_client{
	long type;
	struct sockaddr_in client;
	u_int32_t hash;
	socklen_t len;
	struct data {
		char out[256];
		char sin[256];
		char val[256];
	}data;
};
struct win{
        WINDOW*wnd;
        WINDOW*wnd2;
        WINDOW*wnd3;
	WINDOW*wnd4;
	WINDOW*wnd5;
        WINDOW*subwnd;
        WINDOW*subwnd2;
        WINDOW*subwnd3;
	WINDOW*subwnd4;
	WINDOW*subwnd5;
};

struct win create_interface();
void del_interface(struct win*);
void color_pair(WINDOW *win, int color_bg);
void create_hashtable(struct for_func_table *table);
uint32_t jenkins_hash(char *key, size_t len);
void signal_handler(int signo);
void hashtab_lookup(struct data_client *message, struct for_func_table out_table,
                        struct for_func_table sin_table, struct for_func_table val_table);
void reply(struct msgvar *var, struct for_func_table out_table,
                        struct for_func_table sin_table, struct for_func_table val_table);




