/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira < itaskira@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:47:40 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/09 13:47:57 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include "../cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 44
# endif

char	*get_next_line(int fd, t_gc **gc);
char	*ft_strchr_gnl(char *line, int c);
char	*ft_strjoin_gnl(char *line, char *buffer, t_gc **gc);
int		ft_strlen_gnl(char *s);

#endif
