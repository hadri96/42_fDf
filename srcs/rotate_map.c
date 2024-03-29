/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:09:36 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/19 12:09:36 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

void rotate_map_x(t_map *map, double angle)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
			map->coord_3d[j][i] = rotate_x(map->coord_3d[j][i], angle);
	}
}

void rotate_map_y(t_map *map, double angle)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
			map->coord_3d[j][i] = rotate_x(map->coord_3d[j][i], angle);
	}
}

void rotate_map_z(t_map *map, double angle)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
			map->coord_3d[j][i] = rotate_x(map->coord_3d[j][i], angle);
	}
}

