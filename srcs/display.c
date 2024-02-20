/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:41:05 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/20 09:31:29 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

void pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		dst = data->addr + (y * data->line_length + \
x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

double compute_slope(t_point2D a, t_point2D b)
{
	double slope;

	if (b.y == a.y && a.x > b.x)
		return (INFINITY);
	else if (b.y == a.y && a.x < b.x)
		return (-INFINITY);
	slope = (b.y - a.y) / (b.x - a.x);
	return (slope);
}

double compute_intersect(t_point2D a, double slope)
{
	double intersect;

	if (slope == fabsf(INFINITY))
		return (a.x);
	intersect = a.y - (a.x * slope);
	return (intersect);
}

void prepare_points(t_point2D *a, t_point2D *b)
{
	double slope;

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
	double	intensity_high;
	double	intensity_low;

	y_floor = floor(y);
	y_frac = y - y_floor;
	intensity_high = pow(y_frac, 1/2.2);
	intensity_low = pow(1.0 - y_frac, 1/2.2);
	pixel_put(&img, x, y_floor, create_color(color, intensity_high));
	pixel_put(&img, x, y_floor + 1, create_color(color, intensity_low));
}

void draw_line(t_data img, t_point2D a, t_point2D b)
{
	unsigned int color;
	double x;
	double y;
	double intersect;
	double slope;

	color = create_color(0xFFF8332F, 1);
	prepare_points(&a, &b);
	slope = compute_slope(a, b);
	intersect = compute_intersect(a, slope);
	if (a.swapped)
	{
		x = a.x;
		while (++x < b.x)
		{
			y = compute_y(x, slope, intersect, a.y);
			draw_midpoint(y, x, img, color);
		}
	}
	else if (slope == fabsf(INFINITY))
	{
		y = a.y;
		x = a.x;
		if (slope > 0)
		{
			while (++y < b.y)
				draw_midpoint(x, y, img, color);
		}
		else
		{
			while (--y > b.y)
				draw_midpoint(x, y, img, color);
		}
	}
	else
	{
		x = a.x;
		while (++x < b.x)
		{
			y = compute_y(x, slope, intersect, a.y);
			draw_midpoint(x, y, img, color);
		}
	}
}

int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_map		map;
	int			i;
	int			j;

	map = init_map("test_maps/pylone.fdf", 1920 / 1080);
	scale_z(&map, 0.3);
	transform_iso(&map);
	zoom_by(&map, 20);
	center_map(&map);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
&img.line_length, &img.endian);
	j = -1;
	while (++j < map.limits.y)
	{
		i = -1;
		while (++i < map.limits.x)
		{
			pixel_put(&img, map.coord_2d[j][i].x, map.coord_2d[j][i].y,
			create_color(0xFFF8332F, 1));
			if (j < map.limits.y - 1)
			{
				draw_line(img, map.coord_2d[j + 1][i], map.coord_2d[j][i]);
				draw_line(img, map.coord_2d[j][i], map.coord_2d[j + 1][i]);
			}
			if (i < map.limits.x - 1)
			{
				draw_line(img, map.coord_2d[j][i], map.coord_2d[j][i + 1]);
				draw_line(img, map.coord_2d[j][i + 1], map.coord_2d[j][i]);
			}

		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
