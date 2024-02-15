/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:53:11 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/15 17:53:11 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>
# include <mlx.h>
# include <libft.h>

# define WIDTH   400
# define HEIGHT  400

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx_data;

typedef struct s_point2D
{
	double		x;
	double		y;
	bool		swapped;
}	t_point2D;

typedef struct s_point3D
{
	double			x;
	double			y;
	double			z;
	unsigned int	color;
}	t_point3D;

typedef struct s_map3D
{
	t_point3D	**coordinates;
	int			max_height;
	int			min_height;
	t_point3D	limits;
	bool		colors;
} t_map3D;

// parsing

t_map3D			init_map(char *filename);

// parse utils

unsigned int	ft_atoi_hex(char *str);
t_list			*parse_lines(char *filepath);

// memory utils

void			free_map(t_map3D *map);
void			free_lines(t_list *lines);
void			free_strarr(char **arr);

#endif
