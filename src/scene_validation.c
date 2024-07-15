/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:19:16 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/15 14:44:44 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	verify_path_access(char *path)
{
	if (access(path, O_RDONLY))
		return (1);
	return (0);
}

int	verify_paths_data(t_paths *paths)
{
	if (!paths->east_path|| verify_path_access(paths->east_path))
		return (1);
	if (!paths->west_path || verify_path_access(paths->west_path))
		return (1);
	if (!paths->north_path || verify_path_access(paths->north_path))
		return (1);
	if (!paths->south_path || verify_path_access(paths->south_path))
		return (1);
	if (!paths->floor_colorscheme)
		return (1);
	if (!paths->ceiling_colorscheme)
		return (1);
	return (0);
	// checar si en verdad existen estos paths
}

/*
int	map_validation(char **map)
{
	return (0);
}*/
