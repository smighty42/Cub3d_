/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira < itaskira@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:34:33 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 14:50:56 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdlib.h>


char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strtrim_gc(char const *s1, char const *set, t_gc **gc)
{
	size_t	len;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len != 0 && ft_strchr(set, s1[len - 1]))
		len--;
	return (ft_substr_gc(s1, 0, len, gc));
}
