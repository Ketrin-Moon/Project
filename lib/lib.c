#include "../include/header.h"

void create_hashtable(struct for_func_table *table)
{
        int fd_file; char c='0'; int i, j; char word[1024];
        uint32_t hash;
	int bytes;
	setlocale(LC_CTYPE, "ru_RU.UTF8");
        if((fd_file = open(table->name,O_RDONLY)) == -1){
		printf("FD %d\n", fd_file);
		exit(1);
	}
        i=0;
        memset(word,0,1024);
        for(i=0; i< HASHTAB_SIZE; i++){
		for(j = 0; j < 256; j++)
                table->hashtable[i][j]=0;
        }
	i = 0;
	read(fd_file,&c,sizeof(char));
        while(c!='!'){
                do{
                        word[i]=c;
                        i++;
                        read(fd_file,&c,sizeof(char));
                }while(c!='*');
//		printf("%s ", word);
                hash=jenkins_hash(word,strlen(word));
//		printf("%d ", hash);
                c='0';
                i=0;
                memset(word,0,1024);
                read(fd_file,&c,sizeof(char));
                do{
                        table->hashtable[hash][i]=c;
                        i++;
                        read(fd_file,&c,sizeof(char));
                }while(c!='*');
//		printf("%s\n", table->hashtable[hash]);
		read(fd_file,&c,sizeof(char));
		i=0;


        }
}

void signal_handler(int signo)
{
	if(signo == SIGTERM){
		kill(0, signo);
		exit(EXIT_SUCCESS);
	}
}

void hashtab_lookup(struct data_client *message, struct for_func_table out_table,
			struct for_func_table sin_table, struct for_func_table val_table)
{
	int index;

	index = message->hash;

	if(out_table.hashtable[index] == NULL){
		strncpy(message->data.out, "This is no such word", 21);
//		return message;
	}
	else{
		strcpy(message->data.out, out_table.hashtable[index]);
		strcpy(message->data.sin, sin_table.hashtable[index]);
		strcpy(message->data.val, val_table.hashtable[index]);
	}
//	printf("out: %s\n", message->data.out);
//	printf("sin: %s\n", message->data.sin);
//	printf("val: %s\n", message->data.val);
//	return *message;
}

void reply(struct msgvar *var, struct for_func_table out_table,
                        struct for_func_table sin_table, struct for_func_table val_table)
{
	struct data_client message;
//	printf("REPLY\n");
	while(1){
		msgrcv(var->request, &message, sizeof(message), 1L, 0);
//		printf("Type: %li\n", message.type);
//		printf("hash: %d\n", message.hash);
		message.type = 2L;
		hashtab_lookup(&message, out_table, sin_table, val_table);
		msgsnd(var->reply, &message, sizeof(message), 0);
	}

}
