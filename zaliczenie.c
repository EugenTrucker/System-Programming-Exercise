#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc ,char *argv[]){
	
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		_exit(1);
	}
	if(pid > 0)
	{
		int status;
		wait(&status);
		if(WIFEXITED(status))
		{
			printf("Proces dziecka zakonczony z statuem: %d\n",WEXITSTATUS(status));
			
			
			struct stat buf;
			stat( argv[1], &buf);
			printf ("Rozmiar stworzonego pliku wynosi: %ld bajtow\n", buf.st_size);
			
				
		}
		else
		{
			printf("Proces dziecka nie zakonczyl pracy\n");
			return 0;
		}
		//Parent
		_exit(0);
	}
	if(pid == 0)
	{
		FILE *fd;
		int i = 0;
		fd = fopen(argv[1],"a+");
		if(!fd)
		{
			perror("fopen");
			_exit(100);
		}	
		if(fd == -1)
		{
			fprintf(stderr,"Nie mozna otworzyc pliku\n");
			perror("open");
			return 1;
		}
		else{
			fputs("Otwarto/ Utworzono Plik \n",stdout);
		}
		while(i<50){
			if(i%3==0){
				fprintf(fd, "%d", i);
				fprintf(fd, "%s", " ,");
				i++;
			}
			else{
				i++;
			}
			 	
		}
		fprintf(fd, "%s", "\n");
		
		
		fclose(fd);
		_exit(0);
			//Child
		
	}
	
	//?
	printf("aaaaaaaa\n");
	//?	
	return 0;
}






