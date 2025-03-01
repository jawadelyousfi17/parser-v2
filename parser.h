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
	FILE_T = (1 << 0),
	COMMAND = (1 << 1),
	ARG = (1 << 2),
	PIPE = (1 << 3),
	REDIRECT_INPUT = (1 << 4),
	REDIRECT_OUTPUT = (1 << 5),
	HERE_DOC_REDIRECT = (1 << 6),
	HERE_DOC = (1 << 7),
	APPEND = (1 << 8),
	LIMITER = (1 << 9),
	STRING = (1 << 10),
	ERROR_TOKEN = (1 << 11),
	FIRST = (1 << 12),
    NO = (1 << 13),
	OPERATOR = (1 << 14),
} t_tokens;


#define VALID_AFTER_PIPE (COMMAND | REDIRECT_INPUT | REDIRECT_OUTPUT | HERE_DOC | APPEND)
#define VALID_AFTER_REDIRECTION (FILE_T)
#define VALID_AFTER_HERE_DOC (LIMITER)



typedef struct s_tokens {
    char *value;
    t_tokens token;
} t_token;


typedef enum e_token_type {
	T_OPERATOR,
	T_STRING,
} t_token_type;

typedef struct s_ttoken {
	t_tokens type;
	char *value;
	char **splited;
} tt_token;



// utils
int is_equal(char *s, char *p);
int hl_skip_white_spaces(char **s);
char *ft_strndup(char *s, size_t len);


// split commands
int ft_count_tokens(char *s);
int ft_count_quoted(char *s);

t_list *ft_split_command(char *s, char **env);
char **ft_split_commands(char *s);

// lexer
t_list *_ft_lexer(char **s);
char *check_syntax(t_list *tokens);
int ft_lexing(tt_token **tokens);

// join cmds
int ft_join_cmd(tt_token **token);

//expandeer
int ft_expand_data(t_list *tokens);
char *ft_expand(char *s);
char *ft_expanding(char *s);

// here doc
int ft_execute_heredoc(t_list *tokens);