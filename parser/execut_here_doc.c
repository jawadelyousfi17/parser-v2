#include "../include/minishell.h"

static char *create_tmp()
{
    int i;
    char *file_path;
    char *n;

    i = 0;
    while (1)
    {
        n = ft_itoa(i);
        if (n == NULL)
            return NULL;
        file_path = ft_strjoin("/tmp/minishel_", n, 0);
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
        return fd;
    while (1)
    {
        tmp = readline("> ");
        if (!tmp)
            return ( unlink(file_path), -2);
        if (tmp && is_equal(tmp, limiter))
        {
            free(tmp);
            break;
        }
        if (write(fd, tmp, ft_strlen(tmp)) == -1 || write(fd, "\n", 1) == -1)
            return ( free(tmp), unlink(file_path), -2);
        free(tmp);
    }
    close(fd);
    fd = open(file_path, O_RDONLY);
    if (unlink(file_path) == -1)
        return -1;
    return fd;
}

int ft_execute_heredoc(tt_token **tokens)
{
    char *file_path;
    t_token *data;
    int i;
    int fd;

    i = 0;
    file_path = NULL;
    while (tokens[i])
    {
        if (tokens[i]->type == HERE_DOC)
        {
            tokens[i]->type = HERE_DOC_REDIRECT;
            file_path = create_tmp();
            if (file_path == NULL)
                return 0;
            fd = execute_heredoc(file_path, tokens[i + 1]->value);
            if (fd < 0)
                return 0;
            tokens[++i]->type = FILE_T;
            tokens[i]->fd = fd;
            tokens[i]->value = file_path;
        }
        i++;
    }
    return 1;
}
