/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:12:34 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/01 12:39:56 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	error_exit(int status)
{
	if (status == OPEN_FAILURE)
	{
		ft_printerror("Error opening input file, exiting");
		exit (EXIT_FAILURE);
	}
	if (status == CLOSE_FAILURE)
	{
		ft_printerror("Error closing input file, exiting");
		exit (EXIT_FAILURE);
	}
	if (status == SPLIT_FAILURE)
	{
		ft_printerror("Error loading map from input file, exiting");
		exit (EXIT_FAILURE);
	}
}

int	file_validation(char *filename)
{
	char	*temp;

	temp = ft_strrchr(filename, 0) - 4;
	if (ft_strcmp(temp, ".cub"))
	{
		printf("file must be a .cub file\n");
		return (0);
	}
	return (1);
}

void	load_map(t_file *filedata)
{
	char	*temp;
	char	*mapline;
	char	*oneline;
	int		fd;

	mapline = NULL;
	fd = open(filedata->filename, O_RDONLY);
	if (fd == -1)
		error_exit(OPEN_FAILURE);
	oneline = get_next_line(fd);
	temp = oneline;
	if (!oneline)
		return ;
	while (oneline)
	{
		mapline = ft_strjoin_flex(mapline, oneline, 3);
		oneline = get_next_line(fd);
	}
	free(temp);
	printf("content of mapline:%s\n", mapline);
	filedata->map = ft_split(mapline, '\n');
	if (!filedata->map)
		error_exit(SPLIT_FAILURE);
	free(mapline);
	close (fd);
	if (fd == -1)
		error_exit(CLOSE_FAILURE);
}
