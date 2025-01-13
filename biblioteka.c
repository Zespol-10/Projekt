#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteka.h"

#define MAX_WORD_LENGHT 1000
#define MAX_TEXT_SIZE 1000000

void statystyki(const char *text, TextStats *stats) {
    for (int i = 0; i < 52; i++) stats->tablica_liter[i] = 0;
    int i = 0, dlugosc_slowa = 0, dlugosc_zdania = 0;
    stats->liczba_wyrazow = stats->liczba_akapitow = stats->liczba_cyfr = stats->liczba_znakow = stats->liczba_zdań = stats->liczba_liter = 0;
    stats->srednia_dlugosc_slowa = stats->srednia_dlugosc_zdania = stats->liczba_znakow_specjalnych = stats->zlozonosc_leksykalna = 0;
    stats->max_dlugosc_slowa = 0;
    stats->min_dlugosc_slowa = MAX_WORD_LENGHT;
    
    while (text[i] != '\0') {
        char znak = text[i];
        stats->liczba_znakow++;

        if (isalpha(znak)) {
            stats->liczba_liter++;
            dlugosc_slowa++;
            if ('a' <= znak && znak <= 'z') stats->tablica_liter[(int)znak-97]++;
            if ('A' <= znak && znak <= 'Z') stats->tablica_liter[(int)znak-65+26]++;
        }
        else if (isdigit(znak)) stats->liczba_cyfr++;
        else if (ispunct(znak)) stats->liczba_znakow_specjalnych++;

        if (isspace(znak)) {
            if (znak == '\n' && (i == 0 || text[i-1] == '\n')) stats->liczba_akapitow++;
            if (dlugosc_slowa > 0 && znak == ' ') {
                stats->liczba_wyrazow++;
                if (dlugosc_slowa > stats->max_dlugosc_slowa) stats->max_dlugosc_slowa = dlugosc_slowa;
                if (dlugosc_slowa < stats->min_dlugosc_slowa) stats->min_dlugosc_slowa = dlugosc_slowa;
                dlugosc_zdania = dlugosc_zdania + dlugosc_slowa + 1;
                dlugosc_slowa = 0;
            }
        }

        if (znak == '.' || znak == '!' || znak == '?') {
            stats->liczba_zdań++;
            stats->srednia_dlugosc_zdania += dlugosc_zdania;
            dlugosc_zdania = 0;
        }

        i++;
    }
    
    if (dlugosc_slowa > 0) {
        stats->liczba_wyrazow++;
        if (dlugosc_slowa > stats->max_dlugosc_slowa) stats->max_dlugosc_slowa = dlugosc_slowa;
        if (dlugosc_slowa < stats->min_dlugosc_slowa) stats->min_dlugosc_slowa = dlugosc_slowa;
        dlugosc_zdania = dlugosc_zdania + dlugosc_slowa + 1;
    }
        

    stats->srednia_dlugosc_slowa = (float) stats->liczba_znakow / stats->liczba_wyrazow;
    stats->srednia_dlugosc_zdania = (float) stats->srednia_dlugosc_zdania / stats->liczba_zdań;
    stats->zlozonosc_leksykalna = (float) stats->liczba_wyrazow / stats->liczba_zdań;
}

void wyszukiwanie_wzorca(const char *text, const char *pattern) {
    const char *text_copy = text;
    char buffer[MAX_TEXT_SIZE];       

    if ((pattern[0] == '.' && strlen(pattern) == 1) || (pattern[0] == '!' && strlen(pattern) == 1) || (pattern[0] == '?' && strlen(pattern) == 1) || (pattern[0] == '-' && strlen(pattern) == 1)) wyszukiwanie_znaku_specjalnego(text, pattern);

    while (strstr(text_copy, pattern) != NULL) {
        text_copy = strstr(text_copy, pattern);

        // zdanie przed patternem
        int i = 1;
        while ((text_copy - i) >= text && text_copy[-i] != '\t' && text_copy[-i] != '\n' && text_copy[-i] != '-' && text_copy[-i] != '.'  && text_copy[-i] != '!'  && text_copy[-i] != '?') {
            buffer[i-1] = text_copy[-i];
            i++;
        }
        int licznik = 1;
        while (buffer[strlen(buffer)-licznik] == ' ') licznik++;
        for (int j = strlen(buffer)-licznik; j >= 0; j--) printf("%c", buffer[j]);
        memset(buffer, 0, sizeof(buffer));

        //pattern
        printf("\033[0;31m");
        for (int j = 0; j < strlen(pattern); j++) printf("%c", text_copy[j]);
        printf("\033[0m");

        // reszta zdania
        int k = strlen(pattern);
        while (text_copy[k] != '\n' && text_copy[k] != '.'  && text_copy[k] != '!'  && text_copy[k] != '?' && text_copy[k] != '\0') {
            printf("%c", text_copy[k]);
            k++;
        }
        printf("%c", text_copy[k]);

        text_copy += strlen(pattern);
        putchar('\n');
    }
}

