#include "../include/minishell.h"

int hl_var_len(char *s, char ***env)
{
    int size;
    char *value;

    value = gb_get_env(*env, s);
    size = ft_strlen(value);
    free(value);
    return size;
}

int hl_is_valid(char c)
{
    return ft_isalpha(c) || c == '_';
}

int hl_calcul_len(char *s, char ***env)
{
    int counter;
    char *var;

    counter = 0;
    if (s == NULL)
        return 0;
    while (*s)
    {
        if (*s == '$' && *(s + 1) && (hl_is_valid(*(s + 1)) || *(s + 1) == '?'))
        {
            char *start = ++s;
            while (*s && (ft_isalnum(*s) || *s == '_'))
                s++;
            if (*start == '?')
                s++;
            var = ft_strndup(start, s - start, 0);
            if (var == NULL)
                return -1;
            counter += hl_var_len(var, env);
            continue;
        }
        s++;
        counter++;
    }
    return counter;
}

void *hl_join(char **dest, char *var, char ***env)
{
    char *value;
    size_t len;

    if (var == NULL)
        return NULL;
    value = gb_get_env(*env, var);
    if (value == NULL)
        return *dest;
    len = ft_strlen(value);
    ft_memcpy(*dest, value, len);
    free(value);
    (*dest) += len;
    return *dest;
}

char *ft_expand(char *s, char ***env)
{
    char *expnd;
    char *current;
    char *start;
    int size;

    (1) && (size = hl_calcul_len(s, env),
            expnd = ft_malloc(sizeof(char) * (hl_calcul_len(s, env) + 1), 0), current = expnd);
    if (size == -1 || s == NULL || expnd == NULL)
        return NULL;
    while (*s)
    {
        if (*s == '$' && *(s + 1) && (hl_is_valid(*(s + 1)) || *(s + 1) == '?'))
        {
            start = ++s;
            while (*s && (ft_isalnum(*s) || *s == '_'))
                s++;
            s += *start == '?';
            if (hl_join(&expnd, ft_strndup(start, s - start, 0), env) == NULL)
                return NULL;
            continue;
        }
        *expnd++ = *s++;
    }
    *expnd = 0;
    return current;
}

char *ft_expanding(char *s, char ***env)
{
    char *r;

    if (s == NULL)
        return NULL;
    r = NULL;
    if (*s == '\'')
        r = ft_strtrim(s, "'", 0);
    else if (*s == '"')
        r = ft_strtrim(s, "\"", 0);
    else
        r = s;
    if (*s == '\'')
        return r;
    return ft_expand(r, env);
}