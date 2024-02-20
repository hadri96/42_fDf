/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:40:24 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/18 18:40:45 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

void	translate_map(t_map *map, double offset_x, double offset_y)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->limits.y)
	{
		i = -1;
		while (++i < map->limits.x)
		{
			map->coord_2d[j][i].x += offset_x;
			map->coord_2d[j][i].y += offset_y;
		}
	}
}

void	center_map(t_map *map)
{
	double	offset_x;
	double	offset_y;

	offset_x = map->coord_2d[(int) \
map->limits.y / 2][(int) map->limits.x / 2].x - 960;
	offset_y = map->coord_2d[(int) \
map->limits.y / 2][(int) map->limits.x / 2].y - 540;
	translate_map(map, -offset_x, -offset_y);

}
