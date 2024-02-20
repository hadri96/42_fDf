/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:08:09 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/19 12:08:09 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

void	init_2d(t_map *map, double focal)
{
	int	i;
	int	j;

	map->coord_2d = malloc(sizeof(t_point2D *) * map->limits.y);
	if (!map->coord_2d)
		return ;
	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		map->coord_2d[j] = malloc(sizeof(t_point2D) * map->limits.x);
		if (!map->coord_2d[j])
			return ;
		while (++i < map->limits.x)
		{
			if (map->coord_3d[j][i].z != 0)
			{
				map->coord_2d[j][i].x = (map->coord_3d[j][i].x * focal) / \
map->coord_3d[j][i].z;
				map->coord_2d[j][i].y = (map->coord_3d[j][i].y * focal) / \
map->coord_3d[j][i].z;
			}
			else
			{
				map->coord_2d[j][i].x = map->coord_3d[j][i].x;
				map->coord_2d[j][i].y = map->coord_3d[j][i].y;
			}
			map->coord_2d[j][i].color = map->coord_3d[j][i].color;
			map->coord_2d[j][i].swapped = false;
		}
	}
}

void	transform_2d(t_map *map, double focal)
{
	int i;
	int j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
		{
			if (map->coord_3d[j][i].z != 0)
			{
				map->coord_2d[j][i].x = (map->coord_3d[j][i].x * focal) /
map->coord_3d[j][i].z;
				map->coord_2d[j][i].y = (map->coord_3d[j][i].y * focal) / \
map->coord_3d[j][i].z;
			}
			else
			{
				map->coord_2d[j][i].x = map->coord_3d[j][i].x;
				map->coord_2d[j][i].y = map->coord_3d[j][i].y;
			}
			map->coord_2d[j][i].swapped = false;
		}
	}
}

t_point2D	isometric_view(t_point3D point)
{
	t_point2D	new_point;

	new_point.x = (point.x - point.y) * cos(30 * M_PI / 180);
	new_point.y = (point.x + point.y) * sin(30 * M_PI / 180) - point.z;
	return (new_point);
}

void transform_iso(t_map *map)
{
	int i;
	int j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
			map->coord_2d[j][i] = isometric_view(map->coord_3d[j][i]);
	}
}
