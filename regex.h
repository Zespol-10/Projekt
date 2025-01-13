int match(const char *text, const char * expr);
int reg_ast(char c, const char *text, const char *expr);
int reg_pl(char c, const char *text, const char *expr);
int reg_br(char c, int m, int n, const char *pattern, const char *text);
int is_dgt(char c);
int parse_dgt(const char *pattern);
void reverse(char * s);
void int_str(int n, char * s);
