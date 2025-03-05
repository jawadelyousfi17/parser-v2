#include "../include/minishell.h"

char *ft_extract_var(char *s)
{
    char *r;
    int i;

    i = 0;
    while (s[i] && s[i] != '=')
        i++;
    r = ft_strndup(s, i, GB);
    return r;
}

int ft_set_env(char ***env, char *var, char *value)
{
    size_t i;
    char **tmp_env;

    (1) && (tmp_env = *env, i = 0);
    while (tmp_env[i])
    {
        if (is_equal(ft_extract_var(tmp_env[i]), var))
        {
            free(tmp_env[i]);
            tmp_env[i] = ft_strjoin(ft_strjoin(var, "=", GB), value, NO_GB);
            if (!tmp_env[i])
                return -1;
            *env = tmp_env;
            return 1;
        }
        i++;
    }
    tmp_env = (char **) ft_env_realloc((void **)*env, i, i + 2);
    if (!tmp_env)
        return -1;
    tmp_env[i] = ft_strjoin(ft_strjoin(var, "=", 0), value, NO_GB);
    if (!tmp_env[i])
        return (ft_free_env(tmp_env), -1);
    (1) && (tmp_env[i + 1] = NULL, *env = tmp_env);
    return 1;
}

