/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:12:01 by smayti            #+#    #+#             */
/*   Updated: 2026/01/06 18:58:18 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 42

static char	*read_line(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(storage, buffer);
		free(storage);
		storage = temp;
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free(buffer);
	return (storage);
}

static char	*extract_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_storage(char *storage)
{
	char	*new_storage;
	int		i;
	int		j;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
	if (!new_storage)
		return (NULL);
	i++;
	j = 0;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}




char	*get_next_line(int fd)
{

	static char	*gnl_storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	if (!gnl_storage)
	{
		gnl_storage = malloc(1);
		if (!gnl_storage)
			return (NULL);
		gnl_storage[0] = '\0';
	}
	gnl_storage = read_line(fd, gnl_storage);
	if (!gnl_storage)
		return (NULL);
	line = extract_line(gnl_storage);
	gnl_storage = update_storage(gnl_storage);
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
