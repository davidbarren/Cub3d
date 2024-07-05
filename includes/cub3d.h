/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:32 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/01 12:43:39 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include "parsing.h"
# include <stdio.h>
# include <math.h>

/****************************
 * *********TYPEDEFS*********
 * *************************/
enum e_errors
{
	OPEN_FAILURE,
	CLOSE_FAILURE,
	MALLOC_FAILURE,
	SPLIT_FAILURE,
};
typedef struct s_textures
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
}	t_textures;

typedef struct s_file
{
	char		*filename;
	char		**map;
	t_textures	*textures;

}	t_file;

typedef struct s_player
{
	
}	t_player;
int		file_validation(char *filename);
void	load_map(t_file *filedata);
int		map_validation(char	**map);
#endif
