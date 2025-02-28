#include "expand.h"

static char *f_ex(char *var)
{
    char *r;

    if (var == NULL)
        return NULL;
    if (*var == '?')
        r = getenv("last_exit");
    else
        r = getenv(var);
    if (r == NULL)
        return ft_strdup("");
    return ft_strdup(r);
}

static t_list *ft_expander_helper(char *s, char is_var, int *i)
{
    int start;

    if (is_var != '$')
    {
        start = *i;
        while (s[*i])
            if (s[++(*i)] == '$')
                break;
        return ft_lstnew(ft_substr(s, start, *i - start));
    }
    *i = *i + 1;
    start = *i;
    if (s[*i] == '?')
    {
        (*i)++;
        return ft_lstnew(f_ex(ft_substr(s, start, *i - start)));
    }
    while (s[*i] && ft_isalnum(s[*i]))
        *i = *i + 1;
    return ft_lstnew(f_ex(ft_substr(s, start, *i - start)));
}

static t_list *ft_expander(char *s, char **env)
{
    int i;
    int start;
    char *var;
    t_list *head;

    head = ft_lstnew(NULL);
    i = 0;
    start = 0;
    while (s[i])
    {
        if (s[i] == '$' && s[i + 1] && (ft_isalnum(s[i + 1]) || s[i + 1] == '?'))
        {
            if (ft_lstadd_back(&head, ft_expander_helper(s, '$', &i)) == 0)
                return NULL;
        }
        else
        {
            if (ft_lstadd_back(&head, ft_expander_helper(s, 0, &i)) == 0)
                return NULL;
        }
    }
    return head;
}

char *ft_expand_and_join(char *s)
{
    t_list *expanded;
    char *r;

    r = NULL;
    expanded = ft_expander(s, NULL);
    while (expanded)
    {
        if (expanded->content != NULL)
        {
            r =  ft_strjoin(r, expanded->content);
            if (r == NULL)
                return NULL;
        }
        expanded = expanded->next;
    }
    return r;
}