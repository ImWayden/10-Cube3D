/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logic_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:33:35 by wayden            #+#    #+#             */
/*   Updated: 2024/04/10 17:00:39 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

void set_step(t_raydata data, double player_pos, int map_pos)
{
	if(*data.raydir < 0)
	{
		*data.step = -1;
		*data.sidedist = (player_pos - map_pos) * *data.deltadist;
	}
	else
	{
		*data.step = 1;
		*data.sidedist = (map_pos + 1.0 - player_pos) * *data.deltadist;
	}
}

void trace_ray(t_mapdata data, t_rayutils *u)
{
	while(!u->hit)
	{
		if(u->side_dist.x < u->side_dist.y)
		{
			u->side_dist.x += u->delta_dist.x;
      		u->map_x += u->step_x;
     		u->side = 0;
		}
		else
		{
			u->side_dist.y += u->delta_dist.y;
      		u->map_y += u->step_y;
     		u->side = 1;	
		}
		if(data.map[u->map_x][u->map_y] == 1)
			u->hit++;
	}
}

void cast_ray(t_player player, t_mapdata data, t_rayutils *u) 
{
	u->hit = 0;
	u->ray_dir.x = player.direction.x + player.Camera.x * u->camera_x;
	u->ray_dir.y = player.direction.y + player.Camera.y * u->camera_x;
	u->map_x = (int)player.pos.x;
	u->map_y = (int)player.pos.y;
	set_step((t_raydata){&u->delta_dist.x, &u->side_dist.x,\
	&u->ray_dir.x,&u->step_x}, player.pos.x, u->map_x);
	set_step((t_raydata){&u->delta_dist.y, &u->side_dist.y,\
	&u->ray_dir.y,&u->step_y}, player.pos.y, u->map_y);
	trace_ray(data, u);
	
}

void update_raycast(t_player player, t_mapdata data)
{
	t_rayutils	u;
	int			x;
	
	x = -1;
	while (++x < WIDTH)
	{
		u.camera_x = 2 * x / (double)WIDTH - 1;
		cast_ray(player, data, &u);
		print_line();
	}
}


