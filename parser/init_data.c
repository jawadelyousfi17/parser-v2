#include "../include/minishell.h"

int ft_is_builtin(char *s)
{
    if (s == NULL)
        return 0;
    return is_equal(s, "echo") || is_equal(s, "cd") || is_equal(s, "pwd") || is_equal(s, "export") || is_equal(s, "unset") || is_equal(s, "env") || is_equal(s, "exit");
}

int hl_is_pipe(tt_token **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (tokens[i]->type == PIPE)
            return 1;
        i++;
    }
    return 0;
}

char **hl_get_cmd(tt_token **tokens, int start, int pos)
{
    if (pos == -2)
        return NULL;
    if (pos != UNDIFINED)
        return tokens[pos]->splited;
    while (tokens[start] && tokens[start]->type != PIPE)
    {
        if (tokens[start]->type == COMMAND_J)
            return tokens[start]->splited;
        start++;
    }
    return NULL;
}

int hl_count_files(tt_token **tokens, int start)
{
    int count;

    count = 0;
    while (tokens[start] && tokens[start]->type != PIPE)
    {
        if (tokens[start]->type & (REDIRECT_INPUT | REDIRECT_OUTPUT | APPEND | HERE_DOC_REDIRECT))
            count++;
        start++;
    }
    return count;
}

t_files **hl_get_files(tt_token **tokens, int start, int count)
{
    t_files **files;
    int i;

    i = 0;
    if (count == UNDIFINED)
        count = hl_count_files(tokens, start);
    if (count == 0)
        return NULL;
    files = ft_malloc(sizeof(t_files *) * (count + 1), 0);
    if (files == NULL)
        return (void *)ERR_MALLOC;
    while (tokens[start] && tokens[start]->type != PIPE)
    {
        if (tokens[start]->type & (REDIRECT_INPUT | REDIRECT_OUTPUT | APPEND | HERE_DOC_REDIRECT))
        {
            files[i] = ft_malloc(sizeof(t_files), 0);
            if (files[i] == NULL)
                return (void *)ERR_MALLOC;
            files[i]->type = tokens[start++]->type;
            files[i++]->file = tokens[start]->value;
        }
        start++;
    }
    files[i] = NULL;
    return files;
}

t_data *hl_init_data(tt_token **tokens, int start, int pos, int count)
{
    t_data *data;

    data = ft_malloc(sizeof(t_data), 0);
    if (data == NULL)
        return NULL;
    data->cmd = hl_get_cmd(tokens, start, pos);
    data->is_builtin = 0;
    if (data->cmd != NULL)
        data->is_builtin = ft_is_builtin(data->cmd[0]);
    data->files = hl_get_files(tokens, start, count);
    if (data->files == (void *)ERR_MALLOC)
        return NULL;
    if (count == UNDIFINED)
        data->pipe = 0;
    else
        data->pipe = 1;
    return data;
}

t_list *ft_lst_add(t_list *current, t_list *new)
{
    if (current == NULL || new == NULL)
        return NULL;
    current->next = new;
    return new;
}

t_list *hl_create_pipe_list(tt_token **tokens)
{
    t_list *pipes;
    t_list *current;
    tt_token **start;
    int count;

    (1) && (pipes = NULL, current = NULL);
    while (*tokens)
    {
        (1) && (count = 0, start = tokens);
        while (*tokens && (*tokens)->type != PIPE)
            count += ((*tokens++)->type & (REDIRECT_INPUT | REDIRECT_OUTPUT | APPEND | HERE_DOC_REDIRECT)) != 0;
        if (pipes == NULL)
        {
            pipes = ft_lstnew(hl_init_data(start, 0, UNDIFINED, count));
            if (pipes == NULL)
                return NULL;
        }
        else
        {
            current = ft_lst_add(current, ft_lstnew(hl_init_data(start, 0, UNDIFINED, count)));
            if (current == NULL)
                return NULL;
        }
        if (current == NULL)
            current = pipes;
        if (*tokens)
            tokens++;
    }
    return pipes;
}

t_data *ft_initialize_data(tt_token **tokens)
{
    t_data *data;

    if (hl_is_pipe(tokens) == 0)
        return hl_init_data(tokens, 0, UNDIFINED, UNDIFINED);
    data = ft_malloc(sizeof(t_data), 0);
    if (data == NULL)
        return NULL;
    data->pipe = 1;
    data->pipe_cmd = hl_create_pipe_list(tokens);
    if (data->pipe_cmd == NULL)
        return NULL;
    return data;
}
