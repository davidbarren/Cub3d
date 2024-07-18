/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/17 16:44:37 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_gamestate(t_gamedata *data)
{
	data->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	mlx_image_t* img = mlx_new_image(data->window, WINDOW_WIDTH, WINDOW_HEIGHT);
    int y = 0;
	while (data->map[y] != NULL)
	{
		int x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == '1') // Nota: Asegúrate de comparar con el carácter '1'
			{
				int i = 0;
				while (i <= 50)
				{
					int i2 = 0;
					while(i2 <= PIXEL_SIZE)
					{
						mlx_put_pixel(img, x * 50 + i, y * 50 + i2, data->floor[0]);
						i2++;
					}
				i++;
				}
					//mlx_put_pixel(img, x * PIXEL_SIZE + i, y * PIXEL_SIZE + j, color_red);
			}
			x++;
		}
		y++;
	}
    mlx_image_to_window(data->window, img, 0, 0);
    mlx_loop(data->window);
    mlx_close_window(data->window);
    mlx_terminate(data->window);
    free_data_content(data);
    free(data);
    printf("end of game :)\n");
}
