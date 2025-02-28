#include "expand.h"

static int add_to_ls(t_list **head, int *i, char *s, char qt)
{
    int j;
    t_quote *quote;

    j = 0;
    while (s[*i] && s[*i] != '\'' && s[*i] != '"')
    {
        j++;
        *i = *i + 1;
    }
    char *ss = ft_substr(s, *i - j, j);
    if (j)
    {
        quote = (t_quote *)ft_malloc(sizeof(t_quote *), 0);
        if (quote == NULL)
            return 0;
        quote->is_quote = qt == 0;
        quote->string =  ft_substr(s, *i - j, j);
        if (quote->string == NULL)
            return 0;
        if (ft_lstadd_back(head, ft_lstnew(quote)) == 0)
            return 0;
    }
    return 1;
}
static int add_to_ls_2(t_list **head, int *i, char *s, char qt)
{
    int j;
    t_quote *quote;

    j = 0;
    while (s[*i] && qt != '\0' && s[*i] != qt)
    {
        j++;
        *i = *i + 1;
    }
    if (j)
    {
        quote =  (t_quote *)ft_malloc(sizeof(t_quote *), 0);
        if (quote == NULL)
            return 0;
        quote->is_quote = qt == '"' || qt == 0;
        quote->string =  ft_substr(s, *i - j, j);
        if (quote->string == NULL)
            return 0;
        if (ft_lstadd_back(head, ft_lstnew(quote)) == 0)
            return 0;
    }
    return 1;
}


t_list *ft_split_arg(char *s)
{
    int i;
    char qt;
    t_list *head;

    head = ft_lstnew(NULL);
    qt = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
            qt = s[i++];
        else if (add_to_ls(&head, &i, s, qt) == 0)
            return NULL;
        if (add_to_ls_2(&head, &i, s, qt) == 0)
            return NULL;
        if (s[i] && qt)
            i++;
        qt = 0;
    }
    return head;
}