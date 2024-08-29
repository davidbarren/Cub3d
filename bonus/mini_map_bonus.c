/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 16:16:21 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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