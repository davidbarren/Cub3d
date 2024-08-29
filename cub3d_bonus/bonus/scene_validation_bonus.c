/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:19:16 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 16:18:00 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	verify_path_access(char *path)
{
	if (access(path, O_RDONLY))
		return (1);
	return (0);
}

int	verify_paths_data(t_paths *paths)
{
	if (!paths->east || verify_path_access(paths->east))
		return (1);
	if (!paths->west || verify_path_access(paths->west))
		return (1);
	if (!paths->north || verify_path_access(paths->north))
		return (1);
	if (!paths->south || verify_path_access(paths->south))
		return (1);
	if (!paths->floor)
		return (1);
	if (!paths->ceiling)
		return (1);
	return (0);
}

void	set_pixel_size(t_gamedata *data)
{
	if (data->width > 50 || data->height > 30)
		data->pixel_size = 5;
	else
		data->pixel_size  = 10;
}

void	verify_map(t_gamedata *data)
{
	if (map_validation(data->map))
		error_free(BAD_MAP, data, NULL);
	data->playerdata = ft_calloc(1, sizeof(t_player));
	find_player_pos(data, data->map);
	set_pixel_size(data);
}
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

int	check_directions(char **map, int *x, int *y)
{
	while (map[*y][*x])
	{
		if (map[*y][*x] == '0' || is_player_dir(map[*y][*x]))
		{
			if (ft_is_whitespace(map[*y][*x + 1]) || !map[*y][*x + 1])
				return (1);
			if (ft_is_whitespace(map[*y][*x - 1]) || !map[*y][*x - 1])
				return (1);
			if (ft_is_whitespace(map[*y + 1][*x]) || !map[*y + 1][*x])
				return (1);
			if (ft_is_whitespace(map[*y - 1][*x]) || !map[*y - 1][*x])
				return (1);
			if (ft_is_whitespace(map[*y + 1][*x + 1]) || !map[*y + 1][*x + 1])
				return (1);
			if (ft_is_whitespace(map[*y + 1][*x - 1]) || !map[*y + 1][*x - 1])
				return (1);
			if (ft_is_whitespace(map[*y - 1][*x + 1]) || !map[*y - 1][*x + 1])
				return (1);
			if (ft_is_whitespace(map[*y - 1][*x - 1]) || !map[*y - 1][*x - 1])
				return (1);
		}
		*x += 1;
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
		if (check_directions(map, &x, &y))
			return (1);
		y++;
	}
	return (0);
}
