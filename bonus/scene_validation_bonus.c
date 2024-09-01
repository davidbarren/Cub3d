/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:19:16 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/30 18:58:13 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	check_bounds(char **map, int x, int y)
{
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	return (1);
}

int	check_dir(char **map, int x, int y)
{
	if (check_bounds(map, x, y) && (ft_is_whitespace(map[y][x]) || !map[y][x]))
		return (0);
	else if (!check_bounds(map, x, y))
		return (0);
	return (1);
}

int	check_directions(char **map, int x, int y)
{
	if ((map[y][x] == '0' || is_player_dir(map[y][x])) && map[y + 1])
	{
		if ((!x || !y))
			return (1);
		if (!check_dir(map, x + 1, y))
			return (1);
		if (!check_dir(map, x - 1, y))
			return (1);
		if (!check_dir(map, x, y - 1))
			return (1);
		if (!check_dir(map, x + 1, y - 1))
			return (1);
		if (!check_dir(map, x - 1, y - 1))
			return (1);
		if (!check_dir(map, x, y + 1))
			return (1);
		if (!check_dir(map, x + 1, y + 1))
			return (1);
		if (!check_dir(map, x - 1, y + 1))
			return (1);
	}
	return (0);
}

int	map_validation(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (check_directions(map, x, y))
				return (1);
			x++;
		}
		y++;
	}
	if (!is_border(map[y - 1]))
		return (1);
	return (0);
}
