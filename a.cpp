#include <bits/stdc++.h>
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
int1024 shift(int1024 a){
	int1024 c;
	//
	//
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

int1024 modulo(int1024 a, int1024 b){
	int1024 c;
	
	return c;
}


int main(){

/*	int1024 a,b,c;
	a.chunk[0]=5656565;
	a.chunk[2]=43434334;
	b.chunk[0]=5656566;
	b.chunk[2]=43434333;
	c = subtract(a,b);
	cout<<c.chunk[0]<<","<<c.chunk[1]<<"\n";*/




}