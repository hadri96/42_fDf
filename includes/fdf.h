/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 08:52:07 by yourlogin         #+#    #+#             */
/*   Updated: 2024/01/15 08:52:07 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point2D
{
	double		x;
	double		y;
	bool		swapped;
}	t_point2D;

typedef struct s_point3D
{
	double	x;
	double	y;
	double	z;
}	t_point3D;

#endif
