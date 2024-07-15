/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:12:34 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/15 04:20:39 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	file_validation(t_file *filedata, int argc, char **av)
{
	char	*temp;

	if (argc != 2)
		error_exit(BAD_ARGS);
	filedata->filename = av[1];
	temp = ft_strrchr(filedata->filename, 0) - 4;
	if (ft_strcmp(temp, ".cub"))
		error_exit(BAD_FORMAT);
}

void	scene_opening(t_file *filedata)
{
	int	fd;

	if (access(filedata->filename, F_OK))
		error_exit(NONEXISTING_FILE);
	fd = open(filedata->filename, O_RDONLY);
	if (fd == -1)
		error_exit(OPEN_FAILURE);
	load_scene(filedata, fd);
	close (fd);
	if (fd == -1)
		error_exit(CLOSE_FAILURE);
}

void	load_scene(t_file *filedata, int fd)
{
	char	*temp;
	char	*fullscene;
	char	*oneline;
	char	in_map;

	in_map = 0;
	fullscene = NULL;
	oneline = get_next_line(fd);
	temp = oneline;
	if (!oneline)
		return ;
	while (oneline)
	{
		fullscene = ft_strjoin_flex(fullscene, oneline, 3);
		oneline = get_next_line(fd);
		if (oneline && is_border(oneline) && !in_map)
			in_map = 1;
		if (oneline && *oneline == '\n' && in_map)
			in_map = INVALID_MAP;
	}
	free(temp);
	if (in_map != INVALID_MAP)
		filedata->scene_data = ft_split(fullscene, '\n');
	free(fullscene);
	if (in_map == INVALID_MAP)
		error_exit(INVALID_MAP);
	if (!filedata->scene_data)
		error_exit(SPLIT_FAILURE);
}

int	verify_paths_data(t_paths *paths)
{
	if (!paths->east_path)
		return (1);
	if (!paths->west_path)
		return (1);
	if (!paths->north_path)
		return (1);
	if (!paths->south_path)
		return (1);
	if (!paths->floor_colorscheme)
		return (1);
	if (!paths->ceiling_colorscheme)
		return (1);
	return (0);
}

int	copy_map(t_file *scenedata, t_gamedata *data)
{
	int		arrlen;
	int		i;
	char	**fullscene;

	i = 0;
	fullscene = scenedata->scene_data;
	fullscene += scenedata->map_index;
	arrlen = ft_arrlen(fullscene);
	data->map = ft_calloc(arrlen + 1, sizeof (char *));
	while (fullscene[i])
	{
		data->map[i] = ft_strdup(fullscene[i]);
		if (!data->map[i])
			return (1);
		i++;
	}
	return (0);
}
/*
int	verify_map(t_gamedata *data)
{

	return (0);
}
*/
int	load_map(t_file *scenedata, t_gamedata *data)
{
	if (copy_map(scenedata, data))
		return (1);
	print_2d(data->map);
	free_2d(scenedata->scene_data);
//	if (verify_map(data))
//		return (1);
	return (0);
}
