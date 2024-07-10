/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:12:34 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/10 18:23:08 by dbarrene         ###   ########.fr       */
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

	fullscene = NULL;
	oneline = get_next_line(fd);
	temp = oneline;
	if (!oneline)
		return ;
	while (oneline)
	{
		fullscene = ft_strjoin_flex(fullscene, oneline, 3);
		oneline = get_next_line(fd);
	}
	free(temp);
	filedata->scene_data = ft_split(fullscene, '\n');
	if (!filedata->scene_data)
		error_exit(SPLIT_FAILURE);
	free(fullscene);
}
