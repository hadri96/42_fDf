/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:54:11 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/20 11:05:17 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"
#include "../includes/fdf.h"

void	map_basics(t_map *map, t_list *lines)
{
	char	*first_line;
	char	**coordinates;
	int		i;

	map->limits.y = ft_lstsize(lines);
	first_line = lines->content;
	coordinates = ft_split(first_line, ' ');
	if (!coordinates)
		return ;
	i = -1;
	while (coordinates[++i + 1])
		free(coordinates[i]);
	map->limits.x = i + 1;
	map->max_height = -1000000;
	map->min_height = 1000000;
	free(coordinates[i]);
	free(coordinates);
}

t_point3D	parse_point(char *coordinates, t_map *map, int x, int y)
{
	t_point3D	point;
	char		**info;

	if (ft_strchr(coordinates, ','))
	{
		info = ft_split(coordinates, ',');
		point.z = ft_atoi(info[0]);
		point.color = ft_atoi_hex(info[1] + 2);
	}
	else
		point.z = (double) ft_atoi(coordinates);
	if (point.z > map->max_height)
		map->max_height = point.z;
	if (point.z < map->min_height)
		map->min_height = point.z;
	point.x = x;
	point.y = y;
	return (point);
}

t_point3D	**init_coordinates(t_map *map, t_list *lines)
{
	t_point3D	**map_coordinates;
	char		**coordinates;
	t_point3D	*line_coordinates;
	int			i;
	int			j;

	j = -1;
	map_coordinates = malloc(sizeof(t_point3D *) * (map->limits.y));
	if (!map_coordinates)
		return (NULL);
	while (map->limits.y > ++j)
	{
		line_coordinates = malloc(sizeof(t_point3D) * map->limits.x);
		coordinates = ft_split(lines->content, ' ');
		if (!line_coordinates || !coordinates)
			return (NULL);
		i = -1;
		while (++i < map->limits.x)
			line_coordinates[i] = parse_point(coordinates[i], map, i, j);
		map_coordinates[j] = line_coordinates;
		free_strarr(coordinates);
		lines = lines->next;
	}
	return (map_coordinates);
}

t_map	init_map(char *filename, double focal)
{
	t_map	map;
	t_list	*lines;

	lines = parse_lines(filename);
	if (!lines)
		return ((t_map){0, 0, 0, 0, (t_point3D){0, 0, 0, 0},
						(t_point2D){0, 0, 0, 0},
						(t_point2D){0, 0, 0, 0}, 0});
	map_basics(&map, lines);
	map.coord_3d = init_coordinates(&map, lines);
	init_2d(&map, focal);
	free_lines(lines);
	return (map);
}

/*int	main(void)
{
	t_map	map;

	map = init_map("test_maps/42.fdf", 5);
	if (!map.coord_3d)
		ft_putstr_fd("Error", 1);
	printf("limits x: %f\nlimits y: %f\n", map.limits.x, map.limits.y);
	for (int j = 0; map.limits.y > j; j++)
	{
		for (int i = 0; map.limits.x > i; i++)
		{
			ft_putnbr_fd(map.coord_3d[j][i].z, 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	free_map(&map);
}*/
