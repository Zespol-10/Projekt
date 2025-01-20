# Projekt
Biblioteka w C/C++ zajmująca się operacjami na tekstach. 

Testowy program może zostać skompilowany i uruchomiony przy pomocy:

```bash
g++ main.cpp base64.cpp
./a.out
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
