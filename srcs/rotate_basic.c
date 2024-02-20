/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:06:26 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/19 12:07:03 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

t_point3D	rotate_x(t_point3D point, double angle)
{
	double	radians;

	radians = M_PI * angle / 360;
	point.y = point.y * cos(radians) - point.z * sin(radians);
	point.z = point.y * sin(radians) + point.z * cos(radians);
	return (point);
}

t_point3D	rotate_y(t_point3D point, double angle)
{
	double	radians;

	radians = M_PI * angle / 360;
	point.x = point.x * cos(radians) + point.z * sin(radians);
	point.z = - point.x * sin(radians) + point.z * cos(radians);
	return (point);
}

t_point3D	rotate_z(t_point3D point, double angle)
{
	double	radians;

	radians = M_PI * angle / 360;
	point.x = point.x * cos(radians) - point.y * sin(radians);
	point.y = point.x * sin(radians) + point.y * cos(radians);
	return (point);
}

