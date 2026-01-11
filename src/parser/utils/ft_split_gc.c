/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:55:43 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 15:42:30 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static size_t	ft_count_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (!s[1] || s[1] == c))
			count++;
		s++;
	}
	return (count);
}

static char	*ft_nextword(const char **s, char c, t_gc **gc)
{
	const char	*start;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	return (ft_substr_gc(start, 0, *s - start, gc));
}

char	**ft_split_gc(char const *s, char c, t_gc **gc)
{
	char	**res;
	char	**ptr;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_count_word(s, c);
	res = (char **)gc_malloc(gc, sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	ptr = res;
	while (words--)
	{
		*ptr = ft_nextword(&s, c, gc);
		if (!*ptr++)
			return (NULL);
	}
	*ptr = NULL;
	return (res);
}
