/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:00:25 by dbarrene          #+#    #+#             */
/*   Updated: 2024/09/02 14:08:22 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_border(char *line)
{
	if (*line == '\n' || *line == EOF)
		return (0);
	while (*line)
	{
		if (*line != '1' && *line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

char	*set_path(char *pathdest, char *pathsrc)
{
	if (pathdest)
	{
		free(pathdest);
		return (NULL);
	}
	ft_skip_spaces(&pathsrc);
	return (ft_strdup(pathsrc));
}

void	load_paths(t_file *scenedata, t_paths *paths)
{
	char	**scene;
	char	*temp;
	int		i;

	i = 0;
	scene = scenedata->scene_data;
	while (scene[i] && !is_border(scene[i]))
	{
		temp = scene[i];
		ft_skip_spaces(&temp);
		if (!ft_strncmp(temp, "NO", 2))
			paths->north = set_path(paths->north, (temp + 2));
		else if (!ft_strncmp(temp, "SO", 2))
			paths->south = set_path(paths->south, (temp + 2));
		else if (!ft_strncmp(temp, "EA", 2))
			paths->east = set_path(paths->east, (temp + 2));
		else if (!ft_strncmp(temp, "WE", 2))
			paths->west = set_path(paths->west, (temp + 2));
		else if (!ft_strncmp(temp, "C", 1))
			paths->ceiling = set_path(paths->ceiling, temp + 1);
		else if (!ft_strncmp(temp, "F", 1))
			paths->floor = set_path(paths->floor, temp + 1);
		i++;
	}
	scenedata->map_index = i;
}

int	load_colorschemes(char *str, unsigned char *target)
{
	char	*temp;
	int		i;
	int		result;
	char	*token;

	i = 0;
	temp = str;
	while (*temp && (ft_is_whitespace(*temp) || *temp == 'F' || *temp == 'C' ))
		temp++;
	token = ft_strtok(temp, ',');
	while (token && i < 3)
	{
		result = ft_atoi_rgb(token);
		if (result < 0)
			return (BAD_RGB);
		target[i] = result;
		token = ft_strtok(NULL, ',');
		i++;
	}
	if (token || i != 3)
		return (BAD_RGB);
	return (0);
}

t_gamedata	*scene_parsing(t_file *scenedata)
{
	t_gamedata	*data;
	t_paths		*paths;	

	data = ft_calloc (1, sizeof(t_gamedata));
	paths = ft_calloc (1, sizeof(t_paths));
	if (!paths || !data)
	{
		free(paths);
		free(data);
		free_2d (scenedata->scene_data);
		error_exit(SPLIT_FAILURE);
	}
	load_paths(scenedata, paths);
	data->paths = paths;
	if (verify_paths_data(paths))
		error_free(BAD_SCENE, data, scenedata);
	if (load_colorschemes(paths->floor, data->floor)
		|| load_colorschemes(paths->ceiling, data->ceiling))
		error_free(BAD_RGB, data, scenedata);
	if (load_map(scenedata, data))
		error_free(INVALID_MAP, data, scenedata);
	return (data);
}
