/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:08:53 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/08 14:08:55 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdlib.h>

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*extract_word(char const *s, char c, int *index, t_gc **gc)
{
	char	*word;
	int		start;
	int		len;
	int		i;

	while (s[*index] && s[*index] == c)
		(*index)++;
	start = *index;
	len = 0;
	while (s[*index] && s[*index] != c)
	{
		len++;
		(*index)++;
	}
	word = gc_malloc(gc, sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill_result(char const *s, char c, char **result, int words, t_gc **gc)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < words)
	{
		result[i] = extract_word(s, c, &index, gc);
		if (!result[i])
			return (NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split_gc(char const *s, char c, t_gc **gc)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = gc_malloc(gc, sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	return (fill_result(s, c, result, words, gc));
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	return (fill_result(s, c, result, words, NULL));
}

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_gc(char const *s1, char const *set, t_gc **gc)
{
	char	*trimmed;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && is_in_set(s1[end], set))
		end--;
	trimmed = gc_malloc(gc, sizeof(char) * (end - start + 2));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trimmed[i] = s1[start];
		i++;
		start++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && is_in_set(s1[end], set))
		end--;
	trimmed = malloc(sizeof(char) * (end - start + 2));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trimmed[i] = s1[start];
		i++;
		start++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