void wyszukiwanie_znaku_specjalnego(const char *text, const char *znak) {
    const char *text_copy = text;
    char buffer[MAX_TEXT_SIZE];

    if (znak[0] == '.' || znak[0] == '!' || znak[0] == '?') {
        while (strstr(text_copy, znak) != NULL) {
        text_copy = strstr(text_copy, znak);

        int i = 1;
        while ((text_copy - i) > text && text_copy[-i] != '\t' && text_copy[-i] != '\n' && text_copy[-i] != '.'  && text_copy[-i] != '!'  && text_copy[-i] != '?' && text_copy[-i] != '-') {
            buffer[i-1] = text_copy[-i];
            i++;
        }
        //for (int j = i-3; j >= 0; j--) printf("%c", buffer[j]);
        for (int j = strlen(buffer)-1; j >= 0; j--) printf("%c", buffer[j]);

        printf("\033[0;31m%s\033[0m\n", znak);
        text_copy++;
        }
    }

    if (znak[0] == '-') {
        while (strstr(text_copy, znak) != NULL) {
            text_copy = strstr(text_copy, znak);

            if (text_copy[-1] == '\n' || text_copy[-1] == '\t') {
                printf("\033[0;31m%s\033[0m\n", znak);
                int k = 1;
                while (text_copy[k] != '\n' && text_copy[k] != '.'  && text_copy[k] != '!'  && text_copy[k] != '?') {
                    printf("%c", text_copy[k]);
                    k++;    
                }
                printf("%c", text_copy[k]);
            }
            
            else {
                // zdanie przed patternem
                const char *pattern = znak; 
                int i = 1;
                while ((text_copy - i) > text && text_copy[-i] != '\t' && text_copy[-i] != '\n' && text_copy[-i] != '.'  && text_copy[-i] != '!'  && text_copy[-i] != '?') {
                    buffer[i-1] = text_copy[-i];
                    i++;
                }
                for (int j = i-3; j >= 0; j--) printf("%c", buffer[j]);

                //pattern
                printf("\033[0;31m");
                for (int j = 0; j < strlen(pattern); j++) printf("%c", text_copy[j]);
                printf("\033[0m");

                // reszta zdania
                int k = strlen(pattern);
                while (text_copy[k] != '\n' && text_copy[k] != '.'  && text_copy[k] != '!'  && text_copy[k] != '?' && text_copy[k] != '\0') {
                    printf("%c", text_copy[k]);
                    k++;
                }
                printf("%c", text_copy[k]);
            }

            text_copy++;
            putchar('\n');
        }
    }
}

void ignorowanie_wielkosci_liter(const char *text, const char *pattern) {

    char text_copy[strlen(text)];
    char pattern_copy[strlen(pattern)];
    if (text_copy == NULL || pattern_copy == NULL) {
        perror("Błąd alokacji pamięci");
        return;
    }

    strcpy(text_copy, text);
    strcpy(pattern_copy, pattern);
    int text_len = strlen(text), pattern_len = strlen(pattern);

    for (int i = 0; i < text_len; i++) text_copy[i] = toupper(text_copy[i]);
    for (int i = 0; i < pattern_len; i++) pattern_copy[i] = toupper(pattern_copy[i]);

    char word[pattern_len + 1];
    for (int i = 0; i < text_len - pattern_len; i++) {
        for (int j = 0; j < pattern_len; j++) word[j] = text_copy[i+j];
        word[pattern_len] = '\0';
        if (strcmp(word, pattern_copy) == 0) {
            char buffer[MAX_TEXT_SIZE];
            int licznik = -i+1;
            while ((i - licznik) >= 0 && text[-licznik] != '\t' && text[-licznik] != '\n' && text[-licznik] != '-' && text[-licznik] != '.'  && text[-licznik] != '!'  && text[-licznik] != '?') {
                buffer[i+licznik-1] = text[-licznik];
                licznik++;
            }
            int licznik2 = 1;
            while (buffer[strlen(buffer)-licznik2] == ' ') licznik2++;
            for (int j = strlen(buffer)-licznik2; j >= 0; j--) printf("%c", buffer[j]);
            memset(buffer, 0, sizeof(buffer));

            //pattern
            printf("\033[0;31m");
            for (int j = 0; j < strlen(pattern); j++) printf("%c", text[i+j]);
            printf("\033[0m");

            // reszta zdania
            int k = strlen(pattern);
            while (text[i+k] != '\n' && text[i+k] != '.'  && text[i+k] != '!'  && text[i+k] != '?' && text[i+k] != '\0') {
                printf("%c", text[i+k]);
                k++;
            }
            printf("%c", text_copy[i+k]);

            putchar('\n');
        }
        memset(word, 0, sizeof(word));
    }
}

int zliczanie_wzorca(const char *text, const char *pattern) {
    const char *text_copy = text;
    int result = 0;

    while (strstr(text_copy, pattern) != NULL) {
        result++;
        text_copy = strstr(text_copy, pattern);
        text_copy += strlen(pattern);
    }

    return result;
}

void podmiana_wzorca(const char *text, const char* pattern, const char* replacement, char* result) {
    const char *text_copy = text;         // aktualna pozycja w tekscie
    char buffer[MAX_TEXT_SIZE];     // wynikowy tekst
    char *buffer2 = buffer;         // wskaźnik

    while (strstr(text_copy, pattern) != NULL) {        // strstr to jakaś funkcja która zwraca wskaźnik na pierwsze wystąpienie pattern w text_copy
        text_copy = strstr(text_copy, pattern);         
        strncpy(buffer2, text, text_copy - text);       // w buffer2 trzymamy wszystko oprócz patternu
        buffer2 += text_copy - text;                    // przesuwamy buffer do końca
        strcpy(buffer2, replacement);                   // dodajemy do buffer2 replacement
        buffer2 += strlen(replacement);                 // przesuwamy buffer do końca
        text_copy += strlen(pattern);                   
        text = text_copy;
    }

    strcpy(buffer2, text);
    strcpy(result, buffer);
}