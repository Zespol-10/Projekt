include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
enum {FALSE, TRUE};
 
int match(const char *text, const char * expr){
    while (* text != '\0'){
    if(match_pos(text, expr)) return TRUE;
    return FALSE;
    }
}
 
int match_pos(const char *text, const char * expr){
    if(expr[0] == '\0') return TRUE;
    if(expr[1] == '*') return reg_ast(expr[0], expr + 2, text);
    if(expr[1] == '+') return reg_pl(expr[0], expr + 2, text);
    if(expr[0] == '.' && expr[1] == '{') {
        int m = parse_number(&expr);
        if (*expr == ',') {
            expr++;
            int n = parse_number(&expr);
            if (*expr == '}') {
                expr++;
                return match_braces('.', m, n, expr, text);
            }
        }
    }
    if (expr[0] == '$' && expr[1] == '\0') {
        return *text == '\0';
    }
    if (*text != '\0' && (expr[0] == '.' || expr[0] == *text)) {
        return match_here(expr + 1, text + 1);
    }
    return FALSE;
}
 
void reverse(char * s){
    int i, j;
    char c;
    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) c = s[i], s[i] = s[j], s[j] = c;
}
 
void int_str(int n, char * s){
    int rem;
    short i = 0;
    while(n > 0){
        rem = n % 10;
        n -= rem;
        n /= 10;
        s[i++] = rem + '0';
    }
    s[i] = '\0';
    reverse(s);
}
 
int reg_ast(char c, const char *text, const char *expr){
    while(* text != '\0' && (* text == c || c == '.')){
        if(match_here(expr, text++)) return TRUE;
    }
    return FALSE;
}
