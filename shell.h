#ifndef HEADER
#define HEADER

char **tokenize(char *, char *);
char *get_path(char **);
int forkit(char **, char **, char **, char *, int);
int exit_check(char *);
void env_check(char *, char **);
int path_check(char *);
void free_array(char **);
char *space_check(char *);
void set_path(char *temp_path, char **paths, char **tokens);
void execute(char *, char **, char **);
#endif
