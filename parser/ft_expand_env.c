#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/minishell.h"

void add_to_list(t_list **head, char *content)
{
    ft_lstadd_back(head, ft_lstnew(content));
}

void skip_single_quotes(char **s, t_list **head)
{
    char *tmp = *s;
    tmp++;
    while (*tmp && *tmp != '\'')
        tmp++;
    if (*tmp == '\'')
        tmp++;
    add_to_list(head, strndup(*s, tmp - *s));
    *s = tmp;
}

char *split_and_add_quotes(char *var)
{
    if (!var)
        return NULL;
    char **splited = ft_split(var, ' ');
    int i = 0;
    while (splited[i])
    {
        splited[i] = ft_strjoin("\'", splited[i], NO_GB);
        if (splited[i + 1])
         splited[i] = ft_strjoin(splited[i], "\' ", NO_GB);
        else
            splited[i] = ft_strjoin(splited[i], "\'", NO_GB);
        i++;
    }
    char *res = malloc(i + 1);
    res[0] = '\0';
    i = 0;
    while (splited[i])
    {
        strcat(res, splited[i]);
        i++;
    }
    return res;
}

void skip_variable_name(char **s, t_list **head, char **env)
{
    char *tmp = *s;
    char *start;
    tmp++;
    start = tmp;
    if ((*tmp >= 'a' && *tmp <= 'z') || (*tmp >= 'A' && *tmp <= 'Z') || *tmp == '_')
    {
        tmp++;
        while ((*tmp >= 'a' && *tmp <= 'z') || (*tmp >= 'A' && *tmp <= 'Z') || (*tmp >= '0' && *tmp <= '9') || *tmp == '_')
        {
            tmp++;
        }
    }
    char *var = gb_get_env(env, strndup(start, tmp - start));
    var = split_and_add_quotes(var);
    if (var)
    {
        add_to_list(head, var);
    } else {
        add_to_list(head, "");
    }

    *s = tmp;
}

void skip_double_quotes(char **s, t_list **head)
{
    char *tmp = *s;
    tmp++;
    while (*tmp && *tmp != '"')
        tmp++;
    if (*tmp == '"')
        tmp++;
    add_to_list(head, strndup(*s, tmp - *s));
    *s = tmp;
}

void skip_normal(char **s, t_list **head)
{
    char *tmp = *s;
    tmp++;
    while (*tmp && *tmp != '"' && *tmp != '\'' && *tmp != '$')
        tmp++;
    add_to_list(head, strndup(*s, tmp - *s));
    *s = tmp;
}

size_t calculate_total_length(t_list *head)
{
    size_t len = 0;
    t_list *tmp = head;
    while (tmp)
    {
        len += strlen(tmp->content);
        tmp = tmp->next;
    }
    return len;
}

char* concatenate_list_contents(t_list *head, size_t len)
{
    char *res = malloc(len + 1);
    res[0] = '\0'; // Initialize the result string

    while (head)
    {
        strcat(res, head->content);
        head = head->next;
    }

    return res;
}

char* replace_vars(char *s, char **env)
{
    t_list *head = NULL;

    while (*s)
    {
        if (*s == '\'')
            skip_single_quotes(&s, &head);
        if (*s == '"')
            skip_double_quotes(&s, &head);
        while (*s && *s != '"' && *s != '\'')
        {
            if (*s == '$' && *(s + 1) && (*(s + 1) >= 'a' && *(s + 1) <= 'z'))
                skip_variable_name(&s, &head, env);
            else
                skip_normal(&s, &head);
        }
    }

    size_t len = calculate_total_length(head);
    return concatenate_list_contents(head, len);
}

// int main()
// {
//     char *s = strdup("szs$var");
//     char *res = replace_vars(s);
//     printf("%s\n", res);
//     free(s);
//     free(res);
// }
