#include <stdlib.h>
#include <stdio.h>

/* Garbage Collector Node */
typedef struct s_collect
{
    void            *content;
    struct s_collect *next;
} t_collect;

/* Clears the entire GC list and frees all allocated memory */
void lst_clear(t_collect *head)
{
    t_collect *tmp;
    while (head)
    {
        tmp = head->next;
        free(head->content);
        free(head);
        head = tmp;
    }
}

/* Returns the last node in the GC list */
t_collect *lst_last(t_collect *lst)
{
    if (!lst)
        return NULL;
    while (lst->next)
        lst = lst->next;
    return lst;
}

/* Adds a new node at the end of the GC list */
void ptr_add_back(t_collect **head, t_collect *node)
{
    if (!*head)
    {
        *head = node;
        return;
    }
    t_collect *tmp = lst_last(*head);
    tmp->next = node;
}

/* Creates a new GC node to store a pointer */
t_collect *new_node(void *ptr)
{
    t_collect *new = malloc(sizeof(t_collect));
    if (!new)
        return NULL;
    new->content = ptr;
    new->next = NULL;
    return new;
}

/*
 * ft_malloc: A malloc wrapper that tracks allocations.
 * If flag == 0, it allocates memory and adds it to the GC list.
 * If flag != 0, it frees all tracked memory and resets the GC.
 */
void *ft_malloc(size_t size, int flag)
{
    static t_collect *head = NULL;
    if (flag != 0)
    {
        lst_clear(head);
        head = NULL; // Reset the static pointer after clearing
        return NULL;
    }
    void *ptr = malloc(size);
    if (!ptr)
        return NULL;
    t_collect *node = new_node(ptr);
    if (!node)
    {
        free(ptr);
        return NULL;
    }
    ptr_add_back(&head, node);
    return ptr;
}

/* Example usage */
// int main(void)
// {
//     char *str1 = ft_malloc(50, 0);
//     if (str1)
//     {
//         snprintf(str1, 50, "Hello, Garbage Collector!");
//         printf("%s\n", str1);
//     }
    
//     int *array = ft_malloc(5 * sizeof(int), 0);
//     if (array)
//     {
//         for (int i = 0; i < 5; i++)
//             array[i] = i * 10;
//         for (int i = 0; i < 5; i++)
//             printf("%d ", array[i]);
//         printf("\n");
//     }
    
//     /* Free all tracked allocations */
//     ft_malloc(0, 1);
    
//     return 0;
// }
