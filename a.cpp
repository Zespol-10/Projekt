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
	for(int i = 0; i < 2048/32; i++){
		if(a.chunk[i] > b.chunk[i]) return true;
		if(a.chunk[i] < b.chunk[i]) return false;
	}
	return true;
}

int1024 modulo(int1024 a, int1024 b){
	int1024 c;
	int a_len = 0;
	int b_len = 0;
	for(int i = 2048/32-1; i>=0; i--){
		if(a.chunk[i] != 0){
			a_len = i+1;
			break;
		}
	}
	for(int i = 2048/32-1; i>=0; i--){
		if(b.chunk[i] != 0){
			b_len = i+1;
			break;
		}
	}
	for(int i = a_len-1; i>=b_len-1; i--){
		ll A = a.chunk[i];
		ll B = b.chunk[b_len]+1;
		int1024 d; d.chunk[0]=A/B;
		a  = subtract(a,shift(multiply(d,b),i-b_len));
		if(i>=b_len) {
			a.chunk[i-1]+=a.chunk[i]<<32;
			a.chunk[i]=0;
		}




	}
	int cnt = 0;
	while(isGreaterOrEqual(a,b)){
		subtract(a,b);
		cnt++;

		if(cnt > 1) cerr<<"Linia 100 a.cpp Blad\n"; 

	}
	
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