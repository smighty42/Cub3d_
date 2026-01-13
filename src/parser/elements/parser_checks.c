/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:30:53 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/13 14:37:54 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	check_tex_id(char *line, int len)
{
	if (len >= 2 && ft_strncmp(line, "NO", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	if (len >= 2 && ft_strncmp(line, "SO", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	return (0);
}

static int	check_tex_id_2(char *line, int len)
{
	if (len >= 2 && ft_strncmp(line, "WE", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	if (len >= 2 && ft_strncmp(line, "EA", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	return (0);
}

int	check_identifier(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (check_tex_id(line, len) || check_tex_id_2(line, len))
		return (1);
	if (len >= 1 && line[0] == 'F')
	{
		if (len == 1 || line[1] == ' ' || line[1] == '\t')
			return (2);
	}
	if (len >= 1 && line[0] == 'C')
	{
		if (len == 1 || line[1] == ' ' || line[1] == '\t')
			return (2);
	}
	return (0);
}

int	is_valid_rgb_format(char *str)
{
	int	i;
	int	comma_count;

	if (!str || !str[0])
		return (0);
	if (str[0] == ',')
		return (0);
	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			comma_count++;
			if (str[i + 1] == ',' || str[i + 1] == '\0')
				return (0);
		}
		i++;
	}
	if (comma_count != 2)
		return (0);
	return (1);
}

int	is_texture_or_color(char *line)
{
	if (!line || !line[0])
		return (0);
	if (line[0] == ' ' || line[0] == '\t')
		return (0);
	if (line[0] == '1' || line[0] == '0')
		return (0);
	return (check_identifier(line));
}
