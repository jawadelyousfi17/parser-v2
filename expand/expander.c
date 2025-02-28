#include "expand.h"


static char *ft_expand(char *s)
{
    t_list *splited_args;
    char *r;
    t_quote *qt;

    r = NULL;
    splited_args = ft_split_arg(s);
    while (splited_args)
    {
       qt = (t_quote *) splited_args->content;
       if (qt->is_quote)
       {
            r = ft_strjoin(r, ft_expand_and_join(qt->string));
            if (r == NULL)
                return NULL;
       } 
       else 
       {
            r = ft_strjoin(r, qt->string);
            if (r == NULL)
                return NULL;
       }
       splited_args = splited_args->next;
    }
    return r;
}


int ft_expand_data(t_list *tokens)
{
    t_token *data;

    while (tokens)
    {
        data = (t_token *)tokens->content;
        data->value = ft_expand(data->value);
        if (data->value == NULL)
            return 0;
        tokens = tokens->next;
    }
    return 1;
}