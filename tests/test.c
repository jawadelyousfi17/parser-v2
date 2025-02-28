#include "../parser.h"
#include <string.h>
#include <errno.h>

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
    if (token == ARG)
        return "arg";
    if (token == PIPE)
        return "pipe";
    if (token == REDIRECT_INPUT)
        return "r input";
    if (token == REDIRECT_OUTPUT)
        return "r output";
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
        printf(GREEN " [%s] " RESET, arr[i++]);
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
int main(int ac, char **av, char **env)
{

    // atexit(__f);

    while (1)
    {
        // readline("< ");
        // printf("[%s]\n", in);
        ft_malloc(10000, 0);
            // ft_malloc(0, 1);

        // continue;
        char **splited = ft_split_commands("ls < ls > ls < ls > ks");

        
        _display_2d_array(splited);
        if (splited == NULL)
        {
            if (errno != 0)
                perror("Error");
            return 0;
        }

        t_list *tokens = _ft_lexer(splited);

        if (tokens == NULL)
        {
            perror("Lexer Error");
            return 0;
        }

        if (check_syntax(tokens))
        {
            printf(RED "\n%s\n\n" RESET, check_syntax(tokens));
            ft_malloc(0, 1);
            continue;
        }

        if (ft_expand_data(tokens) == 0)
        {
            perror("ERROR");
            return 0;
        }

        if (ft_execute_heredoc(tokens) == 0)
        {
            perror("ERROR");
            return 0;
        }

        _display_list(tokens);

        ft_malloc(0, 1);

        usleep(1000);
    }
    return 0;
}