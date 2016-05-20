#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>

int main() {

int isDigit=1;
float linesWithNumbers=0;
float lines=0;
int i=0;
char znak;
float wynik;
int plik=open("plik.txt", O_CREAT|O_RDWR,0700);

while (read(0, &znak, 1)) {

	if (!isdigit(znak)) {
		isDigit=0;
	}

	if (isdigit(znak) || isalpha(znak)) {
		write(1,&znak,1);

		i++;
	}
	
	if (i==8) { 
		write(1,"\n",1); 
		
		i=0;
		lines++;
		if(isDigit) {
			linesWithNumbers++;
		}
		isDigit=1;
	}
}
wynik=(linesWithNumbers/lines)*100;
int a=sizeof(wynik);
write(plik,&wynik,a);
write(plik,"\n",1);

close(plik);
return 0;
}
