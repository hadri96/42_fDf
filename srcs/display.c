/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:31:04 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/15 19:56:50 by hmorand          ###   ########.ch       */
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

	slope = (b.y - a.y) / (b.x - a.x);
	return (slope);
}

double compute_intersect(t_point2D a, double slope)
{
	double intersect;

	intersect = a.y - (a.x * slope);
	return (intersect);
}

double compute_y(int x, double slope, double intersect)
{
	double y;

	y = x * slope + intersect;
	return (y);
}

bool is_steep(double slope)
{
	if (slope > 0.5 || slope < -0.5)
		return (true);
	return (false);
}

bool to_right(t_point2D a, t_point2D b)
{
	if (a.x > b.x)
		return (true);
	return (false);
}

void swap_xy(t_point2D *a)
{
	int temp;

	a->swapped = true;
	temp = a->x;
	a->x = a->y;
	a->y = temp;
}

void swap_points(t_point2D *a, t_point2D *b)
{
	t_point2D temp;

	temp = *a;
	a = b;
	b = &temp;
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
	return ((new_alpha << 24) | (line_red << 16) |
			(line_green << 8) | line_blue);
}

void draw_midpoint(int x, double y, t_data img, unsigned int color)
{
	double y_floor;

	y_floor = floor(y);
	pixel_put(&img, x, y_floor, create_color(color, 1));
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
	//pixel_put(&img, a.x, a.y, color);
	//pixel_put(&img, b.x, b.y, color);
}

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	t_point2D	a;
	t_point2D	b;
	t_point2D	c;
	t_point2D	d;

	a.x = 960 - 19 / 2 * 20;
	a.y = 540 - 10 / 2 * 20;
	b.x = 960 + 19 / 2 * 20;
	b.y = 540 + 10 / 2 * 20;
	c.x = 960 - 19 / 2 * 20;
	c.y = 540 + 10 / 2 * 20;
	d.x = 960 + 19 / 2 * 20;
	d.y = 540 - 10 / 2 * 20;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
&img.line_length, &img.endian);
	draw_line(img, a, b);
	//draw_line(img, b, d);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
