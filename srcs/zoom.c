/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:42 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/19 13:14:30 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

void	scale_z(t_map *map, double factor)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
			map->coord_3d[j][i].z *= factor;
	}
}

void	init_extremas(t_map *map)
{
	map->max.x = map->coord_2d[0][0].x;
	map->min.x = map->coord_2d[0][0].x;
	map->max.y = map->coord_2d[0][0].y;
	map->min.y = map->coord_2d[0][0].y;
}

void	extremas_2d(t_map *map)
{
	int		i;
	int		j;

	init_extremas(map);
	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
		{
			if (map->coord_2d[j][i].x < map->min.x)
				map->min.x = map->coord_2d[j][i].x;
			if (map->coord_2d[j][i].x > map->max.x)
				map->max.x = map->coord_2d[j][i].x;
			if (map->coord_2d[j][i].y < map->min.y)
				map->min.y = map->coord_2d[j][i].y;
			if (map->coord_2d[j][i].y > map->max.y)
				map->max.y = map->coord_2d[j][i].y;
		}
	}
}

double	optimal_zoom(t_map *map)
{
	double	zoom;
	double	span_x;
	double	span_y;

	extremas_2d(map);
	span_x = map->max.x - map->min.x;
	span_y = map->max.y - map->min.y;
	if (1920 / span_x < 1080 / span_y)
		zoom = (1920 / span_x) - 20;
	else
		zoom = (1080 / span_y) - 20;
	return (zoom);
}


void	zoom_by(t_map *map, double zoom)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
		{
			map->coord_2d[j][i].x = (map->coord_2d[j][i].x) * zoom;
			map->coord_2d[j][i].y = (map->coord_2d[j][i].y) * zoom;
		}
	}
}
