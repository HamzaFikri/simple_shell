#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFSIZE 600
#define FREE_ADDRESSES ((void *)3)
#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof((ARRAY)[0]))
/**
 * struct buffer - structure for controlling buffer
 * @buf: pointer the buffer
 * @size: size of the buffer
 * @bp: current point in buffer to check for multiple command passes
 */
typedef struct buffer
{
	char *buf;
	unsigned int size;
	unsigned int bp;
} buffer;
/**
 * struct builtin - lookup structure for builtin functions
 * @name: string name user types to call function
 * @func: function pointer to that function
 */
typedef struct builtin
{
	char *name;
	int (*func)();
} builtin;
/**
 * struct addr_list - List for saving addresses for freeing on exit
 * @address: an address of any type
 * @next: the next node in the list
 */
typedef struct addr_list
{
	void *address;
	struct addr_list *next;
} addr_list;

/**
 * struct hist_s - history linked list for saving commands
 * @cmd: command given as input
 * @next: pointer to next node on list
 */

typedef struct hist_s
{
	char *cmd;
	struct hist_s *next;
} hist_t;

extern char **environ;
/**
 * struct env_s - structure for each environmental variable
 * @value: value of the environmental variable
 * @next: next environmental variable
 */

typedef struct env_s
{
	char *value;
	struct env_s *next;
} env_t;
/**
 * struct alias - structure for holding aliases
 * @key: key to search for when matching
 * @value: value to replace matched keys
 * @next: next node in the list
 */
typedef struct alias
{
	char *key;
	char *value;
	struct alias *next;
} alias;

typedef void (*signhandler_t)(int);
void signal_handler(int signo);

/* history.c */
void history_wrapper(char *cmd, env_t *envp, char mode);
void print_history_2(hist_t *history);

/* history_func.c*/
void create_history(hist_t *history, env_t *envp);
int read_file(env_t *envp, char **buf);
hist_t *add_history(hist_t *head, char *cmd);
void print_history(hist_t *head);
char *make_path(char **path, char *filename, char *key, env_t *envp);

/* history_func2.c*/
void add_cmdhist(hist_t *history, char *cmd);
void pop_head(hist_t *head);
int write_history(env_t *envp, hist_t *history);
char *_itoa(int num, int mode);

/* shell.c */
int more_cmds(buffer *buf, int return_value);
void trim_cmd(buffer *buf);

/* variable_expansion.c */
void variable_expansion(buffer *b, env_t *envp, int retrn_value);
char *_getpid(void);
char *_getTok(char *stat, int n);

/* run_execute.c */
int run_execute(char **arg_list, env_t *env_p, int cmd_size);
int execute_func(char *cmd, char **args, env_t *envp);

/* linked_env.c*/
env_t *create_envlist();
env_t *add_env(env_t **head, char *value);
void  remove_env(env_t **head, int index);
void update_env(env_t *envp, char *name, char *value, int buf_size);
void print_env(env_t *head);

/* helpers.c */
void print_cmdline(void);
void *safe_malloc(size_t size);
void _write_err(char *s);
void free_args(char **arg_list);
char *rm_vname(env_t *envp, char *arg, int buf_size);
char *get_env_value(env_t *envp, char *name);

/* helper2.c */
void _write(char *s);
char *update_path(char **arg_list, env_t *envp, char *path, int buf_size);
char **list_to_array(env_t *envp);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);

/* helper_str.c*/
char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strstr(char *haystack, char *needle);

/* helper_str2.c */
char *_strdup(char *str);
char *_strchr(char *s, char c);
int _strlen(char *s);
int _str_match(char *s1, char *s2);
int _str_match_tonull(char *s1, char *s2);
int _atoi(char *s);

/* helper_str3.c */
int _strstr_int(char *haystack, char *needle);
int _strpbrk_int(char *s, char *needles);
int _str_match_strict(char *s1, char *s2);
int is_alpha(char c);
int is_digit(char c);

/* helper_str4.c */
int string_match(char *s1, char *s2, char *delim);
int char_match(char c, char *needles);

/* getline.c */
int _getline(buffer *b, int fd, env_t *envp);
int _endread(char *s);
int _getline_fileread(buffer *b, env_t *envp);

/* buffer_maniputlation.c */
void buffer_reallocate(buffer *b);
void buffer_word_erase(buffer *b, int n);
void buffer_insert(buffer *b, char *s, int n);

/* hsh_alias.c */
int hsh_alias(char **argv, env_t *env_p, int mode);
char *hsh_alias_search(alias *list, char *arg);
int hsh_alias_printall(alias *list);
int hsh_alias_print(alias *list, char **argv);
int hsh_alias_add(alias *list, char **argv);

/* cd_func.c */
char *cd_path(char **arg_list, env_t *envp, int buf_size);

/* path_funcs.c */
int get_path(char *path, env_t *list);
char **tokenize_path(char **search_path, char *path, int size);
int create_path(char *cmd, char **search_path);

/* tokenize.c */
void tokenize_buf(buffer *buf, char ***av);
void _av_init(char *buf, char ***av);
void _add_null(char *buf);
int _is_whitespace(char c);
int _is_endofcmd(char c);

/* run_builtin.c */
int run_builtin(char **arg_list, env_t *env_p, int buf_size);

/* alias.c */
int alias_expansion(buffer *b, env_t *env_p);

/* memory_allocation.c */
void _free(void *address);
void defer_free(void *address);
int clear_addr_list_node(addr_list *list, void *address);
void add_addr_list_node(addr_list *list, void *address);
void free_addr_list(addr_list *list);

/* list of builtin functions */
int hsh_env(char **arg, env_t *env_p);
int hsh_setenv(char **arg, env_t *env_p, int buf_size);
int hsh_unsetenv(char **arg, env_t *env_p);
int hsh_cd(char **arg, env_t *env_p, int buf_size);
int hsh_help(char **arg);
int hsh_exit(char **arg_list, env_t *env_p, int buf_size);
int hsh_history(char **arg, env_t *env_p, int buf_size);

/* list of builtin help printouts */
int hsh_exit_help(void);
int hsh_env_help(void);
int hsh_setenv_help(void);
int hsh_unsetenv_help(void);
int hsh_cd_help(void);
int hsh_history_help(void);
int hsh_help_help(void);
int hsh_alias_help(void);
#endif
