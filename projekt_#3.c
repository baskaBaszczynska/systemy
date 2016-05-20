#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

int fd[2];

char *arg[2];
arg[0]="./filtr";
arg[1]=NULL;

int i;

for (i=0;i<20;i++) {

pipe(fd);
pid_t pid=fork();

	if(pid==0){
		dup2(fd[1],1);
		close(fd[1]);

		close(fd[0]);
		system("./parec.sh");	
	
	}
	else { 
		dup2(fd[0],0);
		close(fd[0]);

		close(fd[1]);
		execvp(arg[0], arg);
	}
}

return 0;
}
	
	
