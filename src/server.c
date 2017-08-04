#include "../include/header.h"
int main()
{
	int sock;
	struct sockaddr_in addr, client;
	uint32_t buf;
	char name[20] = "Connected";
 	struct data_client message;
        struct msgvar var;
        struct for_func_table out_table, sin_table, val_table;
        key_t ipckey;
        pid_t pid;
        pthread_t p_out, p_sin, p_val;

	socklen_t len = sizeof(struct sockaddr);

	setlocale(LC_ALL, "Rus");

	ipckey = ftok("server", 'b');
        var.request = msgget(ipckey, IPC_CREAT|0666);
	ipckey = ftok("client", 'c');
        var.reply = msgget(ipckey, IPC_CREAT|0666);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(3452);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("bind");
		exit(1);
	}

	bzero(&out_table, sizeof(out_table));
        bzero(&sin_table, sizeof(sin_table));
        bzero(&val_table, sizeof(val_table));

        strncpy(out_table.name, "out_table.txt", 20);
       	pthread_create(&p_out, NULL, (void*)create_hashtable, &out_table);
        strncpy(sin_table.name, "sin_table.txt", 20);
        pthread_create(&p_sin, NULL, (void*)create_hashtable, &sin_table);
        strncpy(val_table.name, "val_table.txt", 20);
      	 pthread_create(&p_val, NULL, (void*)create_hashtable, &val_table);

        pthread_join(p_out, NULL);
        pthread_join(p_sin, NULL);
        pthread_join(p_val, NULL);

	if((pid = fork()) < 0){
                perror("fork()");
                exit(1);
        }

        if(pid == 0){
                reply(&var, out_table, sin_table, val_table);
        }


//	printf("Подключение клиента...\n");
	while(1){
		if(recvfrom(sock, &buf, sizeof(buf), 0, (struct sockaddr *)&client, &len) == -1){
			perror("recvfrom");
			exit(1);
		}
		if(buf != 0){
                        message.type = 1L;
                     	message.len = len;
                        message.hash = buf;
                        message.client = client;
                        msgsnd(var.request, &message, sizeof(message), 0);
                        msgrcv(var.reply, &message, sizeof(message), 2L, 0);

//			printf("Клиент подключен: %d\nОтвет сервера...\n", buf);
			if(sendto(sock, &message.data, sizeof(message.data), 0, (struct sockaddr *)&client, len) == -1){
				perror("sendto");
			exit(1);
			}
		}
	}

	signal(SIGTERM, signal_handler);

	close(sock);

	return 0;
}
