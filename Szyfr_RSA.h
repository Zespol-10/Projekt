#define ll unsigned long long
#define min(a, b) ((a) < (b) ? (a) : (b))
#define true 1
#define false 0
//structy
typedef struct int1024{
	ll chunk[2048/32];
} int1024;
typedef struct public_key{
	struct int1024 e;
	int1024 n;
} public_key;
typedef struct private_key{
	int1024 d;
	int1024 n;
} private_key;
typedef struct key{
	public_key publickey;
	private_key privatekey;
} key;
typedef struct Montgomery_pack{
	int R_wykladnik;
	int1024 R;
	int1024 R_;
	int1024 N;
	int1024 M;
} Montgomery_pack;
typedef struct pair_int1024{
	int1024 fi;
	int1024 se;
} pair_int1024;
typedef struct pair_int{
	int fi;
	int se;	
} pair_int;
typedef struct vec_pair_int{
	int rozm;
	int rozm_max;
	pair_int* wsk;
} vec_pair_int;
typedef struct c_string{
	int rozm;
	int rozm_max;
	char* wsk;
} c_string;
//funkcje pomocnicze
__declspec(dllexport) int1024 multiply(int1024 a, int1024 b);
__declspec(dllexport) int1024 shift(int1024 a, int s);
__declspec(dllexport) int1024 right_shift(int1024 a, int s);
__declspec(dllexport) int get_bits(int1024 a);
__declspec(dllexport) int1024 subtract(int1024 a, int1024 b);
__declspec(dllexport) int1024 add(int1024 a, int1024 b);
__declspec(dllexport) bool isGreaterOrEqual(int1024 *a, int1024 *b);
__declspec(dllexport) int1024 bitshift(int1024 a, ll s);
__declspec(dllexport) int1024 right_bitshift(int1024 a, ll s);
__declspec(dllexport) int1024 fast_divide_by_two(int1024 a);
__declspec(dllexport) int count_zeroes(int1024 a);
__declspec(dllexport) int1024 modulo(int1024 a, int1024 b);
__declspec(dllexport) pair_int1024 division_with_modulo(int1024 a, int1024 b);
__declspec(dllexport) int1024 random_int1024_v();
__declspec(dllexport) int1024 random_int1024(int1024 n);
__declspec(dllexport) bool isEqual(int1024 a, int1024 b);
__declspec(dllexport) void init_vec_pair_int(vec_pair_int* a);
__declspec(dllexport) void push_vec_pair_int(vec_pair_int* a, int f, int s);
__declspec(dllexport) void free_vec_pair_int(vec_pair_int* a);
__declspec(dllexport) pair_int top_vec_pair_int(vec_pair_int* a);
__declspec(dllexport) void pop_vec_pair_int(vec_pair_int* a);
__declspec(dllexport) pair_int1024 Binary_Euclidean_Algorithm(int1024 a , int1024 b);
__declspec(dllexport) int1024 fast_divide(int1024 A, int b);
__declspec(dllexport) int1024 fast_modulo(int1024 A, int b);
__declspec(dllexport) Montgomery_pack init_Montgomery_algorithm(int1024 N, int wykladnik);
__declspec(dllexport) int1024 ConvertToMontgomeryForm(int1024 a, Montgomery_pack pack);
__declspec(dllexport) int1024 ConvertFromMontgomeryForm(int1024 a, Montgomery_pack pack);
__declspec(dllexport) int1024 REDC(int1024 T, Montgomery_pack pack);
__declspec(dllexport) int1024 fast_montgomery_exponentation(int1024 a, int1024 b, int1024 mod, Montgomery_pack pack);
__declspec(dllexport) bool RabinMiller(int1024 p, int k);
//funkcje udostepniane
__declspec(dllexport) key RSA();
__declspec(dllexport) void init_c_string(c_string* a);
__declspec(dllexport) void push_c_string(c_string* a, char z);
__declspec(dllexport) void free_c_string(c_string* a);
__declspec(dllexport) char get_c_string(c_string* a, int i);
__declspec(dllexport) void RSA_encode(c_string* s, public_key klucz, c_string* res);
__declspec(dllexport) void RSA_decode(c_string* s, private_key klucz, c_string* res);
__declspec(dllexport) void print_hex(int1024 a, c_string* res);
__declspec(dllexport) int1024 read_hex(c_string* a);
__declspec(dllexport) void print_c_string(c_string* a);
__declspec(dllexport) void read_c_string(c_string* res);
