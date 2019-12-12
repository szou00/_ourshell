void initialize();
char ** parse_args(char *line);
char ** reading();
void execute(char **args);
char ** parse_semi(char *line);
int redirectout(char **input, int pos);
int redirectin(char **input, int pos);
void piping(char **input, int pos);
