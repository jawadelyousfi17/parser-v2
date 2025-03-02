#include "../include/minishell.h"

int hl_var_len(char *s)
{
    if (s == NULL)
        return 0;
    return ft_strlen(getenv(s));
}

int hl_is_valid(char c)
{
    return ft_isalpha(c) || c == '_' ;
}

int hl_calcul_len(char *s)
{
    int counter;

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
            counter += hl_var_len(ft_strndup(start, s - start));
            continue;
        }
        s++;
        counter++;
    }
    return counter;
}

void hl_join(char **dest, char *var)
{
    char *value;
    size_t len;

    if (var == NULL)
        return;
    value = getenv(var);
    if (value == NULL)
        return;
    len = ft_strlen(value);
    ft_memcpy(*dest, value, len);
    (*dest) += len;
}

char *ft_expand(char *s)
{
    char *expanded;
    char *current;
    char *start;

    expanded = ft_malloc(sizeof(char) * (hl_calcul_len(s) + 1), 0);
    if (s == NULL || expanded == NULL)
        return NULL;
    current = expanded;
    while (*s)
    {
        if (*s == '$' && *(s + 1) && (hl_is_valid(*(s + 1)) || *(s + 1) == '?'))
        {
            start = ++s;
            while (*s && (ft_isalnum(*s) || *s == '_'))
                s++;
            s += *start == '?';
            hl_join(&expanded, ft_strndup(start, s - start));
            continue;
        }
        *expanded++ = *s++;
    }
    *expanded = 0;
    return current;
}

char *ft_expanding(char *s)
{
    char *r;

    if (s == NULL)
        return NULL;
    r = NULL;
    if (*s == '\'')
        r =  ft_strtrim(s, "'");
    else if (*s == '"')
        r =  ft_strtrim(s, "\"");
    else
        r = s;
    if (*s == '\'')
        return r;
    return ft_expand(r);
}