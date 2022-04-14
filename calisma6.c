#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_MODE          (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int main(int argc, char*argv[])
{
	if(argc!=2)
	{
		printf("bir dosya ismi vermelisiniz.\n");
		exit(-1);
	}
	int fd = open(argv[1], O_RDONLY,FILE_MODE);
	if(fd<0)
	{
		printf("dosya okuma hatasi.\n");
		exit(-2);
	}
	int fd2 = open("tersten.txt", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	if(fd2<0)
	{
		printf("dosya olusturma hatasi.\n");
		exit(-3);
	}
	char buf[1];
	int n = 1;
	int cursor = lseek(fd,0,SEEK_END)-1;

	while(cursor>=0)
	{
		lseek(fd,cursor,SEEK_SET);
		read(fd,buf,1);
		write(fd2,buf,1);
		if(fd2<0)
		{
			printf("yazma hatasi.\n");
			exit(-4);
		}
	cursor--;
	}
	close(fd);
	close(fd2);
return 0;

}
