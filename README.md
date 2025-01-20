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
g++ -std=c++17 main.cpp base64.cpp arithmetic.cpp -o main
./main base64
```

## arithmetic

Testowy program może zostać skompilowany i uruchomiony przy pomocy:

```bash
g++ -std=c++17 main.cpp base64.cpp arithmetic.cpp -o main
./main arithmetic "${FILE_PATH}"
```
## Specyfikacja klas

### `bitio::bit_istream`

#### Opis:
Bazowa klasa pomocnicza reprezentująca strumień wejściowy z operacjami na bitach.

#### Funkcje:
- `bool get_bit()`: zwraca pojedynczy bit ze strumienia.
- `bool eof()`: zwraca informację czy wszystkie bit zostały przeczytane ze strumienia.

#### Implementacje:
- `bitio::bit_ifstream` wykorzystuje `std::ifstream`.
- `bitio::bit_string_istream` wykorzystuje `std::string`.

### `bitio::bit_ostream`

#### Opis:
Bazowa klasa pomocnicza reprezentująca strumień wyjściowy z operacjami na bitach.

#### Funkcje:
- `void put_bit(bool bit)`: dodaje pojedynczy bit do strumienia.
- `void flush()`: dopełnia niedokończony bajt zerami i zapisuje strumienia.

#### Implementacje:
- `bitio::bit_ofstream` wykorzystuje `std::ofstream`.
    Posiada dodatkową funkcję `void close()` zamykającą strumień.
- `bitio::bit_string_ostream` wykorzystuje `std::string`.
    Posiada dodatkową funkcję `std::string result()` zwracającą wewnętrzny napis.

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


### `void szyfruj()`

#### Opis:

Funkcja  `szyfruj` pobiera ze standardowego wejścia dwa argumenty od użytkownika  
	- tekst do zaszyfrowania – niepusty ciąg znaków ASCII  
	- głębokość szyfru – dodatnia liczba naturalna   
   
Funkcja sprawdza poprawność wejścia, w przypadku podania nieprawidłowego wyświetla komunikat i ponownie oczekuje na wejście.
Gdy otrzyma oba parametry, umieszcza litery w odpowiednich dla nich rzędach i na koniec wypisuje na standardowe wyjście zaszyfrowany tekst.

#### Parametry i zwracana wartość
Funkcja nie przyjmuje żadnych parametrów, ani nic nie zwraca

### `char* readString()`

#### Opis:

Jest to funkcja pomocnicza, która zapisuje podane przez użytkownika argumenty jako ciągi znaków.
Funkcja alokuje dynamicznie tablicę i dopóki użytkownik nie zakończy wpisywania klawiszem ENTER, zapisuje w niej podane znaki.


#### Parametry i zwracana wartość
Funkcja nie przyjmuje żadnych argumentów
  
Zwraca `char *` - ciąg znaków w której zapisane są dane podane ze standardowego wejścia przez użytkownika.

### `std::string base64::encode1421(const std::string_view input)`

#### Opis:
Funkcja `encode1421` koduje podany tekst (`input`) przy pomocy *base64*, wykorzystując specyfikację z RFC 1421.
Istnieją analogiczne funkcje dla następujących RFC: 2045, 2152, 3501, 4648.4 (4648_4), 4648.5 (4648_5), 4880.

#### Parametry:
- `const std::string_view input`: Tekst wejściowy, który zostanie zakodowany.

#### Zwracana wartość:
- `std::string`: Nowy napis zawierający zakodowany tekst.

### `std::optional<std::string> base64::decode1421(const std::string_view input)`

#### Opis:
Funkcja `encode1421` dekoduje podany tekst (`input`) przy pomocy *base64*, wykorzystując specyfikację z RFC 1421.
Istnieją analogiczne funkcje dla następujących RFC: 2045, 2152, 3501, 4648.4 (4648_4), 4648.5 (4648_5), 4880.

#### Parametry:
- `const std::string_view input`: Tekst wejściowy, który zostanie zdekodowany.

#### Zwracana wartość:
- `std::string`: Nowy napis zawierający zdekodowany tekst lub brak wartości w przypadku błędu dekodowania.

### `void arithmetic::compress(std::istream &input, bitio::bit_ostream &output)`

#### Opis:
Funkcja kompresuje strumień `input` przy pomocy adaptacyjnego kodowania arytmetycznego do strumienia `output`.

#### Parametry:
- `std::istream &input`: Strumień wejściowy, zawierający tekst do skompresowania.
- `bitio::bit_ostream &output`: Bitowy strumień wyjściowy, do którego zostaną zapisane skompresowane dane.

### `void arithmetic::compress(bitio::bit_istream &input, std::ostream &output)`

#### Opis:
Funkcja dekompresuje strumień `input` przy pomocy adaptacyjnego kodowania arytmetycznego do strumienia `output`.

#### Parametry:
- `bitio::bit_istream &input`: Bitowy strumień wejściowy, zawierający skompresowany tekst.
- `std::ostream &output`: Strumień wyjściowy, do którego zostaną zapisane zdekompresowane dane.
