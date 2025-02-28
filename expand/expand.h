#include "../parser.h"

typedef struct s_quote {
	char *string;
	int is_quote;
} t_quote;

typedef struct s_var {
	char *value;
	int is_var;
} t_var;

t_list *ft_split_arg(char *s);
char *ft_expand_and_join(char *s);
