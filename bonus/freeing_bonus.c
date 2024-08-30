/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:28:36 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/19 21:25:04 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_path_content(t_paths *paths)
{
	if (paths->east)
		free(paths->east);
	if (paths->west)
		free(paths->west);
	if (paths->north)
		free(paths->north);
	if (paths->south)
		free(paths->south);
	if (paths->floor)
		free(paths->floor);
	if (paths->ceiling)
		free(paths->ceiling);
}

void	free_data_content(t_gamedata *data)
{
	if (data->map)
		free_2d(data->map);
	if (data->paths)
	{
		free_path_content(data->paths);
		free(data->paths);
	}
	if (data->playerdata)
		free(data->playerdata);
	delete_textures(data);
}
