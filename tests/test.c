#include "../include/minishell.h"
#include <string.h>
#include <errno.h>
#include <sys/time.h>

// Text Colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

#define STR "Hello\"de 'fef' de\"dede'dee\"dede\"dd'"

char *__trs(t_tokens token)
{
    // FIRST,
    if (token == FILE_T)
        return "file";
    if (token == COMMAND)
        return "command";
    if (token == COMMAND_J)
        return "command";
    if (token == PIPE)
        return "pipe";
    if (token == REDIRECT_INPUT)
        return "input";
    if (token == REDIRECT_OUTPUT)
        return "output";
    if (token == HERE_DOC)
        return "here doc";
    if (token == APPEND)
        return "append";
    if (token == LIMITER)
        return "limiter";
    if (token == STRING)
        return "string";
    if (token == ERROR_TOKEN)
        return "error";
    if (token == FIRST)
        return "first";
    if (token == HERE_DOC_REDIRECT)
        return "here doc redirect";
    return "not found";
}

void _display_2d_array(char **arr)
{
    if (arr == NULL)
    {
        printf(RED "No command\n" RESET);
        return;
    }

    printf(CYAN "Command: " RESET);
    for (int i = 0; arr[i]; i++)
    {
        printf(MAGENTA "[%s]" RESET, arr[i]);
        if (arr[i + 1])
            printf(YELLOW ", " RESET);
    }
    printf("\n");
}

int main(int ac, char **av, char **env)
{

    // atexit(__f);

    while (1)
    {
        struct timeval start, end;

        char *s = readline("Enter a command: ");

        t_data *data = ft_init(s);
        if (data == NULL)
        {
            ft_malloc(0, 1);
            continue;
        }

        if (data->pipe)
        {
            t_list *tmp = data->pipe_cmd;
            while (tmp)
            {
            printf(CYAN "PIPE\n" RESET);
            t_data *d = (t_data *)tmp->content;
            _display_2d_array(d->cmd);
            int i = 0;
            printf(BLUE "builtin: %s\n" RESET, d->is_builtin ? "yes" : "no");
            if (d->files == NULL)
            {
                printf(RED "No Redirections\n" RESET);
            }
            while (d->files && d->files[i])
            {
                printf(YELLOW "File_name: %-10s " RESET BLUE "Type: %s\n" RESET, d->files[i]->file, __trs(d->files[i]->type));
                i++;
            }
            tmp = tmp->next;
            printf("\n");
            }
        }
        else
        {
            printf(BLUE "builtin: %s\n" RESET, data->is_builtin ? "yes" : "no");
            _display_2d_array(data->cmd);
            int i = 0;
            if (data->files == NULL)
            {
                printf(RED "No Redirections\n" RESET);
            }
            while (data->files && data->files[i])
            {
            printf(YELLOW "File_name: %-10s " RESET BLUE "Type: %s\n" RESET, data->files[i]->file, __trs(data->files[i]->type));
            i++;
            }
        }

        ft_malloc(0, 1);
        continue;
    }
    return 0;
}