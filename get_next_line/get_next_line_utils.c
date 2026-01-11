/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:47:31 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 15:08:07 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr_gnl(char *line, int c)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == (unsigned char)c)
			return ((char *)&line[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&line[i]);
	return (NULL);
}

char	*ft_strjoin_gnl(char *line, char *buffer, t_gc **gc)
{
	char	*str;
	int		i;
	int		j;

	if (!line)
	{
		line = gc_malloc(gc, 1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	if (!buffer)
		return (NULL);
	str = gc_malloc(gc, sizeof(char) * (ft_strlen_gnl(line)
				+ ft_strlen_gnl(buffer) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (line[++i])
		str[i] = line[i];
	j = -1;
	while (buffer[++j])
		str[i + j] = buffer[j];
	str[i + j] = '\0';
	return (str);
}
