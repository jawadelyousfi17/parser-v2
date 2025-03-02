#include "../libft/libft.h"
#include "parser.h"

#include <readline/readline.h>

// garbage collector struct
typedef struct s_collect
{
    void *content;
    struct s_collect *next;
} t_collect;