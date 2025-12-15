#include "../include/cub3d.h"

int	ft_strlen(char const *s)
{
	int	len = 0;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(char const *s1)
{
	char	*dup;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		len1, len2;
	int		i, j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
			c == '\f' || c == '\v');
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		start, end;
	int		len;
	int		i;

	if (!s1 || !set)
		return (NULL);
	
	// Find start
	start = 0;
	while (s1[start] && strchr(set, s1[start]))
		start++;
	
	// Find end
	end = ft_strlen(s1) - 1;
	while (end > start && strchr(set, s1[end]))
		end--;
	
	len = end - start + 1;
	trimmed = malloc(sizeof(char) * (len + 1));
	if (!trimmed)
		return (NULL);
	
	i = 0;
	while (i < len)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

static int	count_words(char const *s, char c)
{
	int	count = 0;
	int	in_word = 0;
	int	i = 0;

	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, int *index)
{
	int	start;
	int	len = 0;
	char	*word;
	int	i;

	// Skip delimiter
	while (s[*index] == c)
		(*index)++;
	
	start = *index;
	
	// Find word length
	while (s[*index] && s[*index] != c)
	{
		len++;
		(*index)++;
	}
	
	word = malloc(sizeof(char) * (len + 1));
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

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word_count;
	int		index = 0;
	int		i;

	if (!s)
		return (NULL);
	
	word_count = count_words(s, c);
	split = malloc(sizeof(char *) * (word_count + 1));
	if (!split)
		return (NULL);
	
	i = 0;
	while (i < word_count)
	{
		split[i] = get_word(s, c, &index);
		if (!split[i])
		{
			// Free allocated memory on failure
			int j = 0;
			while (j < i)
				free(split[j++]);
			free(split);
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}

int	ft_atoi(const char *str)
{
	int	result = 0;
	int	sign = 1;
	int	i = 0;

	// Skip whitespace
	while (is_whitespace(str[i]))
		i++;
	
	// Handle sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	
	// Convert digits
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	return (result * sign);
}

// Simple get_next_line implementation
char	*get_next_line(int fd)
{
	static char	buffer[1024];
	static int	buf_pos = 0;
	static int	buf_size = 0;
	char		line[1024];
	int			line_pos = 0;
	int			bytes_read;

	if (fd < 0)
		return (NULL);

	while (1)
	{
		// If buffer is empty, read more data
		if (buf_pos >= buf_size)
		{
			bytes_read = read(fd, buffer, 1024);
			if (bytes_read <= 0)
			{
				if (line_pos > 0)
				{
					line[line_pos] = '\0';
					return (ft_strdup(line));
				}
				return (NULL);
			}
			buf_size = bytes_read;
			buf_pos = 0;
		}

		// Copy character from buffer to line
		line[line_pos] = buffer[buf_pos];
		buf_pos++;

		// Check for newline
		if (line[line_pos] == '\n')
		{
			line[line_pos + 1] = '\0';
			return (ft_strdup(line));
		}

		line_pos++;
		if (line_pos >= 1023) // Prevent buffer overflow
		{
			line[line_pos] = '\0';
			return (ft_strdup(line));
		}
	}
}

void	error_exit(char *msg)
{
	printf("%s\n", msg);
}