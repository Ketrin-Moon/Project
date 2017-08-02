#include "../include/header.h"

int main()
{
	int sock;
	struct sockaddr_in server, client;
	struct data_client message;
	struct msgvar var;
	struct for_func_table out_table, sin_table, val_table;
	key_t ipckey;
	pid_t pid;
	pthread_t p_out, p_sin, p_val;

	setlocale(LC_ALL, "Rus");

	ipckey = ftok("generate_key", 'A');
	var.request = msgget(ipckey, IPC_CREAT|0666);
	ipckey = ftok("generate_key", 'B');
	var.reply = msgget(ipckey, IPC_CREAT|0666);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		perror("socket");
		exit(1);
	}

	if(fcntl(sock, F_SETFL, O_NONBLOCK) < 0){
		perror("fcntl");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(3436);
	server.sin_addr.s_addr = htons(INADDR_ANY);

	if(bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0){
		perror("bind");
		exit(1);
	}

	bzero(&out_table, sizeof(out_table));
	bzero(&sin_table, sizeof(sin_table));
	bzero(&val_table, sizeof(val_table));

	strncpy(out_table.name, "out_table.txt", 20);
	printf("%s\n", out_table.name);
	pthread_create(&p_out, NULL, (void*)create_hashtable, &out_table);
/*	strncpy(sin_table.name, "sin_table.txt", 20);
	pthread_create(&p_sin, NULL, (void*)create_hashtable, &sin_table);
	strncpy(val_table.name, "val_table.txt", 20);
	pthread_create(&p_val, NULL, (void*)create_hashtable, &val_table);
	pthread_join(p_sin, NULL);
	pthread_join(p_val, NULL);
*/
	pthread_join(p_out, NULL);
/*
	if((pid = fork()) < 0){
		perror("fork()");
		exit(1);
	}

	printf("Подключение клиента...\n");
	if(pid == 0){
		reply(&var, out_table, sin_table, val_table);
	}
	while(1){
		bzero(&message, sizeof(message));
		if(recvfrom(sock, &message.hash, sizeof(message.hash), 0, (struct sockaddr*)&message.client, message.len) == -1){
			perror("recvfrom");
			exit(1);
		}
		if(message.hash != 0){
			message.type = 1L;
			msgsnd(var.request, &message, sizeof(message), 0);
			msgrcv(var.reply, &message, sizeof(message), 2L, 0);
		if(sendto(sock, &message.data, sizeof(message.data), 0, (struct sockaddr *)&message.client, sizeof(message.client)) == -1){
				perror("send");
				exit(1);
			}
		}
	}

	signal(SIGTERM, signal_handler);
*/
	close(sock);

	return 0;
}
