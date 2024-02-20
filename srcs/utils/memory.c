/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:28:32 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/19 11:28:32 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/fdf.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->limits.y)
		free(map->coord_3d[i]);
	free(map->coord_3d);
	map->coord_3d = NULL;
	i = -1;
	while (++i < map->limits.y)
		free(map->coord_2d[i]);
	free(map->coord_2d);
	map->coord_2d = NULL;
}

void	free_lines(t_list *lines)
{
	t_list	*tmp;

	while (lines)
	{
		tmp = lines->next;
		free(lines->content);
		free(lines);
		lines = tmp;
	}
}

void	free_strarr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

