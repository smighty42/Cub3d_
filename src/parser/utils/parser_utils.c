/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:31:14 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 15:42:13 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <fcntl.h>
#include <unistd.h>

int	count_lines(char *filename, t_gc **gc)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd, gc);
		if (!line)
			break ;
		count++;
	}
	close(fd);
	return (count);
}

char	**alloc_lines(char *filename, int *line_count, t_gc **gc)
{
	char	**lines;
	int		fd;

	*line_count = count_lines(filename, gc);
	if (*line_count <= 0)
		return (NULL);
	lines = gc_malloc(gc, sizeof(char *) * (*line_count + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	return (lines);
}

char	**read_file_lines(char *filename, t_gc **gc)
{
	int		fd;
	char	*line;
	char	**lines;
	int		line_count;
	int		i;

	lines = alloc_lines(filename, &line_count, gc);
	if (!lines || line_count == 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < line_count)
	{
		line = get_next_line(fd, gc);
		if (!line)
			break ;
		lines[i] = ft_strtrim_gc(line, "\n", gc);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

int	check_file_ext(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (-1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (-1);
	return (0);
}

int	check_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (0);
}
