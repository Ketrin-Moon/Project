#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd_file, bytes;
	char c;
//	c = malloc(sizeof(char)*2);
	if((fd_file = open("out_table.txt",O_RDONLY)) < 0){
                printf("FD %d\n", fd_file);
                exit(1);
        }
        printf("READ\n");

        bytes = read(fd_file,&c,sizeof(char));
        if(bytes == -1){
                perror("!!!!!!!!!");
	}
	printf("%c\n", c);

	return 0;
}
