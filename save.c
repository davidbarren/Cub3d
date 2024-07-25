void	move_left(t_gamedata *content)
{
	t_player	*player;

	player = content->playerdata;
	if (content->map[(int)player->y_pos][(int)player->x_pos - 1] == '1')
        return ;
	else
    { 
		turnPlayer(content, -1);
		printf("letf %f\n", player->angle);
        //content->player->instances[0].x -= player->x_pos;
    }
}

void	move_right(t_gamedata *content)
{
	t_player *player;

	player = content->playerdata;
    if (content->map[(int)player->y_pos][(int)player->x_pos + 1] == '1')
        return ;
    else
    {
        turnPlayer(content, 1);
		printf("right %f\n", player->angle); 
        //content->player->instances[0].x += player->x_pos;
    }
    //printf("x: %d\n", content->x);
}
void    move_up(t_gamedata *content)
{
	t_player *player;

	//movePlayer(content, -1);
	player = content->playerdata;
    if (content->map[(int)player->y_pos - 1][(int)player->x_pos] == '1')
        return ;
    else
    {   
		//movePlayer(content, -1);
		printf("normal %f  %f\n", player->y_pos, player->x_pos);
		printf("intances %d  %d\n", content->player->instances[0].y, content->player->instances[0].x);
		//printf("down %d  %d\n", content->player->instances[0].x, content->player->instances[0].y);
        //content->player->instances[0].z = player->angle;
		//content->player->instances[0].x = player->x_pos;
        content->player->instances[0].y -= (int)player->y_pos;
        //player->y_pos -= 1;
    }
    //printf("y: %d\n", content->y);
}
void    move_down(t_gamedata *content)
{
	t_player *player;

	//movePlayer(content, 1);
	player = content->playerdata;
    if (content->map[(int)player->y_pos + 1][(int)player->x_pos] == '1')
        return ;
    else
    {  
		//movePlayer(content, 1); 
		printf("normal %f  %f\n", player->y_pos, player->x_pos);
		printf("intances %d  %d\n", content->player->instances[0].y, content->player->instances[0].x);;
        //content->player->instances[0].z = player->angle;
		//content->player->instances[0].x = player->x_pos;
        content->player->instances[0].y += (int)player->y_pos;
        //player->y_pos += 1;
    }
   //printf("y: %d\n", content->y);
}
void	move_player(t_gamedata *data)
{
	
    if (mlx_is_key_down(data->window, MLX_KEY_W ))
        moving(data, -1);
   	else if (mlx_is_key_down(data->window, MLX_KEY_S))
        moving(data, 1);
	else if (mlx_is_key_down(data->window, MLX_KEY_A))
		turnPlayer(data, -1);
	else if (mlx_is_key_down(data->window, MLX_KEY_D))
        turnPlayer(data, 1);  
}