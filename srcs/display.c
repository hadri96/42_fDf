/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:21:13 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/16 11:21:24 by hmorand          ###   ########.ch       */
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

double compute_y(int x, double slope, double intersect, double y)
{
	double new_y;

	if (slope == INFINITY)
		return (y + 1);
	else if (slope == -INFINITY)
		return (y + 1);
	new_y = x * slope + intersect;
	return (new_y);
}

bool is_steep(double slope)
{
	if (slope == INFINITY || slope == -INFINITY)
		return (false);
	if (slope > 1 || slope < -1)
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
	pixel_put(&img, x, (int)y_floor, create_color(color, 1));
	//printf("(%d, %d)", x, (int) y_floor);
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
	printf("a: (%f, %f)\n", a.x, a.y);
	printf("b: (%f, %f)\n", b.x, b.y);
	printf("Swapped: %d\n", (int)a.swapped);
	if (a.swapped)
	{
		x = a.y;
		while ((int) ++x != (int) b.y)
		{
			y = compute_y(x, slope, intersect, a.x);
			draw_midpoint(x, (int)y, img, color);
		}
	}
	else if (slope == fabsf(INFINITY))
	{
		y = a.y;
		x = a.x;
		if (slope > 0)
		{
			while (++y < b.y)
				draw_midpoint((int)x, y, img, color);
		}
		else
		{
			while (--y > b.y)
				draw_midpoint((int)x, y, img, color);
		}
	}
	else
	{
		x = a.x;
		while ((int) ++x != (int)b.x)
		{
			y = compute_y(x, slope, intersect, a.y);
			draw_midpoint((int) x, y, img, color);
		}
	}
	pixel_put(&img, (int)a.x, (int) a.y, color);
	pixel_put(&img, (int)b.x, (int) b.y, color);
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
	t_map3D		map;

	map = init_map("test_maps/42.fdf");
	a.x = 960 - map.limits.x * 20;
	a.y = 540 - map.limits.y * 20;
	b.x = 960 + map.limits.x * 20;
	b.y = 540 + map.limits.y * 20;
	c.x = 960 - map.limits.x * 20;
	c.y = 540 + map.limits.y * 20;
	d.x = 960 + map.limits.x * 20;
	d.y = 540 - map.limits.y * 20;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
&img.line_length, &img.endian);
	draw_line(img, a, b);
	draw_line(img, a, c);
	draw_line(img, a, d);
	draw_line(img, d, b);
	draw_line(img, c, b);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
