/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:05:30 by hmorand           #+#    #+#             */
/*   Updated: 2024/02/13 07:59:05 by hmorand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1048576
# endif

typedef struct s_reader
{
	int		fd;
	int		buffer_location;
	int		buffer_size;
	char	buffer[BUFFER_SIZE];
	int		is_open;
}	t_reader;

char		*get_next_line(int fd);
t_reader	current_file(int fd, t_reader (*files)[24]);
void		ft_putstr_fd(char *s, int fd);
void		update_reader(t_reader current, int fd, t_reader (*files)[24]);
int			search_end_line(t_reader *current, int size_buff);

#endif
