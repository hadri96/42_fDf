/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:07:38 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/13 16:07:38 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/get_next_line.h"
#include <fcntl.h>

unsigned int	ft_atoi_hex(char *str)
{
	unsigned int	result;
	int				i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 16 + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * 16 + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * 16 + (str[i] - 'A' + 10);
		else
			return (result);
		i++;
	}
	return (result);
}

t_list	*parse_lines(char *filepath)
{
	int		fd;
	char	*line;
	t_list	*lines;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		if (!line || !lines)
			return (NULL);
		line = get_next_line(fd);
	}
	return (lines);
}
