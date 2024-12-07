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
void print(int1024 a);

int1024 multiply(int1024 a, int1024 b){ //błądddd!!!!
	int1024 c;
	for(int i  = 0; i < 2048/32; i++){
		ll res = 0; 
		for(int j = 0; j <=i; j++){
			if(i+1 < 2048/32) c.chunk[i+1]+=c.chunk[i]>>32;
			c.chunk[i]=c.chunk[i]-((c.chunk[i]>>32)<<32);
			c.chunk[i]+=a.chunk[j]*b.chunk[i-j];
		}
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

int1024 right_shift(int1024 a, int s){
	int1024 c;
	for(int  i = 2048/32-s-1; i >= 0; i--){
		c.chunk[i] = a.chunk[i+s];
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



int1024 add(int1024 a, int1024 b){ //a+b
	int1024 c;
	for(int i = 0; i < 2048/32; i++){
		c.chunk[i] += a.chunk[i]+b.chunk[i];
		if(c.chunk[i] >= (ll(1)<<32)){
			if(i < 2048/32-1){
				c.chunk[i+1] += (c.chunk[i]/(ll(1)<<32));
			}
			c.chunk[i] %= (ll(1)<<32);
		}
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

int1024 bitshift(int1024 a, ll s){
	int1024 b;
	ll bity = s%32;
	ll czunki = s/32;
	ll carry = 0;
	for(int i = czunki; i < 2048/32; i++){
		b.chunk[i] = (ll(a.chunk[i-czunki])<<ll(bity)) + ll(carry);
		carry = (b.chunk[i]/(ll(1)<<32));
		b.chunk[i]%=(ll(1)<<32);
	}
	return b;
}

int1024 right_bitshift(int1024 a, ll s){
	int1024 b;
	ll bity = s%32;
	ll czunki = s/32;
	int1024 d = bitshift(a,32-bity);
	b = right_shift(bitshift(a,32-bity),czunki+1);
	return b;
}

int count_zeroes(int1024 a){
	int i =0;
	while(i < 1024){
		if( (a.chunk[i/32]&(1<<ll(i%32)) ) != 0 ) return i;
		i++;
	}
	return i;
}

int1024 modulo(int1024 a, int1024 b){
	int a_len = 0;
	int b_len = 0;
	for(int i = 1023; i>=0; i--){
		int1024 d = bitshift(b,i);
		if(isGreaterOrEqual(a,d)) {
			a = subtract(a,d);
		}
	}
	return a;
}

struct pair_int1024{
	int1024 fi;
	int1024 se;
};


pair_int1024 division_with_modulo(int1024 a, int1024 b){
	int1024 c;
	pair_int1024 res;
	int a_len = 0;
	int b_len = 0;
	for(int i = 1023; i>=0; i--){
		int1024 d = bitshift(b,i);
		if(isGreaterOrEqual(a,d)) {
			a = subtract(a,d);
			c.chunk[i/32]+=(ll(1)<<(i%32));
		}
	}
	res.fi = c; res.se = a;
	return res;
}

int1024 random_int1024(){
	int1024 a;
	bool ok = true;
	bool ok2 = true;
	for(int i = 1024/32-1; i  >= 0; i-- ){
		for(int j = 31; j>=0; j--){	
				ll r = rand()%2;
				a.chunk[i]+=r*(ll(1)<<j);
		}
	}
	return a;
}

int1024 random_int1024(int1024 n){ 
	int1024 a = modulo(random_int1024(), n);
	return a;
}


int1024 fast_exponentation(int1024 a, int1024 b, int1024 mod){//wyglada ok
	cout<<"a = ";print(a);
	cout<<"b = ";print(b);
	cout<<"mod = ";print(mod);
	int1024 c; c.chunk[0] = 1;
	for(int i = 1024/32 - 1; i >= 0 ; i-- ){
		for(int j = 31; j >= 0; j--){
			int bit = (b.chunk[i]&(1<<j))>>j;
	//		debug(i);
	//		debug(b.chunk[i]);
	//		debug(i*32+j);
	//		debug(bit);
	//		cout<<"c = ";print(c);
	//		debug("square");
			c = multiply(c,c);
	//		cout<<"c = ";print(c);
			c = modulo(c,mod);
	//		debug("modulo");
	//		cout<<"c = ";print(c);
			if(bit == 1){
	//			debug("multiply by a");
				c = multiply(c,a);
	//			cout<<"c = ";print(c);
	//			debug("modulo");
				c = modulo(c,mod);
	//			cout<<"c = ";print(c);
			}
		}
		
	}
	return c;
}

bool isEqual(int1024 a, int1024 b){
	if(isGreaterOrEqual(a,b) && isGreaterOrEqual(b,a)) return true;
	return false;
}


bool RabinMiller(int1024 p, int k){
	//przydałoby się jeszcze sprawdzanie czy p > 2....
	if(p.chunk[0]%2 == 0) return false; // oczywiście to nie działa dla 2, ale to nie ważne
	int1024 c; int1024 jeden; jeden.chunk[0] = 1;
	c = subtract(p,jeden);
	cout<<"c = ";print(c);
	int s= count_zeroes(c);
	debug(s);
	int1024 d = right_bitshift(c,s);
	print(d);
	while(k--){
		debug(k);
		int1024 a = random_int1024(c);
		cout<<"a = ";print(a);
		int1024 jeden; jeden.chunk[0] = 1;
		bool ok = true;
		int1024 res = fast_exponentation(a,d,p);
		if(isEqual(res,jeden)) ok = false;
		debug(ok);
		if(!ok) continue;
		for(int r = 0; r < s; r++){
			debug(r);
			int1024 q = bitshift(d,r);
			print(a);
			print(q);
			print(p);
			res = fast_exponentation(a,q,p);
			print(res);
			if(isEqual(res,c)) ok = false;
			debug(ok);
			if(!ok) break;
		}
		debug(ok);
		if(ok) return false;
	}
	return true;
}



pair_int1024 Extended_Euclidean_Algorithm(int1024 a , int1024 b){ //musimy znalezc takie x,y > 0, że ax-by=gcd(a,b)
	int1024 zero;
	int1024 x;
	int1024 y;
	pair_int1024 result;
	if(isEqual(a,zero) ){
		y.chunk[0]=1;
		result.fi = x;
		result.se = y;
		return result;
	}
	if(isEqual(b,zero)){
		x.chunk[0]=1;
		result.fi = x;
		result.se = y;
		return result;
	}
	if(isGreaterOrEqual(a,b)){
		pair_int1024 d = division_with_modulo(a,b);
		pair_int1024 r = Extended_Euclidean_Algorithm(d.se,b);
		x = r.fi;
		y = add(r.se,multiply(d.fi,r.fi));
		result.fi = x;
		result.se = y;
		return result;
	}
	if(isGreaterOrEqual(b,a)){
		pair_int1024 d = division_with_modulo(b,a);
		pair_int1024 r = Extended_Euclidean_Algorithm(a,d.se);
		x =  add(r.fi,multiply(d.fi,r.se));
		y = r.se;
		result.fi = x;
		result.se = y;
		return result;
	}
	assert(0==4); //nic nie powinno tu dojść
	return result;
}

void print(int1024 a){
	int1024 dzies; dzies.chunk[0] = 10;
	int1024 zero;
	string s;
	if(isEqual(a,zero)){
		s = "0";
		cout<<s<<"\n";
		return;
	}
	while(!isEqual(a,zero)){
		pair_int1024 d = division_with_modulo(a,dzies);
		a = d.fi;
		s += char(d.se.chunk[0]+'0');
	}
	reverse(s.begin(),s.end());
	cout<<s<<"\n";






}


void RSA(){
	int1024 Z; Z.chunk[32/32] = 1;
	int1024 p,q;
	p = random_int1024(Z);
	q = random_int1024(Z);
	Z.chunk[32/32] = 0; Z.chunk[0] = 1;
	while(!RabinMiller(p,10)){
		p = subtract(p,Z);
	}
	while(!RabinMiller(q,10)){
		q = subtract(q,Z);
	}
	int1024 n = multiply(p,q);
	int1024 phi = multiply(subtract(p,Z),subtract(q,Z));
	int1024 e = random_int1024(phi);
	int1024 d;
	//check if e is coprime to phi...
	bool ok = false;
	while(!ok){
		pair_int1024 ab = Extended_Euclidean_Algorithm(e,phi);
		int1024 ax = multiply(ab.fi,e);
		int1024 by = multiply(ab.se,phi);
		int1024 diff;
		if(isGreaterOrEqual(ax,by)) diff = subtract(ax,by);
		else diff = subtract(by,ax);
		if(isEqual(diff,Z)) ok = true;
		d = modulo(ab.fi,phi);
		if(ok) break;
		e = random_int1024(phi);
	}
	print(d);
	print(e);
	print(n);


}




int main(){
	srand(time(NULL));
	int1024 a,b,c,d;
/*	a.chunk[0]=1;
	b.chunk[1] = 1;
	c = random_int1024(b);
	while(!RabinMiller(c,10)){
		c = subtract(c,a);
	}*/
	c.chunk[0] = 1;
	a.chunk[3] = 83;
	b = random_int1024(a);
/*
	int1024 jeden; jeden.chunk[0] = 1;
	int1024 dwies; dwies.chunk[0] = 210;
	pair_int1024 dziel = division_with_modulo(b,dwies);
	b = add(multiply(dwies,dziel.fi),jeden);

	
	while(!RabinMiller(b,10)){
		print(b);
		b = subtract(b,dwies);

	}
	print(b);*/
	int1024 P;
	P.chunk[0] = 366841091;
	P.chunk[1] = 1940089343;
	P.chunk[2] = 1584104064;
	P.chunk[3] = 78;
	print(P);
	debug(RabinMiller(P,10));


	// c = e.fi;


	//cout<<c.chunk[0]<<","<<c.chunk[1]<<","<<c.chunk[2]<<"\n";
	//RSA();
	return 0;
}