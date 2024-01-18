/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:15:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/18 13:56:31 by vivaccar         ###   ########.fr       */
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

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_fdf;

typedef struct s_map
{
	t_coords	**coords;
	int			width;
	int			heigth;
}				t_map;

t_coords	**read_file(char *file_path);
void		set_coords(t_coords **coords, char *line, int y);
t_coords	**alloc_map(char *file_path);

int			cnt_words(char *s, char c);
int			get_height(int fd);

#endif