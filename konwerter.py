def konwertuj():
    c_header = """
typedef struct int1024{
	unsigned long long chunk[64];
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

int1024 multiply(int1024 a, int1024 b);
int1024 shift(int1024 a, int s);
int1024 right_shift(int1024 a, int s);
int get_bits(int1024 a);
int1024 subtract(int1024 a, int1024 b);
int1024 add(int1024 a, int1024 b);
bool isGreaterOrEqual(int1024 *a, int1024 *b);
int1024 bitshift(int1024 a, unsigned long long s);
int1024 right_bitshift(int1024 a, unsigned long long s);
int1024 fast_divide_by_two(int1024 a);
int count_zeroes(int1024 a);
int1024 modulo(int1024 a, int1024 b);
pair_int1024 division_with_modulo(int1024 a, int1024 b);
int1024 random_int1024_v();
int1024 random_int1024(int1024 n);
bool isEqual(int1024 a, int1024 b);
void init_vec_pair_int(vec_pair_int* a);
void push_vec_pair_int(vec_pair_int* a, int f, int s);
void free_vec_pair_int(vec_pair_int* a);
pair_int top_vec_pair_int(vec_pair_int* a);
void pop_vec_pair_int(vec_pair_int* a);
pair_int1024 Binary_Euclidean_Algorithm(int1024 a , int1024 b);
int1024 fast_divide(int1024 A, int b);
int1024 fast_modulo(int1024 A, int b);
Montgomery_pack init_Montgomery_algorithm(int1024 N, int wykladnik);
int1024 ConvertToMontgomeryForm(int1024 a, Montgomery_pack pack);
int1024 ConvertFromMontgomeryForm(int1024 a, Montgomery_pack pack);
int1024 REDC(int1024 T, Montgomery_pack pack);
int1024 fast_montgomery_exponentation(int1024 a, int1024 b, int1024 mod, Montgomery_pack pack);
bool RabinMiller(int1024 p, int k);

key RSA();
void init_c_string(c_string* a);
void push_c_string(c_string* a, char z);
void free_c_string(c_string* a);
char get_c_string(c_string* a, int i);
void RSA_encode(c_string* s, public_key klucz, c_string* res);
void RSA_decode(c_string* s, private_key klucz, c_string* res);
void print_hex(int1024 a, c_string* res);
int1024 read_hex(c_string* a);
void print_c_string(c_string* a);
void read_c_string(c_string* res);
"""
    znaki_znaczace = list("(),;*[]{}")
    for d in znaki_znaczace:
        c_header = c_header.replace(d, " " + d + " ")
    c_header = ''.join(filter(lambda d: d not in "\n\t", c_header))
    c_header = c_header.split(" ")
    c_header = list(filter(lambda d: d != '', c_header))

    mapa = {}
    mapa['&'] = ''
    mapa['int &'] = 'ctypes.c_int'
    mapa['char &'] = 'ctypes.c_char'
    mapa['float &'] = 'ctypes.c_float'
    mapa['bool &'] = 'ctypes.c_bool'
    mapa['long &'] = 'ctypes.c_long'
    mapa['long long &'] = 'ctypes.c_longlong'
    mapa['unsigned long long &'] = 'ctypes.c_ulonglong'
    mapa['char [ ] &'] = 'ctypes.c_char_p'
    mapa['char * &'] = 'ctypes.POINTER(ctypes.c_char)'
    mapa['# &'] = '#'
    mapa['# * &'] = 'ctypes.POINTER(#)'
    mapa['int * &'] = 'ctypes.POINTER(ctypes.c_int)'
    mapa['int * & [ $ ]'] = 'ctypes.POINTER(ctypes.c_int)*$'
    mapa['int & [ $ ]'] = 'ctypes.c_int*$'
    mapa['void &'] = 'None'
    mapa['# * &'] = 'ctypes.POINTER(#)'
    mapa['unsigned long long & [ $ ]'] = 'ctypes.c_ulonglong*$'

    mapa2 = {}
    mapa2[''] = ''
    mapa2['int'] = 'ctypes.c_int'
    mapa2['char'] = 'ctypes.c_char'
    mapa2['float'] = 'ctypes.c_float'
    mapa2['bool'] = 'ctypes.c_bool'
    mapa2['long'] = 'ctypes.c_long'
    mapa2['long long'] = 'ctypes.c_longlong'
    mapa2['unsigned long long'] = 'ctypes.c_ulonglong'
    mapa2['char [ ]'] = 'ctypes.c_char_p'
    mapa2['char *'] = 'ctypes.POINTER(ctypes.c_char)'
    mapa2['#'] = '#'
    mapa2['# *'] = 'ctypes.POINTER(#)'
    mapa2['int *'] = 'ctypes.POINTER(ctypes.c_int)'
    mapa2['int * [ $ ]'] = 'ctypes.POINTER(ctypes.c_int)*$'
    mapa2['int [ $ ]'] = 'ctypes.c_int*$'
    mapa2['# *'] = 'ctypes.POINTER(#)'

    struct_declaration = False
    function_declaration = False
    defined_structs = []
    stack = []
    depth = 0
    start_depth = 0
    chunks = [[]]
    flag = False
    python_code = ""
    nazwa = ""
    placeholder = ""
    placeholder2 = ""

    for i in range(len(c_header)):
        if c_header[i] in ['{', '[', '(']:
            depth += 1
        if c_header[i] in ['}', ']', ')']:
            depth -= 1
        if not struct_declaration and not function_declaration:
            if c_header[i] in ["typedef", "struct"]:
                struct_declaration = True
                start_depth = depth
                chunks.append([])
                flag = True
            elif c_header[i] in ["bool", "void", "unsigned", "int", "long", "char", "float"] or c_header[i] in defined_structs:
                if not struct_declaration:
                    function_declaration = True
                    start_depth = depth
                    chunks.append([])
                    flag = True
                    stack = []

        if struct_declaration and c_header[i] == "{" and flag:
            flag = False

        if function_declaration and c_header[i] == "(" and flag:
            typ = ' '.join(stack)
            typ = mapa[typ]
            typ = typ.replace("#", placeholder)
            typ = typ.replace('$', placeholder2)
            python_code += "lib." + nazwa + ".restype = " + typ + "\n"
            python_code += "lib." + nazwa + ".argtypes = ["
            stack = []
            flag = False

        if function_declaration:
            if c_header[i] == ',' or c_header[i] == ')':
                typ = ' '.join(stack)
                typ = typ.replace("&", "").split(" ")
                typ = list(filter(lambda d: d != "", typ))
                typ = ' '.join(typ)
                typ = mapa2[typ]
                typ = typ.replace("#", placeholder)
                typ = typ.replace('$', placeholder2)
                python_code += typ
                if c_header[i] == ')':
                    python_code += "]\n"
                else:
                    python_code += ","
                stack = []
            else:
                if c_header[i] in ["bool", "void", "unsigned", "int", "long", "char", "float"]:
                    stack.append(c_header[i])
                elif c_header[i] in defined_structs:
                    stack.append('#')
                    placeholder = c_header[i]
                elif c_header[i].isdigit():
                    stack.append('$')
                    placeholder2 = c_header[i]
                elif c_header[i] in ["[", "]", "*"]:
                    stack.append(c_header[i])
                elif c_header[i] == '(' or c_header[i] == ';':
                    pass
                else:
                    stack.append('&')
                    nazwa = c_header[i]

        if struct_declaration and depth > 0:
            if c_header[i] == ';':
                typ = ' '.join(stack)
                typ = mapa[typ]
                typ = typ.replace('#', placeholder)
                typ = typ.replace('$', placeholder2)
                python_code += "\t\t('" + nazwa + "'," + typ + "),\n"
                stack = []
            else:
                if c_header[i] in ["bool", "void", "unsigned", "int", "long", "char", "float"]:
                    stack.append(c_header[i])
                elif c_header[i] in defined_structs:
                    stack.append('#')
                    placeholder = c_header[i]
                elif c_header[i].isdigit():
                    stack.append('$')
                    placeholder2 = c_header[i]
                elif c_header[i] in ["[", "]", "*"]:
                    stack.append(c_header[i])
                elif c_header[i] == '{' or c_header[i] == 'struct':
                    pass
                else:
                    stack.append('&')
                    nazwa = c_header[i]

        if struct_declaration and flag and c_header[i] not in ["struct", "typedef"]:
            defined_structs.append(c_header[i])
            python_code += "class " + c_header[i] + "(ctypes.Structure):\n"
            python_code += "\t_fields_ = [\n"

        if start_depth == depth and c_header[i] == ';':
            if struct_declaration:
                python_code += "\t]\n"
            struct_declaration = False
            function_declaration = False

        if struct_declaration or function_declaration:
            chunks[-1].append(c_header[i])

    return python_code


print(konwertuj())
