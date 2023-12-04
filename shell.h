#ifndef HEADER
#define HEADER

char **tokenize(char *, char *);
char *get_path(char **);
void forkit(char **, char **);
int exit_check(char *);
void free_array(char **);
char *space_check(char *);

#endif