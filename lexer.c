#include "./parser.h"

int is_equal(char *s, char *p)
{
    if (ft_strlen(s) != ft_strlen(p))
        return 0;
    return ft_strncmp(s, p, ft_strlen(p)) == 0;
}

static int is_start_width(char *source, char *to_find)
{
    if (ft_strlen(to_find) >= ft_strlen(source))
        return 0;
    while (*to_find)
    {
        if (*source != *to_find)
            return 0;
        source++;
        to_find++;
    }
    return 1;
}

static int is_redirection(t_tokens token)
{
    return (token == REDIRECT_INPUT || token == REDIRECT_OUTPUT || token == APPEND || token == HERE_DOC);
}

static int is_file_limiter(t_tokens token)
{
    return (token == FILE_T || token == LIMITER);
}

static t_tokens ft_tokenize(char *s, t_tokens old_key, t_tokens old_old_key)
{
    if (is_start_width(s, "<<") || is_start_width(s, ">>"))
        return ERROR_TOKEN;
    if (is_equal(s, "<"))
        return REDIRECT_INPUT;
    if (is_equal(s, ">"))
        return REDIRECT_OUTPUT;
    if (is_equal(s, "|"))
        return PIPE;
    if (is_equal(s, ">>"))
        return APPEND;
    if (is_equal(s, "<<"))
        return HERE_DOC;
    if (old_key == FIRST)
        return COMMAND;
    if (old_key == REDIRECT_INPUT || old_key == REDIRECT_OUTPUT || old_key == APPEND)
        return FILE_T;
    if (old_old_key == APPEND || old_old_key == REDIRECT_OUTPUT || REDIRECT_INPUT == old_old_key || HERE_DOC == old_old_key || old_key == FILE_T || old_key == PIPE ||
        old_key == COMMAND)
        return COMMAND;
    if (old_key == HERE_DOC)
        return LIMITER;
    return ERROR_TOKEN;
}

static char *ft_syntax_error_join(t_tokens token)
{
    if (!is_redirection(token))
        return SYNTAX_ERR_PIPE;
    if (token == REDIRECT_INPUT)
        return SYNTAX_ERR_REDIRECTIO "`<'\n";
    if (token == REDIRECT_OUTPUT)
        return SYNTAX_ERR_REDIRECTIO "`>'\n";
    if (token == HERE_DOC)
        return SYNTAX_ERR_REDIRECTIO "`<<'\n";
    if (token == APPEND)
        return SYNTAX_ERR_REDIRECTIO "`>>'\n";
    return SYNTAX_ERR_REDIRECTIO;
}

char *check_syntax(t_list *tokens)
{
    t_list *tmp_tokens;
    t_token *token_content;
    t_token *next_content;

    tmp_tokens = tokens;
    token_content = (t_token *)tmp_tokens->content;
    if (token_content && token_content->token == PIPE)
        return SYNTAX_ERR_PIPE;
    while (tmp_tokens)
    {
        token_content = (t_token *)tmp_tokens->content;
        next_content = (t_token *)tmp_tokens->next;
        if (is_redirection(token_content->token) && tmp_tokens->next &&
            !is_file_limiter((((t_token *)tmp_tokens->next->content)->token)))
            return ft_syntax_error_join((((t_token *)tmp_tokens->next->content)->token));
        if (is_redirection(token_content->token) && tmp_tokens->next == NULL)
            return SYNTAX_ERR_NEWLINE;
        tmp_tokens = tmp_tokens->next;
    }
    return NULL;
}

static void _initialize_history(t_tokens history[2], int *i)
{
    *i = 0;
    history[0] = FIRST;
    history[1] = FIRST;
}

t_list *_ft_lexer(char **s)
{
    t_list *tokens;
    t_token *token;
    t_tokens history[2];
    int i;

    _initialize_history(history, &i);
    tokens = NULL;
    if (s == NULL)
        return NULL;
    while (s[i])
    {
        token = (t_token *)ft_malloc(sizeof(t_token *), 0);
        if (token == NULL)
            return NULL;
        token->value = ft_strdup(s[i]);
        if (token->value == NULL)
            return NULL;
        token->token = ft_tokenize(s[i++], history[0], history[1]);
        if (ft_lstadd_back(&tokens, ft_lstnew(token)) == 0)
            return NULL;
        history[1] = history[0];
        history[0] = token->token;
    }
    return tokens;
}
