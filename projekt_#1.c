#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <features.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

	char znak;

	int roz_litery;
	int roz_cyfry;
	int roz_biale;
	int roz_symbole;

	int naj;

	/*	TWORZE I OTWIERAM PLIKI	*/

		
	int litery = open("litery.txt", O_CREAT | O_RDWR,0700);
		if (litery == -1){
			perror("litery.txt");
		}
	int cyfry = open("cyfry.txt", O_CREAT | O_WRONLY, 0700);
		if (cyfry == -1){
			perror("cyfry.txt");
		}

	int biale_znaki = open("biale_znaki.txt", O_CREAT | O_WRONLY, 0700);
		if (biale_znaki == -1){
			perror("biale_znaki.txt");
		}

	int symbole_ster = open("symbole_ster.txt", O_CREAT | O_WRONLY, 0700);
		if (symbole_ster == -1){
			perror("symbole_ster.txt");
		}
	
	/*	OTWIERAM PLIK Z RANDOMOWYMI DANYMI	*/

	int plik = open("plik.txt", O_RDONLY);
		if(plik == -1){
			perror("plik");
			exit(1);
		}
		else {

	/*	PRZESZUKUJE PLIK_RAND I ZAPISUJE ZNAKI DO ODPOWIEDNICH PLIKOW	*/

			while (read(plik, &znak,1)){

				if(isdigit(znak)){
					write(cyfry, &znak,1);
				}
				
				if(isalpha(znak)){
					write(litery, &znak,1);
				}
				
				if(iscntrl(znak)){
					write(symbole_ster, &znak,1);
				}
			
				if(isspace(znak)){
					write(biale_znaki, &znak,1);
				}
			}
		}
	
	roz_litery = lseek(litery,1,2);
	roz_cyfry = lseek(cyfry,1,2);
	roz_biale = lseek(biale_znaki,1,2);
	roz_symbole = lseek(symbole_ster,1,2);
	
	close(plik);
	close(litery);
	close(cyfry);
	close(biale_znaki);
	close(symbole_ster);


	/*	TWORZE PLIK RESULT	*/

	int result = open("result.log", O_CREAT | O_RDWR, 0700);
		if (result == -1){
			perror("result");
		}

	/*	SPRAWDZAM KTORY PLIK JEST NAJWIEKSZY	*/

	if(roz_litery > roz_cyfry){
		if(roz_litery > roz_biale){
			if(roz_litery > roz_symbole){

		/*	KOPIUJE PLIKI	*/

				naj=open("litery.txt", O_RDONLY);		

								
		/*	USUWAM RESZTE PLIKOW	*/

				remove("cyfry.txt");
				remove("biale_znaki.txt");
				remove("symbole_ster.txt");
			}
			
			else{
				naj=open("symbole_ster.txt", O_RDONLY);	

				remove("cyfry.txt");
				remove("biale_znaki.txt");
				remove("litery.txt");

			}
		}
	}
	else{
		if(roz_cyfry > roz_biale){
			if(roz_cyfry > roz_symbole){
				
				naj=open("cyfry.txt", O_RDONLY);	

				remove("symbole_ster.txt");
				remove("biale_znaki.txt");
				remove("litery.txt");
			}
			else{
				naj=open("symbole_ster.txt", O_RDONLY);	

				remove("cyfry.txt");
				remove("biale_znaki.txt");
				remove("litery.txt");
			}
		}
		else{
			if(roz_biale > roz_symbole){
				
				naj=open("biale_znaki.txt", O_RDONLY);	

				remove("cyfry.txt");
				remove("symbole_ster.txt");
				remove("litery.txt");			}
			else{
				naj=open("symbole_ster.txt", O_RDONLY);	

				remove("cyfry.txt");
				remove("biale_znaki.txt");
				remove("litery.txt");			}
		}
	}			
	
	while (read(naj, &znak,1)){
		write(result, &znak, 1);
	}	
	
	close(result);
	close(naj);

	return 0;
}
