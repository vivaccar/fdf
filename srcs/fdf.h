/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:15:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/28 20:29:27 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "Libft/libft.h"
# include <math.h>

# define HEIGHT 1080
# define WIDTH 1900
# define K_RIGHT 0xff53
# define K_LEFT 0xff51
# define K_UP 0xff52
# define K_DOWN 0xff54
# define K_Z 0x007a
# define K_X 0x0078
# define K_N 0x006e
# define K_M 0x006d
# define K_R 0x0072
# define K_P 0x0070
# define K_I 0x0069
# define K_W 0x0077
# define K_A 0x0061
# define K_S 0x0073
# define K_D 0x0064
# define K_SPACE 0x0020

# define WHITE 0xFFFFFF
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define RED 0xFF0000

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
	double	sin;
	double	cos;
	double	gamma;
	double	alpha;
	int		view;
	int		default_color;
}			t_proj;

typedef struct s_coords
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
t_coords	**alloc_map(char *file_path);
int			get_color(char *line, t_map *map);

// utils
void		ft_error(char *str);
int			cnt_words(char *s, char c);
int			get_height(int fd);
int			get_sign(int a, int b);
int			ft_abs(int n);

//utils2
void		rotate_z(int *x, int *y, double gamma);
void		config_events(t_fdf *fdf);

// init
t_map		*init_map(void);
t_fdf		*init_fdf(t_map *map);
t_proj		*init_proj(t_fdf *fdf);
int			get_scale(int zoom);

// keyboard
void		change_color(t_fdf *fdf, int keycode);
void		rotate_img(t_fdf *fdf, int keycode);
void		zoom_img(t_fdf *fdf, int keycode);
void		reset_img(t_fdf *fdf, int keycode);
void		move_scale(t_fdf *fdf, int keycode);
void		move_img(t_fdf *fdf, int keycode);

// draw
void		my_mlx_pixel_put(t_fdf *data, int x, int y, int color);
void		draw_color(int x, int y, t_fdf *fdf, t_coords coords);
void		draw_line(t_point f, t_point s, t_fdf *fdf, t_coords coords);
t_point		get_points(int x, int y, t_fdf *fdf, t_proj *proj);
void		draw_img(t_fdf *fdf, t_proj *proj);
int			get_zoom(t_fdf *fdf);

//atoi base
char		to_lower(char c);
int			get_digit(char c, int digits_in_base);
int			ft_atoi_base(const char *str, int str_base);

// exit
int			close_window(t_fdf *fdf);
void		exit_esc(t_fdf *fdf);

//eventes
void		put_events(t_fdf *fdf);
int			keyup(int keycode, t_fdf *fdf);

#endif