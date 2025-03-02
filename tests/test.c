#include "../parser.h"
#include <string.h>
#include <errno.h>
#include <sys/time.h>

int is_contain_quote(char *s);

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

void _display_list(t_list *head)
{
    t_list *tmp;

    tmp = head;
    printf(BLUE "┌─────────────────────────────────┐\n" RESET);
    while (tmp)
    {
        t_token *token = (t_token *)tmp->content;
        printf(BLUE "│" GREEN "   %-15s " BLUE " %-12s" BLUE " │\n", token->value, __trs(token->token));
        tmp = tmp->next;
        if (tmp)
            printf(BLUE "├─────────────────────────────────┤\n" RESET);
    }
    printf(BLUE "└─────────────────────────────────┘\n" RESET);
}

void _display_2d_array(char **arr)
{
    int i = 0;

    printf("\n");
    if (arr == NULL)
    {
        printf(RED "No commands\n" RESET);
        return;
    }
    while (arr[i])
    {
        printf(" [%s] ", arr[i++]);
        printf(" ");
    }
    printf(" END\n\n");
}

// void _display_list_str(t_list *head)
// {
//     t_quote *qt;

//     while (head)
//     {
//         qt = (t_quote *) head->content;
//         printf("%-20s  is_quote ? %d\n", qt->string, qt->is_quote);
//         head = head->next;
//     }

// }

void __f()
{
    system("leaks a.out");
}

tt_token **ft_fast_split_command(char *s);
int ft_count_tokens(char *s);

int main(int ac, char **av, char **env)
{

    // atexit(__f);

    while (1)
    {
        struct timeval start, end;
        

        char *s = readline(">  ");

        if (s == NULL)
        {
            printf("EOF\n");
            return 0;
        }

        if (s == NULL)
        {
            ft_malloc(0, 1);
            return 0;
        }
        gettimeofday(&start, NULL);
        printf("len = %ld\n", strlen(s));

        tt_token **splited = ft_fast_split_command(s);
        if (splited == NULL)
        {
            perror("Error spliting");
            return 0;
        }

        if (ft_lexing(splited) == 0)
        {
            printf(RED "Syntax error\n");
            ft_malloc(0, 1);
            return 0;
        }

        char *err = ft_invalid_syntax(splited);
          if (err)
          {
               printf(RED "Syntax error  %s\n" RESET, err);

          }
        if (ft_join_cmd(splited) == 0)
        {
            return 0;
        }


        if (ft_execute_heredoc(splited) == 0)
        {
            perror("ERROR here doc");
            ft_malloc(0, 1);
            return 0;
        }

        t_data *data = ft_initialize_data(splited);
        if (data == NULL)
        {
            perror("ERROR init data");
        }

        if (data->pipe)
        {
            t_list *tmp = data->pipe_cmd;
            while (tmp)
            {
                t_data *d = (t_data *)tmp->content;
                _display_2d_array(d->cmd);
                int i = 0;
                while (d->files && d->files[i])
                {
                    printf("FILE = %s T = %s", d->files[i]->file, __trs(d->files[i]->type));
                    i++;
                }
                tmp = tmp->next;
            }
        } else {
            _display_2d_array(data->cmd);
            int i = 0;
            while (data->files && data->files[i])
            {
                printf("FILE = %s T = %s", data->files[i]->file, __trs(data->files[i]->type));
                i++;
            }
        }

        int i = 0;
        while (1 && splited[i])
        {
            if (splited[i]->type == NO)
            {
                i++;
                continue;
            }
            printf("   TYPE " GREEN "%s  " RESET "", __trs(splited[i]->type));
            if (splited[i]->type == COMMAND_J)
            {
                int j = 0;
                while (splited[i]->splited[j])
                {
                    printf(" [%s] ", splited[i]->splited[j++]);
                }
                printf("\n");
            }
            else
                printf("" GREEN "[%s]\n" RESET "", splited[i]->value);

            i++;
        }
        printf("\n");

        ft_malloc(0, 1);
        // free(s);
        gettimeofday(&end, NULL);

        // Calculate elapsed time in seconds and microseconds
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

        printf("Time taken: %f seconds\n", time_taken);
        // return 0;
        // usleep(20000);
        free(s);
        continue;
        0;
        0;
        // t_list *tokens = _ft_lexer(splited);
        // // return 0;

        // if (tokens == NULL)
        // {
        //     perror("Lexer Error");
        //     return 0;
        // }

        // if (check_syntax(tokens))
        // {
        //     printf(RED "\n%s\n\n" RESET, check_syntax(tokens));
        //     ft_malloc(0, 1);
        //     // continue;
        // }

        // if (ft_expand_data(tokens) == 0)
        // {
        //     perror("ERROR");
        //     return 0;
        // }

        // if (ft_execute_heredoc(tokens) == 0)
        // {
        //     perror("ERROR");
        //     return 0;
        // }

        // _display_list(tokens);

        // // ft_malloc(0, 1);
        // // usleep(1000000);
        // free(s);
    }
    return 0;
}