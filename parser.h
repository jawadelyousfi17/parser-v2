#include "./libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

// ERROR MESSAGES
# define SYNTAX_ERR_NEWLINE "minishell: syntax error near unexpected token `newline'\n"
# define SYNTAX_ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define SYNTAX_ERR_REDIRECTIO "minisell: syntax error near unexpected token "


typedef enum e_tokens{
	FILE_T,
	COMMAND,
	ARG,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HERE_DOC_REDIRECT,
	HERE_DOC,
	APPEND,
	LIMITER,
	STRING,
	ERROR_TOKEN,
	FIRST,
    NO,
} t_tokens;

typedef struct s_tokens {
    char *value;
    t_tokens token;
} t_token;



// utils
int is_equal(char *s, char *p);



// split commands
t_list *ft_split_command(char *s, char **env);
char **ft_split_commands(char *s);

// lexer
t_list *_ft_lexer(char **s);
char *check_syntax(t_list *tokens);

//expandeer
int ft_expand_data(t_list *tokens);

// here doc
int ft_execute_heredoc(t_list *tokens);