import ctypes

szyfr = ctypes.CDLL("./Szyfr_RSA.so")

class c_string(ctypes.Structure):
	_fields_ = [
		("rozm",ctypes.c_int),
		("rozm_max",ctypes.c_int),
		("wsk",ctypes.POINTER(ctypes.c_char)),
	]

class int1024(ctypes.Structure):
	_fields_ = [
		("chunks",ctypes.c_ulonglong * 64)
	]

class public_key(ctypes.Structure):
	_fields_ = [
		("e",int1024),
		("n",int1024)
	]

class private_key(ctypes.Structure):
	_fields_ = [
		("d",int1024),
		("n",int1024)
	]

class key(ctypes.Structure):
	_fields_ = [
		("publickey",public_key),
		("privatekey",private_key)
	]
'''
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
'''


szyfr.RSA.argtypes = []
szyfr.RSA.restype = key

szyfr.push_c_string.argtypes = [ctypes.POINTER(c_string),ctypes.c_char]
szyfr.push_c_string.restype = None

szyfr.init_c_string.argtypes = [ctypes.POINTER(c_string)]
szyfr.init_c_string.restype = None

szyfr.free_c_string.argtypes = [ctypes.POINTER(c_string)]
szyfr.free_c_string.restype = None

szyfr.RSA_encode.argtypes = [ctypes.POINTER(c_string),public_key,ctypes.POINTER(c_string)]
szyfr.RSA_encode.restype = None

szyfr.print_c_string.argtypes = [ctypes.POINTER(c_string)]
szyfr.print_c_string.restype = None

tekst = c_string()

szyfr.init_c_string(ctypes.byref(tekst))

szyfr.push_c_string(ctypes.byref(tekst),ctypes.c_char('a'.encode('utf-8')))
szyfr.push_c_string(ctypes.byref(tekst),ctypes.c_char('m'.encode('utf-8')))
szyfr.push_c_string(ctypes.byref(tekst),ctypes.c_char('o'.encode('utf-8')))
szyfr.push_c_string(ctypes.byref(tekst),ctypes.c_char('g'.encode('utf-8')))
szyfr.push_c_string(ctypes.byref(tekst),ctypes.c_char('u'.encode('utf-8')))
szyfr.push_c_string(ctypes.byref(tekst),ctypes.c_char('s'.encode('utf-8')))

klucz = szyfr.RSA()
print(klucz)

zaszyfrowany_tekst = c_string()
szyfr.init_c_string(ctypes.byref(zaszyfrowany_tekst))

szyfr.RSA_encode(ctypes.byref(tekst),klucz.publickey,ctypes.byref(zaszyfrowany_tekst))

szyfr.print_c_string(ctypes.byref(zaszyfrowany_tekst))

