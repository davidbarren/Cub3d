/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:58:04 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/30 13:40:30 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	verify_path_access(char *path)
{
	int	fd;

	fd = open (path, O_RDONLY);
	if (fd == -1)
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
		data->pixel_size = 10;
}

void	verify_map(t_gamedata *data)
{
	if (map_validation(data->map))
		error_free(BAD_MAP, data, NULL);
	data->playerdata = ft_calloc(1, sizeof(t_player));
	find_player_pos(data, data->map);
	set_pixel_size(data);
}
