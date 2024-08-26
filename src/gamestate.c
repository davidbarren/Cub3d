/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/27 01:05:07 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialize_player(t_gamedata *data, char **map)
{
	t_player	*player;

	player = data->playerdata;
	if (map[(int)player->y_pos][(int)player->x_pos] == 'N')
	{
		player->angle = 3 * PI / 2;
		return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'S')
	{
		player->angle = PI / 2;
		printf("player  angle start:%f\n", player->angle);
		return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'E')
	{
		player->angle = 0;
		return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'W')
	{
		player->angle = PI;
		return ;
	}
}

void	ft_player(t_gamedata *data)
{
	uint32_t	color;
	int			player_size;
	int			centerx;
	int			centery;

	player_size = PIXEL_SIZE / 2;
	centerx = PIXEL_SIZE * data->playerdata->x_pos;
	centery = PIXEL_SIZE * data->playerdata->y_pos;
	color = get_color(0, 0, 255, 255);
	int	i = -player_size / 2;
	while (i < player_size / 3)
	{
		int	j = -player_size / 3;
		while (j < player_size / 3)
		{
			mlx_put_pixel(data->img, centerx + j, centery + i, color);
			++j;
		}
		++i;
	}
}

void	draw_flor(t_gamedata *data)
{
	int			x;
	int			y;
	int			i;
	int			i2;
	uint32_t	color;

	y = 0;
	color = get_color(255, 255, 255, 255);
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] != '1' && data->map[y][x] != ' ' && data->map[y][x] != '\t')
			{
				i = 0;
				while (i < PIXEL_SIZE)
				{
					i2 = 0;
					while (i2 < PIXEL_SIZE)
					{
						mlx_put_pixel(data->img, x * PIXEL_SIZE + i, y * PIXEL_SIZE + i2, color);
						i2++;
					}
					i++;
				}
			}
			x++;
		}
		y++;
	}
}

void	display_map(t_gamedata *data)
{
	int			x;
	int			y;
	int			i;
	int			i2;
	uint32_t	color;

	y = 0;
	color = get_color(0, 0, 0, 255);
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == '1')
			{
				i = 0;
				while (i < PIXEL_SIZE)
				{
					i2 = 0;
					while (i2 < PIXEL_SIZE)
					{
						mlx_put_pixel(data->img, x * PIXEL_SIZE + i, y * PIXEL_SIZE + i2, color);
						i2++;
					}
					i++;
				}
			}
			x++;
		}
		y++;
	}
	draw_flor(data);
	//ft_player(data);
}


void	init_gamestate(t_gamedata *data)
{
	data->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	data->img = mlx_new_image(data->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	initialize_player(data, data->map);
	load_texture(data);
	mlx_image_to_window(data->window, data->img, 0, 0);
	display_map(data);
	mlx_cursor_hook(data->window, &mouse_move_hook, data);
	mlx_loop_hook(data->window, &cub3d_keyhook, data);
	mlx_loop(data->window);
	mlx_close_window(data->window);
	mlx_terminate(data->window);
	free_data_content(data);
	free(data);
	printf("end of game :)\n");
}
