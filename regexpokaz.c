#include <stdio.h>
#include "regex.h"

int main() {
    char *expr[] = {"a*b", "a+b", "a{2,4}b", "a.c", ".*ab$", NULL};
    char *text[] = {"aab", "ab", "aaaab", "ababababb", "abababcabb", NULL};
    for(int i = 0; expr[i] != NULL; ++i){
        printf("Testowanie: %s\n", expr[i]);
        for(int j = 0; text[j] != NULL; ++j){
            printf("    Text: %s -> ", text[j]);
            if(match(expr[i], text[j])) printf("Znaleziono\n");
            else printf("Nie znaleziono.\n");
        }
        printf("\n");
    }
    return 0;
}
