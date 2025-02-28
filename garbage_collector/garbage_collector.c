
#include <libc.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_collect
{
    void *content;
    struct s_collect *next;
} t_collect;

t_list	*ft_lstnew(void *content);
void	display_list(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void lst_clear(t_collect *head)
{
    t_collect *tmp;
   
    while (head)
    {
        printf("Clear\n");
        tmp = head->next;
        free(head->content);
        free(head);
        head = tmp;
    }
}

t_collect *lst_last(t_collect *lst)
{
    while(lst->next)
    {
        lst = lst->next;
    }
    return (lst);
}

void ptr_add_back(t_collect **head,t_collect *node)
{
    if(!*head)
    {
        *head = node;
        return;
    }
    t_collect *tmp;
    tmp = lst_last(*head);
    tmp->next = node;
}

t_collect *new_node(void *ptr)
{
    t_collect *new;
    static int t;

    new  = malloc(sizeof(t_collect));
	if (!new)
		return (NULL);
    new->content = ptr;
    new->next = NULL;
    return(new);
}

void *ft_malloc(size_t size,int flag)
{
    static t_collect *head;
    t_collect *node;
    void *ptr;

    if (flag != 0)
    {
        lst_clear(head);
        return (NULL);
    }
    ptr = malloc(size);
    if (!ptr)
    	return (NULL);
    printf("Alloc %s\n", ptr);
    node = new_node(ptr);
    if (node == NULL)
        return (free(ptr), NULL);
    ptr_add_back(&head,node);   
    return(ptr);
} 


