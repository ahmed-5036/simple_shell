#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE__string_splitK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;



typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int error_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type; 
	int readfd;
	int line_number_history;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



int hsh(info_t *, char **);
int biult_in_find(info_t *);
void find_command(info_t *);
void command_fork(info_t *);


int cmd_exec(info_t *, char *);
char *chars_duplicate(char *, int, int);
char *find_cmd_path(info_t *, char *, char *);


int loophsh(char **);


void _str_putss_(char *);
int _char_putss_(char);
int _fd_putss_(char c, int fd);
int _inp_str_print(char *str, int fd);


int _strlen(char *);
int _str_compare(char *, char *);
char *starting_with(const char *, const char *);
char *_string_concatenates(char *, char *);


char *_string_copy(char *, char *);
char *_string_duplicate(const char *);
void _putss_(char *);
int _putcharr(char);


char *_string_copy3(char *, char *, int);
char *_string_concat(char *, char *, int);
char *_string_char_search(char *, char);


char **_string_splitw(char *, char *);
char **_string_splitw2(char *, char);


char *_memory_fill_byte(char *, char, unsigned int);
void strofstr_free(char **);
void *mem_reallocate(void *, unsigned int, unsigned int);


int free_ptr(void **);


int is_interact(info_t *);
int delimeter(char, char *);
int _alpha_char(int);
int str_int(char *);


int _string_int(char *);
void error_mes(info_t *, char *);
int decimal_print(int, int);
char *num_conv(long int, int, int);
void comment_rem(char *);


int _shell_exit(info_t *);
int _shell_cd(info_t *);
int _shell_help(info_t *);


int _listMyHistory(info_t *);
int MyAlias_builtin(info_t *);


ssize_t  input_gett(info_t *);
int _lineget(info_t *, char **, size_t *);
void sigint_Handler(int);


void infoo_clear(info_t *);
void infoo_set(info_t *, char **);
void infoo_free(info_t *, int);


char *_env_var_gett(info_t *, const char *);
int _current_env(info_t *);
int _env_var_sett(info_t *);
int _env_var_remo(info_t *);
int _env_linkedlist_populate(info_t *);


char **_env_get(info_t *);
int _env_rem_var(info_t *, char *);
int _env_set_var(info_t *, char *, char *);


char *get_history_file(info_t *info);
int history_write(info_t *info);
int history_read(info_t *info);
int history_build_(info_t *info, char *buf, int linecount);
int history_renumber(info_t *info);


list_t *node_addstart(list_t **, const char *, int);
list_t *node_addend(list_t **, const char *, int);
size_t str_list_print(const list_t *);
int node_del_index(list_t **, unsigned int);
void list_free(list_t **);


size_t length_linkedlist(const list_t *);
char **array_str_list(list_t *);
size_t linkedlist_print(const list_t *);
list_t *start_of_node(list_t *, char *, char);
ssize_t node_indx(list_t *, list_t *);

int chain(nfo_t *, char *, size_t *);
void chainchecker(info_t *, char *, size_t *, size_t, size_t);
int alias_replace(info_t *);
int vars_replace(info_t *);
int string_replace(char **, char *);

#endif
