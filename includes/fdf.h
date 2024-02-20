/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:51:49 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/20 10:51:49 by hmorand          ###   ########.ch       */
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
	double			x;
	double			y;
	bool			swapped;
	unsigned int	color;
}	t_point2D;

typedef struct s_point3D
{
	double			x;
	double			y;
	double			z;
	unsigned int	color;
}	t_point3D;

typedef struct s_map
{
	t_point3D	**coord_3d;
	t_point2D	**coord_2d;
	int			max_height;
	int			min_height;
	t_point3D	limits;
	t_point2D	max;
	t_point2D	min;
	bool		colors;
} t_map;

// parsing

t_map			init_map(char *filename, double focal);

// parse utils

unsigned int	ft_atoi_hex(char *str);
t_list			*parse_lines(char *filepath);

// coordinates rotations

t_point3D		rotate_x(t_point3D point, double angle);
t_point3D		rotate_y(t_point3D point, double angle);
t_point3D		rotate_z(t_point3D point, double angle);

// map rotations

void			rotate_map_x(t_map *map, double angle);
void			rotate_map_y(t_map *map, double angle);
void			rotate_map_z(t_map *map, double angle);

// transformations in 2D

void			init_2d(t_map *map, double focal);
void			transform_2d(t_map *map, double focal);
t_point2D		isometric_view(t_point3D point);
void			transform_iso(t_map *map);

// translations

void			center_map(t_map *map);
void			translate_map(t_map *map, double offset_x, double offset_y);

// zoom

void			scale_z(t_map *map, double factor);
void			init_extremas(t_map *map);
void			extremas_2d(t_map *map);
double			optimal_zoom(t_map *map);
void			zoom_by(t_map *map, double zoom);

// memory utils

void			free_map(t_map *map);
void			free_lines(t_list *lines);
void			free_strarr(char **arr);

// display utils

double			compute_y(int x, double slope, double intersect, double y);
bool			is_steep(double slope);
bool			to_right(t_point2D a, t_point2D b);
void			swap_xy(t_point2D *a);
void			swap_points(t_point2D *a, t_point2D *b);

#endif
