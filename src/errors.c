/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:58:19 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/17 11:46:38 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(int status)
{
	if (status == EMPTY_FILE)
		ft_printerror("Error: please ensure the file has content");
	if (status == OPEN_FAILURE)
		ft_printerror("Error opening input file, exiting");
	if (status == CLOSE_FAILURE)
		ft_printerror("Error closing input file, exiting");
	if (status == SPLIT_FAILURE)
		ft_printerror("Error loading data from input file, exiting");
	if (status == NONEXISTING_FILE)
		ft_printerror("Error: input file does not exist\n");
	if (status == BAD_FORMAT || status == BAD_ARGS)
		ft_printerror("Error: input file must exist with a .cub extension\n");
	if (status == INVALID_MAP)
		ft_printerror("Error: map provided is invalid\n");
	exit (EXIT_FAILURE);
}

void	error_free(int status, t_gamedata *data, t_file *scenedata)
{
	if (status == BAD_SCENE)
		ft_printerror("Error: incorrect file content\n");
	if (status == BAD_RGB)
		ft_printerror("Error: RGB values must be within 0 and 255\n");
	free_2d(scenedata->scene_data);
	free_data_content(data);
	free(data);
	exit(EXIT_FAILURE);
}
