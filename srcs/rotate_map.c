/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:22:37 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/18 15:22:37 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

void	rotate_map_iso(t_map3D *map)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
			map->coord_3d[j][i] = isometric_view(map->coord_3d[j][i]);
	}
}

void rotate_map_x(t_map3D *map, double angle)
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

void rotate_map_y(t_map3D *map, double angle)
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

void rotate_map_z(t_map3D *map, double angle)
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

