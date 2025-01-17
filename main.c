#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Szyfr_RSA.h"

int main(){

	//Zainicjanilizuj generator liczb pseudolosowych
	srand(time(NULL));	
	//Wygeneruj klucz RSA
	key klucz = RSA();
	//Zadeklaruj obiekt c_string i wczytaj do niego tekst
	c_string* tekst = (c_string *)malloc(sizeof(c_string));  init_c_string(tekst);
	const char * lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras suscipit eget nunc at feugiat. Nunc convallis elit id mauris fringilla ultrices. Morbi iaculis egestas orci, vitae dapibus tellus porta at. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris tempor, purus vestibulum molestie laoreet, dolor erat tempus sapien, ut sollicitudin libero metus et odio. Sed elementum porttitor diam ac condimentum. Vestibulum finibus orci eget lacus vehicula, vitae tempor dui laoreet.";
	while(*lorem != '\0'){
		push_c_string(tekst,*lorem);
		lorem++;
	}
	//zaszyfruj tekst
	c_string* zaszyfrowany_tekst = (c_string *)malloc(sizeof(c_string)); init_c_string(zaszyfrowany_tekst);
	RSA_encode(tekst,klucz.publickey,zaszyfrowany_tekst);
	//wypisz zaszyfrowany tekst na ekran
	print_c_string(zaszyfrowany_tekst);

	//wypisz klucz prywatny w miare przyjaznej do skopiowania postaci
	c_string* prywatny_klucz_d = (c_string *)malloc(sizeof(c_string)); init_c_string(prywatny_klucz_d);
	print_hex(klucz.privatekey.d, prywatny_klucz_d);
	c_string* prywatny_klucz_n = (c_string *)malloc(sizeof(c_string)); init_c_string(prywatny_klucz_n);
	print_hex(klucz.privatekey.n, prywatny_klucz_n);

	print_c_string(prywatny_klucz_d);
	print_c_string(prywatny_klucz_n);

	//nie zapomnij zwolnic zaalokowanej pamieci c_stringow!!! uzyj do tego funkcji free_c_string
	free_c_string(tekst); 
	free_c_string(zaszyfrowany_tekst);
	free_c_string(prywatny_klucz_d);
	free_c_string(prywatny_klucz_n);

	//wypisz linijke przerwy na ekran
	puts("");
	//jesli uzytkownik wklei teraz wynik dzialania czesci szyfrujacej - czyli
	//kolejno: zaszyfrowany_tekst, prywatny_klucz_d, prywatny_klucz_n
	//to program odszyfruje z ich pomoca tekst
	
	read_c_string(zaszyfrowany_tekst);
	read_c_string(prywatny_klucz_d);
	read_c_string(prywatny_klucz_n);

	klucz.privatekey.d = read_hex(prywatny_klucz_d);
	klucz.privatekey.n = read_hex(prywatny_klucz_n);
	RSA_decode(zaszyfrowany_tekst,klucz.privatekey,tekst);
	print_c_string(tekst);
	
	free_c_string(tekst); 
	free_c_string(zaszyfrowany_tekst);
	free_c_string(prywatny_klucz_d);
	free_c_string(prywatny_klucz_n);

	//jeszcze trzeba zwolnic pamiec samych c_stringow
	free(tekst);
	free(zaszyfrowany_tekst);
	free(prywatny_klucz_d);
	free(prywatny_klucz_n);
	return 0;
}