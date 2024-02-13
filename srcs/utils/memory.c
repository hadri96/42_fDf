/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:05:46 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/13 16:05:53 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/fdf.h"

void	free_map(t_map3D *map)
{
	int	i;

	i = -1;
	while (++i < map->limits.y)
		free(map->coordinates[i]);
	free(map->coordinates);
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
}
