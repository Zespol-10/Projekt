#ifndef bits_stdcpp_H
#define bits_stdcpp_H
#include <bits/stdc++.h>
#endif
#include "Szyfr_RSA.hpp"

using namespace std;


int main(){
	srand(time(NULL));	
	int1024 a,b,c,d,e;
	Szyfr_RSA szyf;
	key klucz = szyf.RSA();
	string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
	s = szyf.RSA_encode(s,klucz.publickey);
	cout<<"Skopiuj i wklej ponizsze by program odkodowal zaszyfrowana tresc:\n";
	cout<<s<<"\n";
	cout<<szyf.print_hex(klucz.privatekey.d)<<"\n";
	cout<<szyf.print_hex(klucz.privatekey.n)<<"\n";
	string t,u;
	cin>>s>>t>>u;
	klucz.privatekey.d = szyf.read_hex(t);
	klucz.privatekey.n = szyf.read_hex(u);

	s = szyf.RSA_decode(s,klucz.privatekey);
	cout<<s<<"\n";
	return 0;
}