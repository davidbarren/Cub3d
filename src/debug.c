/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:41:25 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/18 17:49:27 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		printf("%s\n", arr[i++]);
}

void	print_paths(t_paths *paths)
{
	printf("PRINTING PATHS:\n");
	printf("north:%s\n", paths->north);
	printf("south:%s\n", paths->south);
	printf("west_path:%s\n", paths->west);
	printf("east_path:%s\n", paths->east);
	printf("floor colorscheme:%s\n", paths->floor);
	printf("ceiling_colorscheme:%s\n", paths->ceiling);
}

void	print_colorschemes(t_gamedata *data)
{
	printf("PRINTING COLORS:\n");
	printf("floor colorschemes in R G B:\n");
	printf("R:%d\nG:%d\nB:%d\n", data->floor[0], data->floor[1], data->floor[2]);
	printf("ceiling colorschemes in R G B:\n");
	printf("R:%d\nG:%d\nB:%d\n", data->ceiling[0],
		data->ceiling[1], data->ceiling[2]);
}

void	print_playerdata(t_gamedata *data)
{
	printf("PRINTING GAMEDATA:\n");
	printf("height of map:%zu\n", data->height);
	printf("width of map:%zu\n", data->width);
	printf("player x pos: %f\n", data->playerdata->x_pos);
	printf("player y pos: %f\n", data->playerdata->y_pos);
	printf("player dir :%d\n", data->playerdata->dir);
}

void	print_gamedata(t_gamedata *data)
{
	printf("PRINTING FULL DATA:\n");
	print_paths(data->paths);
	print_colorschemes(data);
	printf("PRINTING MAP:\n");
	print_2d(data->map);
	print_playerdata(data);
}
