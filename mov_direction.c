/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:21:20 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 19:57:32 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

void collision_check(t_vec2 target, t_vec2 to_check, t_player *player, \
int **map)
{
	//potentiellement besoin d'ajouter un check afin de verifier si
	//on on atterit en dehors de la map ce qui peut eviter des probleme
	// en cas de vitesse trop elever
	if(map[(int)player->pos.y][(int)to_check.x] != 1)
		player->pos.x = target.x;
	if(map[(int)to_check.y][(int)player->pos.x] != 1)
		player->pos.y = target.y;
}

void move_forward(t_player *player, int **map)
{
	t_vec2 target;
	t_vec2 to_check;
	t_vec2 direction_speed;
	
	direction_speed = vec2_speed(player->direction, player->speed);
	target = vec2_addition(player->pos, direction_speed);
	to_check = vec2_addition(target, direction_speed);
	collision_check(target, to_check, player, map);
}

void move_backward(t_player *player, int **map)
{
	t_vec2 target;
	t_vec2 to_check;
	t_vec2 direction_speed;
	
	direction_speed = vec2_speed(player->direction, player->speed);
	target = vec2_substract(player->pos, direction_speed);
	to_check = vec2_substract(target, direction_speed);
	collision_check(target, to_check, player, map);
}

void move_left(t_player *player, int **map)
{
	t_vec2 target;
	t_vec2 to_check;
	t_vec2 perp_vect;
	
	perp_vect = vec2_perpendicular(player->direction, LEFT);
	perp_vect = vec2_speed(perp_vect, player->speed);
	target = vec2_addition(player->pos, perp_vect);
	to_check = vec2_addition(target, perp_vect);
	collision_check(target, to_check, player, map);
}

void move_right(t_player *player, int **map)
{
	t_vec2 target;
	t_vec2 to_check;
	t_vec2 perp_vect;

	perp_vect = vec2_perpendicular(player->direction, RIGHT);
	perp_vect = vec2_speed(perp_vect, player->speed);
	target = vec2_addition(player->pos, perp_vect);
	to_check = vec2_addition(target, perp_vect);
	collision_check(target, to_check, player, map);
}

void rotate_left(t_player *player)
{
	double tmp = player->direction.x;
    player->direction.x = player->direction.x * cos(-player->speed)\
	- player->direction.y * sin(-player->speed);
    player->direction.y = tmp * sin(-player->speed)\
	+ player->direction.y * cos(-player->speed);	
	player->camera = vec2_perpendicular(player->direction, LEFT);
}


void rotate_right(t_player *player)
{
	double tmp = player->direction.x;
    player->direction.x = player->direction.x * cos(player->speed)\
	- player->direction.y * sin(player->speed);
    player->direction.y = tmp * sin(player->speed)\
	+ player->direction.y * cos(player->speed);
	player->camera = vec2_perpendicular(player->direction, LEFT);
}
