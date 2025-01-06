#include "nawiasowanie.c"
 
int main(){
    char s1[MAXLENGTH];
    int length = getinput(s1, MAXLENGTH);
    removecomments(s1, length, '\b');
    check(s1, length);
    printf("%s\n", s1);
    return 0;
}
