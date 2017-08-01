#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pcap/pcap.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#define HASHTAB_SIZE 100

struct msgvar{
	int request;
	int reply;
};

struct for_func_table{
	char name[256];
	char hashtable[150][256];
};

struct data_client{
	long type;
	struct sockaddr_in client;
	u_int32_t hash;
	socklen_t *len;
	struct data {
		char out[256];
		char sin[256];
		char val[256];
	}data;
};

void signal_handler(int signo);
char hashtab_lookup(struct data_client *message, struct for_func_table out_table,
                        struct for_func_table sin_table, struct for_func_table val_table);
void reply(struct msgvar var, struct for_func_table *out_table,
                        struct for_func_table *sin_table, struct for_func_table *val_table);




