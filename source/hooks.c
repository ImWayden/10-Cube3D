/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:50:40 by wayden            #+#    #+#             */
/*   Updated: 2024/11/12 21:32:55 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** update - Called every update cycle of the program.
** @param: Unused parameter passed by the calling function.
**
** This function updates the raycasting visuals by calling `update_raycast`,
** which recalculates and redraws the view based on the player’s position
** and the current map data.
*/
int	update(void *param)
{
	(void)param;
	update_raycast(get_player(), get_mapdata(NULL), get_mlx(), get_img());
	return (1);
}

/**
** keyboard_manager - Handles keyboard actions for player movement and rotation.
** @keycode: Key code corresponding to a specific action (movement, rotation).
** @param: Unused parameter passed by the calling function.
**
** This function maps key actions to player movements and rotates the view
** by updating the player position or orientation based on `keycode`. It also
** triggers the application exit sequence on Escape key press.
**
** - XK_w : Move forward.
** - XK_s : Move backward.
** - XK_d : Move left.
** - XK_a : Move right.
** - XK_Left : Rotate view left.
** - XK_Right : Rotate view right.
** - XK_Escape : Exit the application.
*/
static int	keyboard_manager(int keycode, void *param)
{
	static t_player	*player;
	static int		**map;

	player = NULL;
	map = NULL;
	(void)param;
	if (!player)
		player = get_player();
	if (!map)
		map = get_mapdata(NULL)->map;
	(void)((keycode == XK_w) && (move_forward(player, map), 1));
	(void)((keycode == XK_s) && (move_backward(player, map), 1));
	(void)((keycode == XK_d) && (move_left(player, map), 1));
	(void)((keycode == XK_a) && (move_right(player, map), 1));
	(void)((keycode == XK_Left) && (rotate_left(player, 0.1), 1));
	(void)((keycode == XK_Right) && (rotate_right(player, 0.1), 1));
	(void)((keycode == XK_Escape) && (destroy_app(get_mlx()), 1));
	
	return (1);
}

void	init_hook(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx_hook(mlx->win_ptr, ON_DESTROY, 0, destroy_app, mlx);
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, &keyboard_manager, NULL);
	mlx_loop_hook(mlx->mlx_ptr, &update, NULL);
}

/*
**void	toggle_mouselock(t_player *player)
**{
**	if (player->is_mouselock)
**		player->is_mouselock = 0;
**	else
**		player->is_mouselock++;
**}
**(void)((keycode == XK_Escape) && (toggle_mouselock(player), 1));
**int	mouse_manager(void *param)
**{
**	static t_vec2	center;
**	int				x;
**	int				y;
**	t_vec2			dir;
**	t_mlx			*mlx;
**
**	center = (t_vec2){WIDTH / 2, HEIGHT / 2};
**	(void)param;
**	if (!get_player()->is_mouselock)
**		return (1);
**	mlx = get_mlx();
**	mlx_mouse_get_pos(mlx->mlx_ptr, mlx->win_ptr, &x, &y);
**	dir = vec2_substract((t_vec2){x, y}, center);
**	if (dir.x > 0)
**		rotate_right(get_player(), 1.0e-2);
**	else if (dir.x < 0)
**		rotate_left(get_player(), 1.0e-2);
**	mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, (int)center.x, (int)center.y);
**	return (1);
**	mlx_hook(mlx->win_ptr, MotionNotify, PointerMotionMask, &mouse_manager,
**		NULL);
**}
*/