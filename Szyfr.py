import ctypes
import os
import subprocess

if os.name == 'posix':
	compile_command = [
		"gcc",
		"-shared",
		"-fPIC",
		"Szyfr_RSA.c",
		"-o",
		"Szyfr_RSA.so"
        ]
	try:
		subprocess.run(compile_command, check=True)
	except:
		print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
		exit()
	lib = ctypes.CDLL("./Szyfr_RSA.so")
elif os.name == 'nt':
        try:
                os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
                subprocess.run(['x86_64-w64-mingw32-gcc', '-shared', 'Szyfr_RSA.c', '-o', 'Szyfr_RSA.dll'], check=True)
        except:
                print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane x86_64-w64-mingw32-gcc.exe pod sciezka C:\\msys64\\mingw64\\bin ")
                exit()
        lib = ctypes.CDLL("./Szyfr_RSA.dll")
#kod z konwerter.py


class int1024(ctypes.Structure):
	_fields_ = [
		('chunk',ctypes.c_ulonglong*66),
	]
class public_key(ctypes.Structure):
	_fields_ = [
		('e',int1024),
		('n',int1024),
	]
class private_key(ctypes.Structure):
	_fields_ = [
		('d',int1024),
		('n',int1024),
	]
class key(ctypes.Structure):
	_fields_ = [
		('publickey',public_key),
		('privatekey',private_key),
	]
class Montgomery_pack(ctypes.Structure):
	_fields_ = [
		('R_wykladnik',ctypes.c_int),
		('R',int1024),
		('R_',int1024),
		('N',int1024),
		('M',int1024),
	]
class pair_int1024(ctypes.Structure):
	_fields_ = [
		('fi',int1024),
		('se',int1024),
	]
class pair_int(ctypes.Structure):
	_fields_ = [
		('fi',ctypes.c_int),
		('se',ctypes.c_int),
	]
class vec_pair_int(ctypes.Structure):
	_fields_ = [
		('rozm',ctypes.c_int),
		('rozm_max',ctypes.c_int),
		('wsk',ctypes.POINTER(pair_int)),
	]
class c_string(ctypes.Structure):
	_fields_ = [
		('rozm',ctypes.c_int),
		('rozm_max',ctypes.c_int),
		('wsk',ctypes.POINTER(ctypes.c_char)),
	]
lib.multiply.restype = int1024
lib.multiply.argtypes = [int1024,int1024]
lib.shift.restype = int1024
lib.shift.argtypes = [int1024,ctypes.c_int]
lib.right_shift.restype = int1024
lib.right_shift.argtypes = [int1024,ctypes.c_int]
lib.get_bits.restype = ctypes.c_int
lib.get_bits.argtypes = [int1024]
lib.subtract.restype = int1024
lib.subtract.argtypes = [int1024,int1024]
lib.add.restype = int1024
lib.add.argtypes = [int1024,int1024]
lib.isGreaterOrEqual.restype = ctypes.c_bool
lib.isGreaterOrEqual.argtypes = [ctypes.POINTER(int1024),ctypes.POINTER(int1024)]
lib.bitshift.restype = int1024
lib.bitshift.argtypes = [int1024,ctypes.c_ulonglong]
lib.right_bitshift.restype = int1024
lib.right_bitshift.argtypes = [int1024,ctypes.c_ulonglong]
lib.fast_divide_by_two.restype = int1024
lib.fast_divide_by_two.argtypes = [int1024]
lib.count_zeroes.restype = ctypes.c_int
lib.count_zeroes.argtypes = [int1024]
lib.modulo.restype = int1024
lib.modulo.argtypes = [int1024,int1024]
lib.division_with_modulo.restype = pair_int1024
lib.division_with_modulo.argtypes = [int1024,int1024]
lib.random_int1024_v.restype = int1024
lib.random_int1024_v.argtypes = []
lib.random_int1024.restype = int1024
lib.random_int1024.argtypes = [int1024]
lib.isEqual.restype = ctypes.c_bool
lib.isEqual.argtypes = [int1024,int1024]
lib.init_vec_pair_int.restype = None
lib.init_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
lib.push_vec_pair_int.restype = None
lib.push_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int),ctypes.c_int,ctypes.c_int]
lib.free_vec_pair_int.restype = None
lib.free_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
lib.top_vec_pair_int.restype = pair_int
lib.top_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
lib.pop_vec_pair_int.restype = None
lib.pop_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
lib.Binary_Euclidean_Algorithm.restype = pair_int1024
lib.Binary_Euclidean_Algorithm.argtypes = [int1024,int1024]
lib.fast_divide.restype = int1024
lib.fast_divide.argtypes = [int1024,ctypes.c_int]
lib.fast_modulo.restype = int1024
lib.fast_modulo.argtypes = [int1024,ctypes.c_int]
lib.init_Montgomery_algorithm.restype = Montgomery_pack
lib.init_Montgomery_algorithm.argtypes = [int1024,ctypes.c_int]
lib.ConvertToMontgomeryForm.restype = int1024
lib.ConvertToMontgomeryForm.argtypes = [int1024,Montgomery_pack]
lib.ConvertFromMontgomeryForm.restype = int1024
lib.ConvertFromMontgomeryForm.argtypes = [int1024,Montgomery_pack]
lib.REDC.restype = int1024
lib.REDC.argtypes = [int1024,Montgomery_pack]
lib.fast_montgomery_exponentation.restype = int1024
lib.fast_montgomery_exponentation.argtypes = [int1024,int1024,int1024,Montgomery_pack]
lib.RabinMiller.restype = ctypes.c_bool
lib.RabinMiller.argtypes = [int1024,ctypes.c_int]
lib.RSA.restype = key
lib.RSA.argtypes = []
lib.init_c_string.restype = None
lib.init_c_string.argtypes = [ctypes.POINTER(c_string)]
lib.push_c_string.restype = None
lib.push_c_string.argtypes = [ctypes.POINTER(c_string),ctypes.c_char]
lib.free_c_string.restype = None
lib.free_c_string.argtypes = [ctypes.POINTER(c_string)]
lib.get_c_string.restype = ctypes.c_char
lib.get_c_string.argtypes = [ctypes.POINTER(c_string),ctypes.c_int]
lib.RSA_encode.restype = None
lib.RSA_encode.argtypes = [ctypes.POINTER(c_string),public_key,ctypes.POINTER(c_string)]
lib.RSA_decode.restype = None
lib.RSA_decode.argtypes = [ctypes.POINTER(c_string),private_key,ctypes.POINTER(c_string)]
lib.print_hex.restype = None
lib.print_hex.argtypes = [int1024,ctypes.POINTER(c_string)]
lib.read_hex.restype = int1024
lib.read_hex.argtypes = [ctypes.POINTER(c_string)]
lib.print_c_string.restype = None
lib.print_c_string.argtypes = [ctypes.POINTER(c_string)]
lib.read_c_string.restype = None
lib.read_c_string.argtypes = [ctypes.POINTER(c_string)]






#program wlasciwy

szyfr = lib

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

