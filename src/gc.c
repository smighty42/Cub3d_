/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:52:52 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/23 13:51:59 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

static void *gc_add(t_gc **gc, void *ptr)
{
	t_gc	*new;

	if (!ptr)
		return NULL;
	new = 0;
	if (!new)
		return NULL;
	new->ptr = ptr;
	new->next = *gc;
	*gc = new;
	return (ptr);
}

void	*gc_malloc(t_gc **gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if(!gc_add(gc, ptr))
	{
		free(ptr);
		return (NULL);
	}
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
