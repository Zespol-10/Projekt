import os
import subprocess
import platform

#gcc -shared -fPIC Szyfr_RSA.c -o Szyfr_RSA.so
#g++ mangluje nazwy funkcji -- przed użyciem trzeba wstawic extern "C"{}
#-static jest potrzebne na Windowsie?

#1. skopiuj deklaracje funkcji i structow z pliku naglowkowego do konwerter.py
#2. skopiuj wynikowy kod do Szyfr.py
#3. skompiluj biblioteke dynamiczna

