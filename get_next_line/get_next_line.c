/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira < itaskira@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:47:36 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/09 13:48:11 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*read_line(char *line, int fd, t_gc **gc)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = gc_malloc(gc, (BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr_gnl(line, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
			return (NULL);
		buffer[bytes] = '\0';
		line = ft_strjoin_gnl(line, buffer, gc);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*new_line(char *line, t_gc **gc)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		str = (char *)gc_malloc(gc, sizeof(char) * (i + 2));
	else
		str = (char *)gc_malloc(gc, sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*update_buffer(char *line, t_gc **gc)
{
	char	*str;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	str = gc_malloc(gc, sizeof(char) * (ft_strlen_gnl(line) - i) + 1);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	return (str);
}

char	*get_next_line(int fd, t_gc **gc)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(line, fd, gc);
	if (!line)
		return (NULL);
	next_line = new_line(line, gc);
	line = update_buffer(line, gc);
	return (next_line);
}
