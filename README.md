# Projekt
Biblioteka w C/C++ zajmująca się operacjami na tekstach. 

## RSA:
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
## base64

Testowy program może zostać skompilowany i uruchomiony przy pomocy:

```bash
g++ -o main.cpp base64.cpp arithmetic.cpp -o main
./main base64
```

## arithmetic

Testowy program może zostać skompilowany i uruchomiony przy pomocy:

```bash
g++ -o main.cpp base64.cpp arithmetic.cpp -o main
./main arithmetic "${FILE_PATH}"
```

## Specyfikacja funkcji

### `const char *detect_language(char *text)`

#### Opis:
Funkcja `detect_language` analizuje tekst i określa, w jakim języku został napisany na podstawie porównania częstotliwości występowania liter z predefiniowanymi profilami językowymi.

#### Jak działa:
1. **Analiza tekstu**: Funkcja zlicza wystąpienia liter od `a` do `z` oraz zamienia je na częstotliwości procentowe.
2. **Porównanie z profilami językowymi**: Częstotliwości liter w tekście są porównywane z profilami języków zdefiniowanymi w strukturze `LanguageBase`.
3. **Określenie dopasowania**: Algorytm oblicza odległość euklidesową pomiędzy rozkładem liter w tekście a każdym profilem językowym, wybierając język o najmniejszej odległości.

#### Parametry:
- `char *text`: Tekst wejściowy, którego język ma zostać rozpoznany.

#### Zwracana wartość:
- `const char *`: Kod języka w formacie trzyliterowym (np. `"ENG"`, `"POL"`).
## Specyfikacja funkcji

### `char *find_longest_palindrome(const char *text)`

#### Opis:
Funkcja `find_longest_palindrome` znajduje najdłuższy palindrom w danym tekście za pomocą algorytmu Manachera, który pozwala na wydajne wyznaczanie palindromów w ciągach znaków.

#### Jak działa:
1. **Przetwarzanie tekstu**: Funkcja najpierw przetwarza tekst, dodając separatory (`#`) pomiędzy każdą literą, a także dodaje znaki krańcowe (`^` na początku i `$` na końcu). To umożliwia łatwiejsze rozszerzanie palindromów.
2. **Algorytm Manachera**: Funkcja stosuje algorytm Manachera do wykrywania palindromów w przetworzonym ciągu. Wartość `P[i]` reprezentuje promień palindromu, którego środek znajduje się w indeksie `i`.
3. **Wyszukiwanie najdłuższego palindromu**: Podczas przetwarzania tekstu funkcja śledzi środek i promień najdłuższego palindromu, a na koniec zwraca najdłuższy palindrom w oryginalnej formie (bez separatorów i znaków krańcowych).

#### Parametry:
- `const char *text`: Tekst wejściowy, w którym należy znaleźć najdłuższy palindrom.

#### Zwracana wartość:
- `char *`: Najdłuższy palindrom znaleziony w tekście. Zwracany łańcuch znaków jest zakończony znakiem `'\0'` i zawiera tylko litery z oryginalnego tekstu, bez dodatkowych separatorów czy znaków krańcowych.
