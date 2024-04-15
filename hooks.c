/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:50:40 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 19:57:42 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"



//called every update
int update(void *param)
{
	(void)param;
	update_raycast(get_player(), get_mapdata(NULL), get_mlx(), get_img());
	return (1);
}
void print_debug(t_player *player)
{
	printf("player->pos.x = %f, player->pos.y = %f\n", player->pos.x, player->pos.y);
	printf("player->direction.x = %f, player->direction.y = %f\n", player->direction.x, player->direction.y);
	
}
//called on keyboard actions
static int keyboard_manager(int keycode, void *param)
{
	static t_player *player = NULL;
	static int **map = NULL;
	(void)param;
	if(!player)
		player = get_player();
	if(!map)
		map = get_mapdata(NULL)->map;
	(keycode == XK_w) && (move_forward(player, map),1);
	(keycode == XK_s) && (move_backward(player, map),1);
	(keycode == XK_d) && (move_left(player, map),1);
	(keycode == XK_a) && (move_right(player, map),1);
	(keycode == XK_Left) && (rotate_left(player),1);
	(keycode == XK_Right) && (rotate_right(player),1);
	(keycode == XK_c) && (print_debug(player),1);
	return(1);
}

// //called on mouse actions
// static int mouse_manager(int keycode, void *param)
// {

// }

int	destroy_app(t_mlx *mlx)
{
	destroy_textures(get_texture(0), mlx);
    mlx_destroy_image(mlx->mlx_ptr, get_img()->img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free_struct_map(get_mapdata(NULL));
	exit(0);
	return (0);
}

void init_hook(void)
{
    t_mlx *mlx;
    mlx = get_mlx();
    // mlx_mouse_hook(mlx->win_ptr, &mouse_manager, NULL);
    mlx_key_hook(mlx->win_ptr, &keyboard_manager, NULL);
    mlx_hook(mlx->win_ptr, ON_DESTROY, 0, destroy_app, mlx);
    mlx_loop_hook(mlx->mlx_ptr, &update, NULL);
}

//mlx_mouse_get_pos