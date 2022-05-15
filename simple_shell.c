#include "shell.h"

/* global variable for ^C handling */
unsigned int sg_flag;

/**
 * sg_handler - handles ^C signal interupt
 * @uuv: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void sg_handler(int uuv)
{  
    (void)uuv;
    if (sg_flag == 0)
    {
        sg_flag = 1;
        write(STDOUT_FILENO, "\n", 1);
    }
    else
        exit(1);
    
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc, char **argv, char **environment)
{
    char *buffer;
    char **av;
    int ac;
    char **env;
    variables vars;
    builtins builtins[] = {
        {"exit", new_exit},
        {"env", environment},
        {"setenv", new_setenv},
        {"unsetenv", new_unsetenv},
        {NULL, NULL}
    };
    int i;
    int status;
    int (*builtin_func)(variables *);

    (void)argc;
    (void)argv;
    sg_flag = 0;
    signal(SIGINT, sg_handler);
    env = make_env(environment);
    vars.av = NULL;
    vars.ac = 0;
    vars.env = env;
    vars.buffer = NULL;
    vars.status = 0;
    vars.count = 0;
    vars.commands = NULL;
    vars.argv = NULL;
    while (1)
    {
        if (sg_flag == 1)
        {
            sg_flag = 0;
            write(STDOUT_FILENO, "$ ", 2);
        }
        buffer = read_line();
        if (buffer == NULL)
            exit(1);
        vars.buffer = buffer;
        vars.commands = buffer;
        vars.argv = tokenize(buffer, " \t\r\n\a");
        vars.ac = _strlen(vars.argv);
        if (vars.ac == 0)
            continue;
        for (i = 0; builtins[i].name != NULL; i++)
        {
            if (_strcmp(vars.argv[0], builtins[i].name) == 0)
            {
                builtin_func = builtins[i].func;
                status = builtin_func(&vars);
                if (status == -1)
                    exit(1);
                else if (status == 0)
                    continue;
                else
                    exit(status);
            }
        }
        if (vars.ac == 0)
            continue;
        if (vars.argv[0][0] == '.' && vars.argv[0][1] == '/')
        {
            status = execute_cwd(&vars);
            if (status == -1)
                exit(1);
            else if (status == 0)
                continue;
            else
                exit(status);
        }
        check_for_path(&vars);
        status = path_execute(vars.argv[0], &vars);
        if (status == -1)
            exit(1);
        else if (status == 0)
            continue;
        else
            exit(status);
    }
    return (0);
}

