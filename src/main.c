/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:12 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/17 13:41:39 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_file		filedata;
	t_gamedata	*data;
//	(void)	data;
	file_validation(&filedata, argc, argv);
	scene_opening(&filedata);
	data = scene_parsing(&filedata);
	if (map_validation(data->map))
		printf("fuck\n");
	free_data_content(data);
	free(data);
//	init_gamestate(data);
	return (0);
}
