#include "../include/minishell.h"

void hl_close_here_docs_files(t_files **files)
{
    int i;

    i = 0;
    while (files[i])
    {
        if (files[i]->type == HERE_DOC_REDIRECT)
        {
            close(files[i]->fd);
        }
        i++;
    }
}

void ft_close_files_t_data(t_data *data)
{
    int i;
    t_data *tmp_t_data;

    i = 0;
    if (data->pipe)
    {
        while (data->pipe_cmd)
        {
            tmp_t_data = (t_data *)data->pipe_cmd->content;
            hl_close_here_docs_files((t_files **)tmp_t_data->files);
            data->pipe_cmd = data->pipe_cmd->next;
        }
        
    } else {
        hl_close_here_docs_files((t_files **)data->files);
    }
}

int ft_close_files(tt_token **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (tokens[i]->type & (HERE_DOC_REDIRECT))
        {
            if (tokens[i + 1] < 0)
            {
                i+=2;
                continue;
            }
            close(tokens[i + 1]->fd) ;
        }
        i++;
    }
    return 1;
}