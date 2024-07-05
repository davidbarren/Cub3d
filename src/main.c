/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:12 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/01 12:40:01 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_file	filedata;

	if (argc != 2)
	{
		printf("Incorrect number of arguments, please include a .cub file\n");
		return (1);
	}
	filedata.filename = (argv[1]);
	if (!file_validation(filedata.filename))
		printf("bad format\n");
	load_map(&filedata);
	return (0);
}
