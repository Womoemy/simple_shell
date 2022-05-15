#include "shell.h"

/**
 * make_env - make the shell environment from the environment passed to main
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **make_env(char **env)
{
    char **new_env;
    int i, j;

    new_env = malloc(sizeof(char *) * _strlen(env));
    if (new_env == NULL)
        return (NULL);
    for (i = 0; env[i]; i++)
    {
        new_env[i] = malloc(sizeof(char) * _strlen(env[i]));
        if (new_env[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(new_env[j]);
            free(new_env);
            return (NULL);
        }
        for (j = 0; env[i][j]; j++)
            new_env[i][j] = env[i][j];
    }
    new_env[i] = NULL;
    return (new_env);
}

/**
 * free_env - free the shell's environment
 * @env: shell's environment
 *
 * Return: void
 */
void free_env(char **env)
{
    int i;

    for (i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}