/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:05:42 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/20 11:06:04 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

double	compute_y(int x, double slope, double intersect, double y)
{
	double	new_y;

	if (slope == INFINITY)
		return (y + 1);
	else if (slope == -INFINITY)
		return (y + 1);
	new_y = x * slope + intersect;
	return (new_y);
}

bool	is_steep(double slope)
{
	if (slope == INFINITY || slope == -INFINITY)
		return (false);
	if (slope > 1 || slope < -1)
		return (true);
	return (false);
}

bool	to_right(t_point2D a, t_point2D b)
{
	if (a.x > b.x)
		return (true);
	return (false);
}

void	swap_xy(t_point2D *a)
{
	int	temp;

	a->swapped = !a->swapped;
	temp = a->x;
	a->x = a->y;
	a->y = temp;
}

void	swap_points(t_point2D *a, t_point2D *b)
{
	t_point2D	temp;

	temp = *a;
	a = b;
	b = &temp;
}
