/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:34:20 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 16:59:09 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../cub3d.h"

int		parse_texture_line(t_game *game, char *line);

int		is_valid_number(char *str);
int		is_valid_rgb_format(char *str);
int		parse_color_line(t_game *game, char *line);

int		is_texture_or_color(char *line);
int		find_map_start(char **lines);

int		parse_map_data(t_game *game, char **lines, int start);
int		parse_elements(t_game *game, char **lines);

char	**read_file_lines(char *filename, t_gc **gc);
int		check_file_ext(char *filename);
int		check_rgb_values(int r, int g, int b);
int		is_player_char(char c);
int		check_map_chars(t_game *game);
int		check_border_walls(t_game *game);
int		check_space_neighbors(t_game *game, int y, int x);
int		check_playable_cell(t_game *game, int y, int x);
int		check_enclosed_map(t_game *game);
int		find_and_init_player(t_game *game);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup_gc(const char *s1, t_gc **gc);
char	*ft_substr_gc(char const *s, unsigned int start, size_t len, t_gc **gc);
int		ft_atoi(const char *str);
char	*ft_strtrim_gc(char const *s1, char const *set, t_gc **gc);
char	**ft_split_gc(char const *s, char c, t_gc **gc);

#endif
