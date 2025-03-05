#include "../include/minishell.h"

int hl_gb_echo(char **s, char *new_line, int i)
{
    while (s[i])
    {
        if (printf("%s", s[i]) == -1)
        {
            ft_print_error4(": echo: can't write", NULL, NULL, NULL);
            return (ft_print_error4(": echo: ", strerror(errno), NULL, NULL), 1);
        }
        if (s[i + 1])
            printf(" ");
        i++;
    }
    if (printf("%s", new_line) == -1)
    {
        ft_print_error4(": echo: can't write", NULL, NULL, NULL);
        return (ft_print_error4(": echo: ", strerror(errno), NULL, NULL), 1);
    }
    return 0;
}

int ft_echo(char **s)
{
    size_t i;
    char *new_line;

    new_line = "\n";
    i = 1;
    if (is_equal(s[i], "-n"))
    {
        i++;
        new_line = "";
    }
    return hl_gb_echo(s, new_line, i);
}
