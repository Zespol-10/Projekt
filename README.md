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

Dzielenie tekstu na słowa, zdania i sprawdzanie gramatyki (funkcje w podzial.c:

- void zwolnij (char **tablica, int liczba)
opis: funkcja zwalnia pamięć zarezerwowaną dla tablicy wskaźników oraz pamięć, na którą wskazują poszczególne elementy tablicy 
parametry wejściowe:
Wskaźnik na dynamicznie alokowaną tablicę wskaźników.
Liczba elementów w tablicy.

- int porownaj_slowo(const void *a, const void*b)
opis:Funkcja porównuje dwa słowa na podstawie ich długości i ustawia je w kolejności rosnącej
parametry wejściowe:
Wskaźnik na pierwszy element do porównania (wskaźnik na wskaźnik).
Wskaźnik na drugi element do porównania (wskaźnik na wskaźnik).

- char **wczytaj_slownik(const char *nazwa_pliku, int *rozmiar_slownika)
opis: wczytuje dane z pliku tekstowego, zapisuje je w dynamicznie alokowanej tablicy wskaźników na ciągi znaków oraz sortuje je używając porownaj_slowo. 
parametry wejściowe:
Wskaźnik na ciąg znaków reprezentujący nazwę pliku, z którego ma wczytać dane.
Wskaźnik na zmienną, gdzie zostanie zapisany rozmiar wczytanego słownika.

-int najlepszy_podzial(const char *tekst, char **slownik, int rozmiar_slownika, char ***wynik, int *licznik, char ** *najlepszy, int *najlepsza_liczba)
opis: służy do rekursywnego znajdowania najlepszego podziału tekstu na słowa w oparciu o dostarczoną listę słów (tutaj tylko dla języka polskiego. Funkcja wykorzystuje podejście rekurencyjne do przeszukiwania wszystkich możliwych podziałów i wybiera ten, który wykorzystuje najmniejszą liczbę słów. tekst podzielony na słowa jest przechowywany w dynamicznie alokowanej tablicy wskaźników na ciągi znaków.
Parametry wejściowe:
const char *tekst:
Ciąg znaków reprezentujący tekst do podziału.
char **slownik:
Tablica wskaźników zawierająca słowa wczytane z wcześniej zdefiniowanego słownika.
int rozmiar_slownika:
Liczba słów w słowniku.
char ***wynik:
Dynamicznie alokowana tablica wskaźników przechowująca aktualny podział tekstu na słowa.
int *licznik:
Licznik określający liczbę słów w bieżącym podziale.
char ***najlepszy:
Dynamicznie alokowana tablica wskaźników przechowująca najkrótszy podział tekstu na słowa.
int *najlepsza_liczba:
Liczba słów w najkrótszym podziale.

char **podziel_na_zdania(const char *tekst, int *liczba_zdan)
opis: dzieli tekst na pojedyncze zdania, wykorzystując określone znaki końca zdania (., !, ?). Wynikiem działania funkcji jest dynamicznie alokowana tablica wskaźników, w której każde zdanie jest przechowywane jako osobny ciąg znaków.
Parametry wejściowe:
const char *tekst:
Ciąg znaków reprezentujący tekst, który ma zostać podzielony na zdania.
Jeśli wartość jest NULL, funkcja natychmiast zwraca NULL.
int *liczba_zdan:
Wskaźnik na zmienną, do której funkcja zapisze liczbę znalezionych zdań.
Jeśli wskaźnik jest NULL, funkcja zwraca NULL.
Zwracana wartość:
Dynamicznie alokowana tablica wskaźników (char **), gdzie każdy element wskazuje na jedno zdanie.
W przypadku błędów alokacji pamięci funkcja zwraca NULL.

void polacz_wyniki_do_ciagu(char **zdania, int liczba_zdan, char **wynik, char **slownik, int rozmiar_slownika)
opis łączy zdania podzielone na słowa w jeden ciąg znaków, wykorzystując zbiór słów oraz funkcję najlepszy_podzial do podziału każdego zdania. Wynik jest przechowywany w dynamicznie alokowanej pamięci.
Parametry wejściowe
char **zdania:
Tablica wskaźników na zdania (char *), które mają zostać przetworzone i połączone w jeden ciąg znaków.
int liczba_zdan:
Liczba elementów w tablicy zdania (czyli liczba zdań).
char **wynik:
Wskaźnik na dynamicznie alokowany ciąg znaków, który będzie przechowywał połączony wynik.
char **slownik:
Tablica wskaźników zawierająca słowa wczytane ze słownika.
int rozmiar_slownika:
Liczba słów w słowniku.
Zwracana wartość
Funkcja nie zwraca wartości bezpośrednio, ale wynik działania zapisuje w dynamicznie alokowanej zmiennej *wynik.
Jeśli wystąpi błąd alokacji pamięci, funkcja nie modyfikuje *wynik.

void sprawdz_gramatyke(const char *tekst)
opis:  sprawdza podstawowe zasady gramatyki w podanym ciągu tekstowym. Weryfikuje, czy zdania zaczynają się od wielkiej litery, czy po znakach interpunkcyjnych występują odpowiednie spacje, oraz czy nie ma zbyt wielu spacji między słowami. parametr wejściowy: ciąg znaków, który ma sprawdzić. funkcja wypisuje komunikaty: jak nie ma błędów to "tekst jest gramatycznie poprawny", jeśli znajdzie błąd to napisze jaki błąd znalazła i pozycję błędu w ciągu znaków.
