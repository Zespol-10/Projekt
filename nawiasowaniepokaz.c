#include <stdio.h>
#include "nawiasowanie.h"
 
#define MAXLENGTH 4096

int main(){
    char s1[MAXLENGTH];
    int length = getinput(s1, MAXLENGTH);
    removecomments(s1, length, '\b');
    printf("%d\n", check(s1, length));
    printf("%s\n", s1);
    return 0;
}
