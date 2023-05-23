#ifndef SHELL_H
#define SHELL_H

/*libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

/*string_handlers*/
char *_strdup(char *str);
char *_strchr(char *str, int chr);
int _strlen(const char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *first, const char *second, int n);

/*command_handler*/
char *_getpath(void);
char **token_maker(char *str);
void exec_cmd(char *c, char **cmd);
char *pathappend(char *path, char *cmd);
char *try_paths(char **p, char *cmd);

/*built-ins*/
void env_builtin(void);
void exiter(char **cmd, char *b);
int is_builtin(char **cmd, char *b);
void prompt_printer(void);
void sighandle(int n);

/*helper function*/
int check_type(char **cmd, char *b);
void free_cmds(char **m);




/*environment variables*/
extern __sighandler_t signal(int __sig, __sighandler_t __handler);
extern char **environ;

/**
 * struct builtins - Handles builtins
 * @env: First member
 * @exit: Second member
 *
 * Description: builtin commands
 */
struct builtins
{
	char *env;
	char *exit;

} builtins;



/**
 * struct info - Status info struct
 * @final_exit: First member
 * @ln_count: Second member
 *
 * Description: Used in error handling
 */
struct info
{
	int final_exit;
	int ln_count;
} info;


/**
 * struct flags - Holds flags
 * @interactive: First member
 *
 * Description: used to handle
 * boolean switches
 */
struct flags
{
	bool interactive;
} flags;


#endif
