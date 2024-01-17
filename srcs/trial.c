/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trial.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:18 by yourlogin         #+#    #+#             */
/*   Updated: 2024/01/15 16:38:01 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <../includes/fdf.h>
#include <mlx.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
/* # include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h> 

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point2D
{
	double		x;
	double		y;
	bool	swapped;
}	t_point2D; */

double	compute_slope(t_point2D a, t_point2D b)
{
	double	slope;

	slope = (b.y - a.y) / (b.x - a.x);
	return (slope);
}

double	compute_intersect(t_point2D a, double slope)
{
	double	intersect;

	intersect = a.y - (a.x * slope);
	return (intersect);
}

double compute_y(int x, double slope, double intersect)
{
	double y;

	y = x * slope + intersect;
	return (y);
}

bool	is_steep(double slope)
{
	if (slope > 0.5 || slope < -0.5)
		return (true);
	return (false);
}

bool	to_right(t_point2D a, t_point2D b)
{
	if (a.x > b.x)
		return (true);
	return (false);
}

void	swap_xy(t_point2D *a)
{
	int		temp;

	a->swapped = true;
	temp = a->x;
	a->x = a->y;
	a->y = temp;
}

void	swap_points(t_point2D *a, t_point2D *b)
{
	t_point2D	temp;

	temp = *a;
	a = b;
	b = &temp;
}

void	prepare_points(t_point2D *a, t_point2D *b)
{
	double	slope;

	slope = compute_slope(*a, *b);
	if (is_steep(slope))
	{
		swap_xy(a);
		swap_xy(b);
	}
	if (to_right(*a, *b))
		swap_points(a, b);
}
unsigned int create_color(unsigned int line_color, double intensity)
{
	uint8_t line_alpha;
	uint8_t new_alpha;
	uint8_t line_red;
	uint8_t line_green;
	uint8_t line_blue;

	line_alpha = (line_color >> 24) & 0xFF;
	line_red = (line_color >> 16) & 0xFF;
	line_green = (line_color >> 8) & 0xFF;
	line_blue = line_color & 0xFF;
	new_alpha = line_alpha * (1 - intensity);
	return ((new_alpha << 24) | (line_red << 16) | \
	(line_green << 8) | line_blue);
}

void	draw_midpoint(int x, double y, t_data img, unsigned int color)
{
	double	y_floor;
	double	y_frac;
	double 	intensity_high;
	double	intensity_low;
	
	y_floor = floor(y);
	y_frac = y - y_floor;
	intensity_high = pow(y_frac, 1/2.2);
	intensity_low = pow(1.0 - y_frac, 1/2.2);
	pixel_put(&img, x, y_floor, create_color(color, intensity_high));
	pixel_put(&img, x, y_floor + 1, create_color(color, intensity_low));
}

void	draw_line(t_data img, t_point2D a, t_point2D b)
{
	unsigned int	color;
	double			x;
	double			y;
	double			intersect;
	double			slope;

	color = create_color(0xFFF8332F, 1);
	prepare_points(&a, &b);
	slope = compute_slope(a, b);
	intersect = compute_intersect(a, slope);
	if (a.swapped)
	{
		x = a.y;
		while (++x != b.y)
		{
			y = compute_y(x, slope, intersect);
			draw_midpoint(y, x, img, color);
		}
	}
	else
	{
		x = a.x;
		while (++x != b.x)
		{
			y = compute_y(x, slope, intersect);
			draw_midpoint(x, y, img, color);
		}
	}
	pixel_put(&img, a.x, a.y, color);
	pixel_put(&img, b.x, b.y, color);
}

t_point2D	init_point(int x, int y)
{
	t_point2D	point;

	point.x = x;
	point.y = y;
	point.swapped = false;
	return (point);
}



int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_point2D	a;
	t_point2D	b;
	t_point2D	c;
	t_point2D	d;

	a = init_point(500, 500);
	b = init_point(620, 550);
	c = init_point(300, 200);
	d = init_point(800, 600);
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
&img.line_length, &img.endian);
	draw_line(img, a, b);
	draw_line(img, c, a);
	draw_line(img, c, d);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
