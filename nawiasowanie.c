#include <stdio.h>
#include "nawiasowanie.h"

#define MAXLENGTH 4096
#define COMMENT 1
#define REPLACEMENT ' '

int getinput(char line[], int max){
    int c, i;
    for(i = 0; i < max - 1 && (c = getchar()) != EOF; i++){
        line[i] = c;
    }
    line[i] = '\0';
    return i;
}

void removecomments(char code[], int length, char replacewith){
    int commentstart, state;
    commentstart = 0;
    state = !COMMENT;
    for(int i = 0; i < length; i++){
        if(code[i] == '/' && state == !COMMENT && i + 1 < length){
            if(code[++i] == '*'){
                commentstart = i - 1;
                state = COMMENT;
            }
        }
        if(code[i] == '*' && state == COMMENT && i + 1 < length){
            if(code[++i] == '/'){
                for(int j = commentstart; j <= i; j++){
                    code[j] = replacewith;
                }
                state = !COMMENT;
            }
        }
    }
}

int check(char code[], int length){
    int nparentheses, nbrackets, nbraces, nsinglequotes, ndoublequotes, state;
    nparentheses = nbrackets = nbraces = nsinglequotes = ndoublequotes = 0;
    state = !COMMENT;
    for(int i = 0; i < length; i++){
        if(code[i] == '/' && state == !COMMENT && i + 1 < length){
            if(code[++i] == '*'){
                state = COMMENT;
            }
        }
        else if(code[i] == '*' && state == COMMENT && i + 1 < length){
            if(code[++i] == '/'){
                state = !COMMENT;
            }
        }
        if(state == COMMENT){
            continue;
        }
        if(code[i] == '('){
            nparentheses++;
        }
        else if(code[i] == ')'){
            nparentheses--;
            if(nparentheses < 0){
                return 0;
            }
        }
        else if(code[i] == '['){
            nbrackets++;
        }
        else if(code[i] == ']'){
            nbrackets--;
            if(nbrackets < 0){
                return 0;
            }
        }
        else if(code[i] == '{'){
            nbraces++;
        }
        else if(code[i] == '}'){
            nbraces--;
            if(nbraces < 0){
                return 0;
            }
        }
        else if(code[i] == '\''){
            nsinglequotes = (nsinglequotes + 1) % 2;
        }
        else if(code[i] == '\"'){
            ndoublequotes = (ndoublequotes + 1) % 2;
        }
    }
    if(nparentheses == 0 && nbrackets == 0 && nbraces == 0 && nsinglequotes == 0 && ndoublequotes == 0){
        return 1;
    }
    return 0;
}
