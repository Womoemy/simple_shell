#include "shell.h"

/**
 * path_execute - executes a command in the path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 *
 * Return: 0 on succcess, 1 on failure
 */
int path_execute(char *command, variables *vars)
{ 
    pid_t child_pid;

    if (access(command, X_OK) == 0)
    {
        child_pid = fork();
        if (child_pid == 0)
        {
            execve(command, vars->av, vars->env);
            exit(1);
        }
        else if (child_pid < 0)
        {
            perror("Error: fork failed");
            return (1);
        }
        else
        {
            wait(&vars->status);
            return (0);
        }
    }
    else
    {
        perror("Error: command not found");
        return (1);
    }
}

/**
 * @find_path - finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *find_path(char **env)
{
    int i;

    for (i = 0; env[i]; i++)
    {
        if (_strncmp(env[i], "PATH=", 5) == 0)
            return (env[i] + 5);
    }
    return (NULL);
}


/**
 * check_for_path - checks if the command is in the PATH
 * @vars: variables
 *
 * Return: void
 */
void check_for_path(variables *vars)
{
    char *path, *path_dup = NULL, *check = NULL;
    unsigned int i = 0, j = 0, k = 0;
    char *path_tokens;
    struct stat buf;

    if (check_for_dir(vars->av[0]))
         return execute_cwd(vars);
    else
    {
        path = find_path(vars->env);
        if (path == NULL)
        {
            perror("Error: PATH not found");
            return;
        }
        path_dup = _strdup(path);
        path_tokens = _strtok(path_dup, ":");
        while (path_tokens != NULL)
        {
            check = _strcat(path_tokens, "/");
            check = _strcat(check, vars->av[0]);
            if (stat(check, &buf) == 0)
            {
                path_execute(check, vars);
                return;
            }
            path_tokens = _strtok(NULL, ":");
        }
        perror("Error: command not found");
    }
}
    /**
 * execute_cwd - executes the command in the current working directory
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int execute_cwd(variables *vars)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == 0)
    {
        execve(vars->av[0], vars->av, vars->env);
        exit(1);
    }
    else if (child_pid < 0)
    {
        perror("Error: fork failed");
        return (1);
    }
    else
    {
        wait(&vars->status);
        return (0);
    }
}



/**
 * check_for_dir - checks if the command is a part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int check_for_dir(char *str)
{
    unsigned int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '/')
            return (1);
    }
    return (0);
}