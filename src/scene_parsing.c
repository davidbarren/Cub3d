/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:00:25 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/10 18:28:49 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_border(char *line)
{
	while (*line)
	{
		if (*line != '1')
			return (0);
		line++;
	}
	return (1);
}

void	ft_skip_spaces(char **str)
{
	while (**str && (**str == ' ' || **str == '\t' || **str == '\v'))
		*str+= 1;
}

void	load_paths(t_file *scenedata, t_paths *paths)
{
	char **scene;
	int	i;

	i = 0;
	scene = scenedata->scene_data;
	while (scene[i] && !is_border(scene[i]))
	{
		ft_skip_spaces(&scene[i]);
		if (!ft_strncmp(scene[i], "NO", 2))
			paths->north_path = ft_strdup(scene[i]);
		else if (!ft_strncmp(scene[i], "SO", 2))
			paths->south_path = ft_strdup(scene[i]);
		else if (!ft_strncmp(scene[i], "WE", 2))
			paths->west_path = ft_strdup(scene[i]);
		else if (!ft_strncmp(scene[i], "EA", 2))
			paths->east_path = ft_strdup(scene[i]);
		else if (!ft_strncmp(scene[i], "C", 1))
			paths->ceiling_colorscheme = ft_strdup(scene[i]);
		else if (!ft_strncmp(scene[i], "F", 1))
			paths->floor_colorscheme = ft_strdup(scene[i]);
		i++;
	}
	printf("scenedata element at index 0 :%s\n", scenedata->scene_data[0]);
}

void	print_paths(t_paths *paths)
{
	printf("north_path:%s\n", paths->north_path);
	printf("south_path:%s\n", paths->south_path);
	printf("west_path:%s\n", paths->west_path);
	printf("east_path:%s\n", paths->east_path);
	printf("floor colorscheme:%s\n", paths->floor_colorscheme);
	printf("ceiling_colorscheme:%s\n", paths->ceiling_colorscheme);

}
void	scene_parsing(t_file *scenedata)
{
	t_gamedata *data;
	t_paths *paths;	

	data = ft_calloc (1, sizeof(t_gamedata));
	paths = ft_calloc (1, sizeof(t_paths));
	load_paths(scenedata, paths);
	print_2d(scenedata->scene_data);
	data->paths = paths;
	print_paths(paths);
}

