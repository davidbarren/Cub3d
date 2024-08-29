/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:31:19 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 13:39:18 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	initialize_player_angle(t_gamedata *data, char **map)
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

int	is_valid_char(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	if (c == '1' || c == '0')
		return (1);
	if (ft_is_whitespace(c))
		return (1);
	return (0);
}

int	is_player_dir(char c)
{
	if (c == 'N')
		return (NORTH);
	if (c == 'E')
		return (EAST);
	if (c == 'S')
		return (SOUTH);
	if (c == 'W')
		return (WEST);
	return (0);
}

static void	update_player_pos(t_gamedata *data, int pcount, int x, int y)
{
	if (pcount || y >= (ft_arrlen(data->map) - 1))
		error_free(BAD_MAP, data, NULL);
	data->playerdata->x_pos = x + STARTING_MARG;
	data->playerdata->y_pos = y + STARTING_MARG;
	initialize_player_angle(data, data->map);
	data->playerdata->angle = is_player_dir(data->map[y][x]);
}

void	find_player_pos(t_gamedata *data, char **map)
{
	static int	y;
	static int	x;
	static int	pcount;

	while (map[y])
	{
		if (ft_strlen(map[y]) > data->width)
			data->width = ft_strlen(map[y]);
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_char(map[y][x]))
				error_free(BAD_MAP, data, NULL);
			if (is_player_dir(map[y][x]))
			{
				update_player_pos(data, pcount, x, y);
				pcount += 1;
			}
			x++;
		}
		y++;
	}
	if (pcount != 1)
		error_free(BAD_MAP, data, NULL);
	data->height = y;
}
