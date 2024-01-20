/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:15:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/20 14:45:49 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include "Libft/libft.h"

# define HEIGHT 900
# define WIDTH 1700

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct	s_coords
{
	int	z;
	int	color;
}				t_coords;

typedef struct s_map
{
	t_coords	**coords;
	int			width;
	int			heigth;
}				t_map;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map;
}				t_fdf;

// read
t_coords	**read_file(char *file_path, t_map *map);
void		set_coords(t_coords **coords, char *line, int y);
t_coords	**alloc_map(char *file_path, t_map *map);
void		ft_error(char *str);
int			cnt_words(char *s, char c);
int			get_height(int fd);

// init
t_map		*init_map();
t_fdf		*init_fdf(t_map *map);

// keyboard
int			keyup(int keycode, t_fdf *data);

// mouse
int			close_window(t_fdf *fdf);

// draw
void		my_mlx_pixel_put(t_fdf *data, int x, int y, int color);
void		draw_color(int x, int y, t_fdf *fdf, int altitude);
void		draw_line(t_point f, t_point s, t_fdf *fdf, int altitude);
t_point		get_points(int x, int y, t_fdf *fdf);
void		draw_img(t_fdf *fdf);

#endif