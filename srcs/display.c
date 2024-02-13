/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:27:32 by yourlogin         #+#    #+#             */
/*   Updated: 2024/01/23 17:29:46 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/fdf.h>

int handle_input(int keysym, t_mlx_data *data)
{
    if (keysym == XK_Escape)
}

int main()
{
    t_mlx_data  data;

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (0);

    data.win_ptr = mlx_new_window(data.mlx_ptr, HEIGHT, WIDTH, "My window");
    if (!data.win_ptr)
        free(data.mlx_ptr);
    mlx_key_hook(data.win_ptr, handle)
    mlx_loop(mlx_connection);
}