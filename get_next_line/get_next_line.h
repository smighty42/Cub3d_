

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 44
# endif

char	*get_next_line(int fd);
char	*ft_strchr_gnl(char *line, int c);
char	*ft_strjoin_gnl(char *line, char *buffer);
int		ft_strlen_gnl(char *s);

#endif
