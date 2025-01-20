# Projekt
Biblioteka w C/C++ zajmująca się operacjami na tekstach. 

Część Szyfr RSA:
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
python3 Szyfr.py

```
lub
```bash
py Szyfr.py
```
Musisz mieć nadzieję, że wersja twojego Pythona (32/64-bitowa) zgadza się z wersją twojego gcc.
W przypadku Windowsa musisz mieć zainstalowanego x86_64-w64-mingw32-gcc pod ścieżką C:\msys64\mingw64\bin.
Musisz mieć też zainstalowaną pythonowe biblioteki:
ctypes, subprocess, os
Jeśli jej nie masz zainstaluj ją za pomocą polecenia:
```bash
pip install ctypes
pip install subprocess
pip install os
```
--------------------------------------
Część base64

Testowy program może zostać skompilowany i uruchomiony przy pomocy:

```bash
g++ -o main.cpp base64.cpp
./a
```

