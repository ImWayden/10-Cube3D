/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:33:35 by wayden            #+#    #+#             */
/*   Updated: 2024/11/12 19:47:36 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** ft_abs_dbl - Computes the absolute value of a double.
** @x: The number whose absolute value is to be computed.
**
** This function returns the absolute value of the given double, ensuring 
** that the value is always non-negative.
*/
double	ft_abs_dbl(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

/**
** set_step - Sets the step values for raycasting, based on the ray direction 
** and the player's position.
** @data: The ray data structure containing ray direction, step, and side 
** distance.
** @player_pos: The player's position in the current direction.
** @map_pos: The map position corresponding to the player's position.
**
** This function calculates the step direction and the initial side distance 
** for the ray, depending on whether the ray direction is positive or 
** negative.
*/
void	set_step(t_raydata data, double player_pos, int map_pos)
{
	if (*data.raydir < 0)
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

/**
** trace_ray - Traces the ray through the map, determining when it hits a wall.
** @data: The map data, containing the level information and wall layout.
** @u: The ray utility structure holding ray-related data.
**
** This function updates the side distances and map coordinates, stepping 
** through the map grid until the ray hits a wall.
*/
void	trace_ray(t_mapdata data, t_rayutils *u)
{
	while (!u->hit)
	{
		if (u->side_dist.x < u->side_dist.y)
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
		if (data.map[u->map_y][u->map_x] == 1)
			u->hit++;
	}
}

/**
** set_deltadist - Sets the delta distance for each axis (x or y) based on the 
** ray direction.
** @delta_dist: The pointer to the delta distance to be set.
** @ray_dir: The direction of the ray.
**
** This function calculates the delta distance for the ray, which is used 
** in the raycasting algorithm to determine how much the ray moves per 
** step in the x or y direction.
*/
void	set_deltadist(double *delta_dist, double ray_dir)
{
	if (!ray_dir)
		*delta_dist = 1.0e+30;
	else
		*delta_dist = (1 / ft_abs_dbl(ray_dir));
}

/**
** calculate_walldist - Calculates the perpendicular distance to the wall 
** based on the side hit by the ray.
** @u: The ray utility structure containing side distance and delta distance 
** for both x and y directions.
**
** This function computes the perpendicular wall distance based on which 
** side of the grid the ray hits.
*/
void	calculate_walldist(t_rayutils *u)
{
	if (!u->side)
		u->perp_wall_dist = u->side_dist.x - u->delta_dist.x;
	else
		u->perp_wall_dist = u->side_dist.y - u->delta_dist.y;
}
