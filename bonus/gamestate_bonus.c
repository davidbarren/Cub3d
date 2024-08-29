/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 16:15:52 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	cubd3_loop(t_gamedata *data)
{
	mlx_cursor_hook(data->window, &mouse_move_hook, data);
	if (mlx_loop_hook(data->window, &cub3d_keyhook, data) != true)
	{
		ft_printerror("Error: mlx_loop_hook failed\n");
		error_free(BAD_KEY_LOOP, data, NULL);
	}
	mlx_loop(data->window);
}

void	init_gamestate(t_gamedata *data)
{
	data->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	if (!data->window)
	{
		ft_printerror("Error: Failed to initialize window.\n");
		error_free(BAD_MLX_INIT, data, NULL);
	}
	data->img = mlx_new_image(data->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
	{
		ft_printerror("Error: failed to create new image.\n");
		error_free(BAD_NEW_IMG, data, NULL);
	}
	load_texture(data);
	if ((mlx_image_to_window(data->window, data->img, 0, 0)) < 0)
	{
		ft_printerror("Error: Failed to put image to window.\n");
		error_free(BAD_ADDING_IMG, data, NULL);
	}
	display_mini_map(data);
	cubd3_loop(data);
	mlx_close_window(data->window);
	mlx_terminate(data->window);
	free_data_content(data);
	free(data);
	printf("end of game :)\n");
}
