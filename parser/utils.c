#include "../include/minishell.h"


int hl_skip_white_spaces(char **s)
{
    while (**s == ' ' || **s == '\t')
        (*s)++;
    if (!**s)
        return 0;
    return 1;
}

char *ft_strndup(char *s, size_t len)
{
    char *r;
    int i;

    i = 0;
    r = ft_malloc(len + 1, 0);
    if (!r)
        return NULL;
    while (s[i] && i < len)
    {
        r[i] = s[i];
        i++;
    }
    r[i] = 0;
    return r;
}