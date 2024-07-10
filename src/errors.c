/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:58:19 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/10 18:22:44 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		ft_printerror("Error loading data from input file, exiting");
		exit (EXIT_FAILURE);
	}
	if (status == NONEXISTING_FILE)
	{
		ft_printerror("Error: input file does not exist\n");
		exit (EXIT_FAILURE);
	}
	if (status == BAD_FORMAT || status == BAD_ARGS)
	{
		ft_printerror("Error: input file must exist and have a .cub extension\n");
		exit (EXIT_FAILURE);
	}
}
