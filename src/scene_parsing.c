/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:00:25 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/11 17:51:20 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_border(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

void	ft_skip_spaces(char **str)
{
	while (**str && (**str == ' ' || **str == '\t' || **str == '\v'))
		*str += 1;
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
			paths->north_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "SO", 2))
			paths->south_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "WE", 2))
			paths->west_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "EA", 2))
			paths->east_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "C", 1))
			paths->ceiling_colorscheme = ft_strdup(temp);
		else if (!ft_strncmp(temp, "F", 1))
			paths->floor_colorscheme = ft_strdup(temp);
		i++;
	}
	scenedata->map_index = i;
	printf("index where map begins:%d\n", i);
	print_2d(scene);
}

int	load_colorschemes(char *str, unsigned char *target)
{
	char	*temp;
	int		i;

	i = 0;
	temp = str;
	while (*temp)
	{
		if (!ft_isdigit(*temp))
			temp++;
		else
		{
			if (ft_atoi(temp) < 0 || ft_atoi(temp) > 255)
				return (1);
			target[i] = ft_atoi(temp);
			i++;
			while (ft_isdigit(*temp))
				temp++;
		}
	}
	printf("value of r in floor:%d\n", target[0]);
	printf("value of g in floor:%d\n", target[1]);
	printf("value of b in floor:%d\n", target[2]);
	printf("temp in load colorscheme:%s\n", temp);
	return (0);
}

void	scene_parsing(t_file *scenedata)
{
	t_gamedata	*data;
	t_paths		*paths;	

	data = ft_calloc (1, sizeof(t_gamedata));
	paths = ft_calloc (1, sizeof(t_paths));
	load_paths(scenedata, paths);
	data->paths = paths;
	if (verify_paths_data(paths))
		error_free(BAD_SCENE, data, scenedata);
	print_paths(paths);
	if (load_colorschemes(paths->floor_colorscheme, data->floor)
		|| load_colorschemes(paths->ceiling_colorscheme, data->ceiling))
		error_free(BAD_RGB, data, scenedata);
	if (load_map(scenedata, data))
		error_free(INVALID_MAP, data, scenedata);
	free_data_content(data);
	free(data);
}
