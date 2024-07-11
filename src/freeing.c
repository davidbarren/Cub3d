/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:28:36 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/11 15:08:55 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_path_content(t_paths *paths)
{
	if (paths->east_path)
		free(paths->east_path);
	if (paths->west_path)
		free(paths->west_path);
	if (paths->north_path)
		free(paths->north_path);
	if (paths->south_path)
		free(paths->south_path);
	if (paths->floor_colorscheme)
		free(paths->floor_colorscheme);
	if (paths->ceiling_colorscheme)
		free(paths->ceiling_colorscheme);
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
}
