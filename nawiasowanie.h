int getinput(char line[], int max);
 
/* funkcja usuwająca komentarze w stylu języka C z tekstu */
void removecomments(char code[], int length, char replacewith);
 
/* sprawdzanie poprawności nawiasowania oraz cudzysłowów, jeśli użytkownik użyje w tekście komentarza tak, jak w C, fragment jest ignorowany */
int check(char code[], int length);
