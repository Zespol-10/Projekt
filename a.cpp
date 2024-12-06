#include <bits/stdc++.h>
#define debug(x) cout<<#x<<" = "<<x<<"\n"
using ll = unsigned long long;
using namespace std;

class int1024{
public:
	ll chunk[2048/32];
	int1024(){
		for(int i = 0; i < 2048/32; i++){
			chunk[i] = 0;
		}


	}
};

int1024 multiply(int1024 a, int1024 b){
	int1024 c;
	for(int i  = 0; i < 2048/32; i++){
		ll res = 0; 
		for(int j = 0; j <=i; j++){
			res+=a.chunk[j]*b.chunk[i-j];
		}
		c.chunk[i]+=res;
		if(i+1 < 2048/32) c.chunk[i+1]+=c.chunk[i]>>32;
		c.chunk[i]=c.chunk[i]-((c.chunk[i]>>32)<<32);
	}

	return c;
}
int1024 shift(int1024 a, int s){
	int1024 c;
	for(int i = s; i < 2048/32; i++){
		c.chunk[i] = a.chunk[i-s];
	}

	return c;
}

int1024 subtract(int1024 a, int1024 b){ //a-b
	int1024 c;
	for(int i = 0; i < 2048/32; i++){
		if(a.chunk[i]  < b.chunk[i]){
			a.chunk[i]+=(ll(1)<<32);
			int j = i+1;
			while(a.chunk[j] == 0){
				a.chunk[j]+=(ll(1)<<32)-1;
				j++;
			}
			a.chunk[j]--;
		}
		c.chunk[i] = a.chunk[i]-b.chunk[i];
	}
	return c;
}

bool isGreaterOrEqual(int1024 a, int1024 b){ //a>=b
	for(int i = 2048/32-1; i >= 0; i--){
		if(a.chunk[i] > b.chunk[i]) return true;
		if(a.chunk[i] < b.chunk[i]) return false;
	}
	return true;
}

int1024 bitshift(int1024 a, int s){
	int1024 b;
	int bity = s%32;
	int czunki = s/32;
	ll carry = 0;
	for(int i = czunki; i < 2048/32; i++){
		b.chunk[i] = a.chunk[i-czunki]<<bity + carry;
		carry = b.chunk[i]-b.chunk[i]%(ll(1)<<32);
		b.chunk[i]%=(ll(1)<<32);
	}
	return b;
}

int1024 modulo(int1024 a, int1024 b){
	int a_len = 0;
	int b_len = 0;

	for(int i = 1023; i>=0; i--){
		int1024 d = bitshift(b,i);
		if(isGreaterOrEqual(a,d)) a = subtract(a,d);
	}
	return a;
}


int1024 fast_exponentation(int1024 a, int1024 b, int1024 mod){
	int1024 c; c.chunk[0] = 1;
	for(int i = 1024/32 - 1; i >= 0 ; i-- ){
	//	debug(i);
		for(int j = 31; j >= 0; j--){
	//		debug(j);
			int bit = (b.chunk[i]&(1<<j))>>j;
	//		debug(bit);
			c = multiply(c,c);
			c = modulo(c,mod);
			if(bit == 1){
				c = multiply(c,a);
				c = modulo(c,mod);
			}
		}
		
	}
	return c;
}

bool RabinMiller(int1024 p, int k){

	//przydałoby się jeszcze sprawdzanie czy p > 2....

	if(p.chunk[0]%2 == 0) return false; // oczywiście to nie działa dla 2, ale to nie ważne
	int1024 c; int1024 jeden; jeden.chunk[0] = 1;
	c = subtract(p,jeden);

//budowa


return true;
}

int main(){

	srand(time(NULL));

	int1024 a,b,c,d;
	a.chunk[0]=3;

	b.chunk[0]=1000;
	b.chunk[2]=1000;
	d.chunk[0] = 100;
	c = fast_exponentation(a,d,b);
	//for(int i = 0; i < 508; i++){
	//	c = multiply(c,a);
//		for(int i = 0; i < 64; i++){debug(i);debug(c.chunk[i]);}
	//	c= modulo(c,b);

	//}/

	cout<<c.chunk[0]<<","<<c.chunk[1]<<","<<c.chunk[2]<<"\n";




}