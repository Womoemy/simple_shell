#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h> // for FILE
#include <stdlib.h> // for malloc
#include <string.h> // for strlen
#include <unistd.h> // for execvp
#include <sys/wait.h> // for wait
#include <sys/types.h> // for pid_t
#include <sys/stat.h> // for stat
#include <fcntl.h> // for open
#include <signal.h> // for signal
#include <errno.h> // for errno
#include <sys/ioctl.h> // for ioctl
#include <termios.h> // for tcsetattr


/**
  * structure variables -variables
  * @av: command line arguments
  * @ac: number of arguments
  * @env: environment variables
  * @buffer: buffer to command line
  * @status: exit status command
  * @count: number of arguments
  * @commands: commands to execute
  * @argv: arguments to execute at opening of shell
 * 
 */
 typedef struct variables{
  char **av;
  int ac;
  char **env;
  char *buffer;
  int status;
  int count;
  char *commands;
  char **argv;
    }variables;

 typedef struct builtins{
  char *name;
  int (*func)(variables *);
    }builtins;

    char **make_env(char **env);
    void free_env(char **env);

    ssize_t _puts(char *str);
    char *_strdup(char *strtodup);
    int _strcmp(char *s1, char *s2);
    char *_strcat(char *strss1, char *strss2);
    unsigned int _strlen(char *str);

    char **tokenize(char *buffer, char *delimeter);
    char **_realloc(char **arr, size_t *size);
    char *new_strtok(char *str, const char *delim);

    void (*builtin_func(vars_t *vars))(vars_t *vars);
    void new_exit(vars_t *vars);
    void environment(vars_t *vars);
    void new_setenv(vars_t *vars);
    void new_unsetenv(vars_t *vars);

    void add_key(vars_t *vars); 
    char **find_key(char **environment, char *key);
    char *add_value(char *key, char *value);
    int _atoi(char *str);

    void check_for_path(vars_t *vars);
    int path_execute(char *command, vars_t *vars);
    char *find_path(char **env);
    int execute_cwd(vars_t *vars);
    int check_for_dir(char *str);

    void print_error(vars_t *vars, char *msg);
    void _puts2(char *str);
    char *_uitoa(unsigned int count);

    #endif /* __SHELL_H__ */
