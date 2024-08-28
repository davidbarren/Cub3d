/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/28 16:37:27 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_mini_map_wall(t_gamedata *data, int x, int y)
{
	int			i;
	int			i2;
	uint32_t	color;

	i = 0;
	color = get_color(255, 0, 0, 255);
	while (i < PIXEL_SIZE)
	{
		i2 = 0;
		while (i2 < data->pixel_size)
		{
			mlx_put_pixel(data->img, x * data->pixel_size + i,
				y * data->pixel_size + i2, color);
			i2++;
		}
		i++;
	}
}

static void	draw_mini_map_flor(t_gamedata *data, int x, int y)
{
	int			i;
	int			i2;
	uint32_t	color;

	color = get_color(255, 255, 255, 255);
	i = 0;
	while (i < data->pixel_size)
	{
		i2 = 0;
		while (i2 < data->pixel_size)
		{
			mlx_put_pixel(data->img, x * data->pixel_size + i,
				y * data->pixel_size + i2, color);
			i2++;
		}
		i++;
	}
}

void	display_mini_map(t_gamedata *data)
{
	int			x;
	int			y;

	y = 0;
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] != '1' && data->map[y][x] != ' '
				&& data->map[y][x] != '\t')
				draw_mini_map_flor(data, x, y);
			if (data->map[y][x] == '1')
				draw_mini_map_wall(data, x, y);
			x++;
		}
		y++;
	}
	cast_rays(data);
}

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
