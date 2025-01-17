#ifndef bits_stdcpp_H
#define bits_stdcpp_H
#include <stdio.h>
#include <cstdlib>
#include <time.h>

#endif
#include "Szyfr_RSA.hpp"

using namespace std;


int main(){
	srand(time(NULL));	
	key klucz = RSA();
	c_string s; init_c_string(&s);
	const char * lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras suscipit eget nunc at feugiat. Nunc convallis elit id mauris fringilla ultrices. Morbi iaculis egestas orci, vitae dapibus tellus porta at. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris tempor, purus vestibulum molestie laoreet, dolor erat tempus sapien, ut sollicitudin libero metus et odio. Sed elementum porttitor diam ac condimentum. Vestibulum finibus orci eget lacus vehicula, vitae tempor dui laoreet.";
	while(*lorem != '\0'){
		push_c_string(&s,*lorem);
		lorem++;
	}
	s = RSA_encode(s,klucz.publickey);
	//puts("Skopiuj i wklej ponizsze by program odkodowal zaszyfrowana tresc:");
	print_c_string(s);
	print_c_string(print_hex(klucz.privatekey.d));
	print_c_string(print_hex(klucz.privatekey.n));
	puts("");
	c_string t,u; free_c_string(&s); 
	s = read_c_string(); t = read_c_string(); u = read_c_string();

	klucz.privatekey.d = read_hex(t);
	klucz.privatekey.n = read_hex(u);
	free_c_string(&t);
	free_c_string(&u);
	u = RSA_decode(s,klucz.privatekey);
	free_c_string(&s);
	print_c_string(u);
	free_c_string(&u);
	return 0;
}