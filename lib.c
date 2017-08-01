void signal_handler(int signo)
{
	if(signo == SIGTERM){
		kill(0, signo);
		exit(EXIT_SUCCESS);
	}
}

char hashtab_lookup(struct data_client *message, struct for_func_table *out_table,
			struct for_func_table *sin_table, struct for_func_table *val_table)
{
	int index;

	index = message.hash;

	if(out_table[index] == NULL){
		strcpy(message.out, "This is no such word", 21);
		return message;
	}
	else{
		message.out = out_table[index];
		message.sin = sin_table[index];
		message.val = val_table[index];
	}
	return message;
}

void reply(struct msgvar *var, struct for_func_table *out_table,
                        struct for_func_table *sin_table, struct for_func_table *val_table)
{
	struct data_client message;

	while(1){
		msgrcv(var->request, &message, sizeof(message), 1L, 0);
		message.type = 2L;
		hashtab_lookup(&message, &out_table, &sin_table, &val_table);
		msgsnd(var->reply, &message, sizeof(message), 0);
	}

}
