/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:19:16 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 17:01:22 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
int		map_validation(char **map)
{
	int x;
	int	y;

	y = 0;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || is_player_dir(map[y][x]))
			{
				if (is_player_dir(map[y][x]) && y >= ft_arrlen(map) - 1)
					return (1);
				if (ft_is_whitespace(map[y][x + 1]) || !map[y][x + 1])
					return (1);
				if (ft_is_whitespace(map[y][x - 1]) || !map[y][x - 1])
					return (1);
				if (ft_is_whitespace(map[y + 1][x]) || !map[y + 1][x])
					return (1);
				if (ft_is_whitespace(map[y - 1][x]) || !map[y - 1][x])
					return (1);
				if (ft_is_whitespace(map[y + 1][x + 1]) || !map[y + 1][x + 1])
					return (1);
				if (ft_is_whitespace(map[y + 1][x - 1]) || !map[y + 1][x - 1])
					return (1);
				if (ft_is_whitespace(map[y - 1][x + 1]) || !map[y - 1][x + 1])
					return (1);
				if (ft_is_whitespace(map[y - 1][x - 1]) || !map[y - 1][x - 1])
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}


 * check that every 0 or player is not next to null terminator or  emptyspace!!!
 */

int	check_bounds(char **map, int x, int y)
{
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	return (1);
}

int	check_dir(char **map, int x, int y)
{
	if (check_bounds(map, x, y) && (ft_is_whitespace(map[y][x] || !map[y][x])))
		return (0);
	else if (!check_bounds(map, x, y))
		return (0);
	return (1);
}

int	check_directions(char **map, int x, int y)
{
	if ((map[y][x] == '0' || is_player_dir(map[y][x])) && map[y + 1])
	{
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
