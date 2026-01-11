/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira < itaskira@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:34:20 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 12:58:04 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../cub3d.h"

int		check_file_exists(char *path);
int		set_texture(t_game *game, char *line, char **split);
int		parse_texture_line(t_game *game, char *line);

int		is_valid_number(char *str);
int		parse_rgb(char **rgb, t_color *color);
int		is_valid_rgb_format(char *str);
int		parse_rgb_color(char *rgb_str, t_color *color, t_gc **gc);
int		parse_color_line(t_game *game, char *line);

int		check_identifier(char *line);
int		is_texture_or_color(char *line);
int		find_map_start(char **lines);
int		get_map_size(char **lines, int start, int *h, int *max_w);
int		parse_map_data(t_game *game, char **lines, int start);
int		parse_elements(t_game *game, char **lines);

int		count_lines(char *filename, t_gc **gc);
char	**alloc_lines(char *filename, int *line_count, t_gc **gc);
char	**read_file_lines(char *filename, t_gc **gc);
int		check_file_ext(char *filename);
int		check_rgb_values(int r, int g, int b);


// parser_checks.c
int		check_identifier(char *line);
int		is_texture_or_color(char *line);
int		is_valid_rgb_format(char *str);

// map_checks.c
int		is_valid_char(char c);
int		is_player_char(char c);
int		check_map_chars(t_game *game);

// map_walls.c
int		check_border_walls(t_game *game);

// map_neighbors.c
int		check_space_neighbors(t_game *game, int y, int x);
int		check_playable_cell(t_game *game, int y, int x);

// map_enclosure.c
int		check_enclosed_map(t_game *game);

// map_player.c
int		find_and_init_player(t_game *game);

// utils/utils.c
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup_gc(const char *s1, t_gc **gc);
char	*ft_substr_gc(char const *s, unsigned int start, size_t len,
			t_gc **gc);

// utils/utils2.c
char	*ft_strjoin_gc(char const *s1, char const *s2, t_gc **gc);
int		ft_atoi(const char *str);
int		is_valid_number(char *str);

// utils/string_utils.c
char	*ft_strtrim_gc(char const *s1, char const *set, t_gc **gc);

// utils/ft_split_gc.c
char	**ft_split_gc(char const *s, char c, t_gc **gc);

#endif
