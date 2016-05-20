#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	
	int n,i,child,grandchild;
	int var=2;
	time_t mytime;
	struct tm *mytm;

	mytime=time(NULL);
	mytm=localtime(&mytime);
	
	printf("Hello!\nPodaj n: ");
	scanf("%d", &n);

	printf("\nMAIN PARENT\n My PID: %d,\n Parent PID: %d\n TIME: %d:%d:%d\n",getpid(),getppid(),mytm->tm_hour,mytm->tm_min,mytm->tm_sec);

	for(i=0;i<n;i++){
		if((child=fork())==0){		
			var=1;
			printf("\nCHILD %d\n My PID: %d,\n Parent PID: %d\n TIME: %d:%d:%d\n",i+1,getpid(),getppid(),mytm->tm_hour,mytm->tm_min,mytm->tm_sec);
			
			if((grandchild=fork())==0){
				var=0;
				printf("\n\tGRANDCHILD %d\n\t My PID: %d\n\t Parent PID: %d\n\t TIME: %d:%d:%d\n",i+1,getpid(),getppid(),mytm->tm_hour,mytm->tm_min,mytm->tm_sec);
				}
			wait();
			exit(1);
			}
		wait();
	}	

	printf("\nZmienna VAR nie zmienila sie pomimo modyfikacji w procesach: %d\n",var);
	printf("Bye, bye!\n");
			
	return 0;
}
