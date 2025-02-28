#include "parser.h"

int count_apparence(char c, char *s)
{
    int r;

    r = 0;
    while (*s)
    {
        if (*s == c)
            r++;
        s++;
    }
    return r;
}

static int skip_split_pipe_redirect(char **s, t_list **head)
{
    int i;
    t_list *new;

    new = NULL;
    i = 0;
    if ((*s)[i] && count_apparence((*s)[i], "|<>") != 0)
    {
        if ((*s)[i] && (*s)[i] == '>')
            while ((*s)[i] && (*s)[i] == '>')
                i++;
        else if ((*s)[i] == '<')
            while ((*s)[i] && (*s)[i] == '<')
                i++;
        else
            i++;
        if (ft_lstadd_back(head, ft_lstnew(ft_substr(*s, 0, i))) == 0)
            return 0;
        (*s) += i;
    }
    return 1;
}

static int skip_word(char **s, t_list **head)
{
    int i;
    char last;

    i = 0;
    while ((*s)[i])
    {
        last = 0;
        if ((*s)[i] == '\'' || (*s)[i] == '"')
            last = (*s)[i++];
        if (count_apparence((*s)[i], " |<>") != 0 && !last)
            break;
        while ((*s)[i] && last)
        {
            if ((*s)[i] == last)
                last = 0;
            i += last != 0;
        }
        i++;
    }
    if (i == 0)
        return 1;
    if (ft_lstadd_back(head, ft_lstnew(ft_substr(*s, 0, i))) == 0)
        return 0;
    (*s) += i;
    return 1;
}

int skip_white_spaces(char **s)
{
    int i = 0;
    while ((*s)[i] && count_apparence((*s)[i], " \t"))
        i++;
    (*s) += i;
    return 1;
}

t_list *ft_split_command(char *s, char **env)
{
    t_list *head;

    head = NULL;
    while (*s)
    {
        while (*s && count_apparence(*s, " \t") != 0)
            s++;
        if (!*s)
            break;
        if (
            !skip_split_pipe_redirect(&s, &head) ||
            !skip_white_spaces(&s) ||
            !skip_word(&s, &head) ||
            !skip_white_spaces(&s))
            return NULL;
    }
    return head;
}

char **ft_split_commands(char *s)
{
    char **result;
    int i;
    int size;
    t_list *commands;

    commands = ft_split_command(s, NULL);
    if (commands == NULL)
        return NULL;
    size = ft_lstsize(commands);
    result = (char **)ft_malloc(sizeof(char **) * (size + 1), 0);
    if (result == NULL)
        return NULL;
    i = 0;
    while (commands)
    {
        result[i] = ft_strdup((char *)commands->content);
        if (result[i++] == NULL)
            return NULL;
        commands = commands->next;
    }
    return result;
}

