#include "../include/minishell.h"

int _hl_is_valid(char c)
{
    return ft_isalpha(c) || c == '_';
}

int _hl_is_valid_var(char c)
{
    return ft_isalpha(c) || c == '_';
}

char *_get_var_name(char **s)
{
    char *start = *s;

    while (**s && _hl_is_valid_var(**s))
        (*s)++;
    return ft_strndup(start, *s - start, GB);
}

char *ft_expand_vars(char *s, char **env)
{
    char qt;
    int i;
    char *var_name;
    size_t len;

    i = 0;
    qt = 0;
    while (*s)
    {
       __skip_white_spaces(&s);
       __find_quotes(&s, &qt);
       __expand__until_quotes(&s, qt);
       
        
    }
    return NULL;
}