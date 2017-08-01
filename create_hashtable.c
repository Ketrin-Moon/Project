#include <fcntl.h>

void create_hashtable(struct for_func_table *table)
{
	int fd_file; char c='0'; int i; char word[1024];
	uint32_t hash;

	fd_file=open(table->name,O_RDONLY);
	i=0;
	memset(word,0,256);
	read(fd_file,&c,sizeof(char));
	for(i=0; i< HASHTAB_SIZE; i++){
		table->table[i]=NULL;
	}
	while(c!='!'){
		do{
			word[i]=c;
			i++;
			read(fd_file,&c,sizeof(char));
		}while(c!='*');
		hash=jenkins_hash(word,strlen(word));
		c='0';
		i=0;
		memset(word,0,256);
		read(fd_file,&c,sizeof(char));
		do{
			table->hashtable[hash][i]=c;
			i++;
			read(fd_file,&c,sizeof(char));
		}while(c!='*');
		read(fd_file,&c,sizeof(char));
	}
}
