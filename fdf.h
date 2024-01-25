/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:15:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/25 10:15:27 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include "Libft/libft.h"
#include <math.h>

# define HEIGHT 1080
# define WIDTH 1900
# define k_right 0xff53
# define k_left 0xff51
# define k_up 0xff52
# define k_down 0xff54
# define k_z 0x007a
# define k_x 0x0078
# define k_n 0x006e
# define k_m 0x006d
# define k_r 0x0072

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct s_proj
{
	int		plus_x;
	int		plus_y;
	int		zoom;
	int		scale;
	double	alpha;
	double	beta;
	double	gama;
}			t_proj;

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
	int			default_color;
	int			high;
	int			low;
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
	t_proj		*proj;
	int			mouse;
}				t_fdf;

// read
t_coords	**read_file(char *file_path, t_map *map);
void		set_coords(t_coords **coords, char *line, int y, t_map *map);
t_coords	**alloc_map(char *file_path, t_map *map);
void		ft_error(char *str);
int			cnt_words(char *s, char c);
int			get_height(int fd);

// init
t_map		*init_map();
t_fdf		*init_fdf(t_map *map);
t_proj		*init_proj(t_fdf *fdf);

// keyboard
int			keyup(int keycode, t_fdf *data);

// mouse
int			close_window(t_fdf *fdf);
int			press_mouse(int button, int x, int y, void *param);
int			release_mouse(int button, int x, int y, void *param);

// draw
void		my_mlx_pixel_put(t_fdf *data, int x, int y, int color);
void	draw_color(int x, int y, t_fdf *fdf, t_coords coords);
void		draw_line(t_point f, t_point s, t_fdf *fdf, t_coords coords);
t_point		get_points(int x, int y, t_fdf *fdf, t_proj *proj);
void		draw_img(t_fdf *fdf, t_proj *proj);
int			get_zoom(t_fdf *fdf);

//atoi base
char		to_lower(char c);
int 		get_digit(char c, int digits_in_base);
int 		ft_atoi_base(const char *str, int str_base);

#endif