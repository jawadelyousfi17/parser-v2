#include "parser.h"



static char *create_tmp()
{
    int i;
    char *file_path;
    char *n;

    i = 0;
    while (1)
    {
        n =  ft_itoa(i);
        if (n == NULL)
            return NULL;
        file_path = ft_strjoin("/tmp/minishel_", n);
        if (file_path == NULL)
            return NULL;
        if (file_path == NULL)
            return NULL;
        if (access(file_path, F_OK) != 0)
            return file_path;
        i++;
    }
    return (NULL);
}

static int execute_heredoc(char *file_path, char *limiter)
{
    char *tmp;
    int fd;

    fd = open(file_path, O_CREAT | O_RDWR | O_EXCL, 0644);
    if (fd < 0)
        return 0;
    while (1)
    {
        tmp =  readline("> ");
        if (!tmp)
            return (close(fd), 0);
        if (tmp && is_equal(tmp, limiter))
        {
            break;
        }
        if ( write(fd, tmp, ft_strlen(tmp)) == -1 || write(fd, "\n", 1) == -1)
            return (close(fd), 0);
    }
    close(fd);
    return 1;
}

int ft_execute_heredoc(t_list *tokens)
{
    char *file_path;
    t_token *data;

    file_path = NULL;
    while (tokens->next)
    {
        data = tokens->content;
        if (data->token == HERE_DOC)
        {
            data->token = HERE_DOC_REDIRECT;
            file_path = create_tmp();
            if (file_path == NULL)
                return 0;
            if (execute_heredoc(file_path, ((t_token *)tokens->next->content)->value) == 0)
                return (0);
            ((t_token *)tokens->next->content)->token = FILE_T;
            ((t_token *)tokens->next->content)->value = file_path;
        }
        tokens = tokens->next;
    }
    return 1;
}

