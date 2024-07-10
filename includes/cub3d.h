/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:32 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/10 18:23:49 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
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
	PERMS_FAILURE,
	NONEXISTING_FILE,
	BAD_FORMAT,
	BAD_ARGS,
};

typedef struct s_paths
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	char	*floor_colorscheme;
	char	*ceiling_colorscheme;
}	t_paths;

typedef struct s_file
{
	char		*filename;
	char		**scene_data;
	t_paths	*textures;

}	t_file;

typedef struct s_player
{
	double x_pos;
	double y_pos;

}	t_player;

typedef struct s_spritedata
{
	mlx_texture_t *north_wall_txt;
	mlx_texture_t *south_wall_txt;
	mlx_texture_t *east_wall_txt;
	mlx_texture_t *west_wall_txt;
	mlx_image_t *north_wall_img;
	mlx_image_t *south_wall_img;
	mlx_image_t *east_wall_img;
	mlx_image_t *west_wall_img;
}	t_spritedata;

typedef struct s_colorscheme
{
	int r;
	int g;
	int b;

}	t_colorscheme;

typedef struct s_gamedata
{
	char		*filename;
	char		**map;
	t_paths		*paths;
	t_colorscheme *floor;
	t_colorscheme *ceiling;

}	t_gamedata;

void	file_validation(t_file *filedata, int argc, char **av);
int		map_validation(char	**map);
void	print_2d(char **arr);
void	scene_opening(t_file *filedata);
void	load_scene(t_file *filedata, int fd);
void	error_exit(int status);
void	scene_parsing(t_file *scenedata);
#endif
