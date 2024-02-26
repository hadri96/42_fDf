/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:45:45 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/25 17:45:45 by hmorand          ###   ########.ch       */
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
# include <fcntl.h>
# include "keys.h"
# include "libft.h"

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
	double		zoom;
} t_map;

typedef struct	s_fdf {
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	map;
}				t_fdf;

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
void			swap_xy_map(t_map *map);

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

bool			is_steep(double slope);
bool			to_right(t_point2D a, t_point2D b);
void			swap_xy(t_point2D *a);
void			swap_points(t_point2D *a, t_point2D *b);
unsigned int	create_color(unsigned int line_color, double intensity);
// map computations

double			compute_y(int x, double slope, double intersect, double y);
double			compute_slope(t_point2D a, t_point2D b);
double			compute_intersect(t_point2D a, double slope);
void			prepare_points(t_point2D *a, t_point2D *b);

// draw

void			draw_midpoint(int x, double y, t_data img, unsigned int color);
void			draw_line_yx(t_data img, t_point2D a, t_point2D b,
					double slope);
void			draw_line_xy(t_data img, t_point2D a, t_point2D b,
					double slope);
void			draw_line_vertical(t_data img, t_point2D a, t_point2D b,
					double slope);
void			draw_line(t_data img, t_point2D a, t_point2D b);

// exceptions

void			check_swap(t_map *map, char *name);
void			correct_filename(char *name);
void			adjust_map(t_map *map, char *name);

// display

void			pixel_put(t_data *data, int x, int y, int color);

#endif
