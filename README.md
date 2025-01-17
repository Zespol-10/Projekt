# Projekt
Biblioteka w C/C++ zajmująca się operacjami na tekstach. 
Żeby przetestować projekt wpisz w terminalu:
```bash
gcc -c main.c -o main.o
gcc -c Szyfr_RSA.c -o Szyfr_RSA.o
gcc main.o Szyfr_RSA.o -o main
./main
```
lub po prostu
```bash
gcc main.c Szyfr_RSA.c -o main
./main
```
Żeby przetestować wersję pythonową wpisz w terminalu:
```bash
gcc -shared -o Szyfr_RSA.so -fPIC Szyfr_RSA.c
python3 Szyfr.py

```
Musisz mieć nadzieję, że wersja twojego Pythona (32/64-bitowa) zgadza się z wersją twojego gcc.
Musisz mieć też zainstalowaną bibliotekę ctypes.
Jeśli jej nie masz zainstaluj ją za pomocą polecenia:
```bash
pip install ctypes
```