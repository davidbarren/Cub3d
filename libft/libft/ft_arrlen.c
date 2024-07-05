/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:32:35 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/01 10:33:36 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!*arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}
