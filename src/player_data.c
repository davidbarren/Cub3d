/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:31:19 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/18 17:48:42 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (pcount)
		error_free(BAD_MAP, data, NULL);
	data->playerdata->x_pos = x;
	data->playerdata->y_pos = y;
	data->playerdata->dir = is_player_dir(data->map[y][x]);
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