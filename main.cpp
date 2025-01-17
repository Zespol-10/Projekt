#ifndef bits_stdcpp_H
#define bits_stdcpp_H
#include <bits/stdc++.h>
#endif
#include "Szyfr_RSA.hpp"

using namespace std;


int main(){
	srand(time(NULL));	
	key klucz = RSA();
	string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
	s = RSA_encode(s,klucz.publickey);
	cout<<"Skopiuj i wklej ponizsze by program odkodowal zaszyfrowana tresc:\n";
	cout<<s<<"\n";
	cout<<print_hex(klucz.privatekey.d)<<"\n";
	cout<<print_hex(klucz.privatekey.n)<<"\n";
	string t,u;
	cin>>s>>t>>u;
	klucz.privatekey.d = read_hex(t);
	klucz.privatekey.n = read_hex(u);

	s = RSA_decode(s,klucz.privatekey);
	cout<<s<<"amogusidlaaae"<<"\n";
	return 0;
}