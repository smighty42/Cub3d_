#include <stdlib.h>
#include "../cub3d.h"

void	gc_add(t_gc **gc, void *ptr)
{
	t_gc	*new;

	if (!ptr)
		return ;
	new = malloc(sizeof(t_gc));
	if (!new)
		return ;
	new->ptr = ptr;
	new->next = *gc;
	*gc = new;
}

void	*gc_malloc(t_gc **gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(gc, ptr);
	return (ptr);
}

void	gc_free_all(t_gc **gc)
{
	t_gc	*tmp;

	while (*gc)
	{
		tmp = (*gc)->next;
		free((*gc)->ptr);
		free(*gc);
		*gc = tmp;
	}
}
