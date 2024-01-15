/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:15:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/15 11:40:56 by vivaccar         ###   ########.fr       */
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

typedef	struct s_maps
{
	int	x;
	int	y;
	int	z;
}			t_map;

typedef struct t_data
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		lines;
	int		rows;
}			t_data;

t_map		**read_map(t_data *fdf, char *file_path);
void		set_map(t_map **map, char *line, int y);
t_map		**alloc_map(char *file_path, t_data *fdf);
int			cnt_words(char *s, char c);
int			get_height(int fd);

#endif