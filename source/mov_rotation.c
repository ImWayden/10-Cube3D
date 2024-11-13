/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:21:39 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 03:41:15 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

double deg_to_rad(double angle)
{
	return ((angle) * M_PI / 180.0);
}

void fix_rotation(t_player *player)
{
	double angle;
	
	angle = atan2(player->direction.y, player->direction.x);

	if (fabs(angle - deg_to_rad(0)) < TOLERANCE) {
		player->direction.x = 1;
		player->direction.y = 0;
	} else if (fabs(angle - deg_to_rad(90)) < TOLERANCE) {
		player->direction.x = 0;
		player->direction.y = 1;
	} else if (fabs(angle - deg_to_rad(180)) < TOLERANCE || fabs(angle + deg_to_rad(180)) < TOLERANCE) {
		player->direction.x = -1;
		player->direction.y = 0;
	} else if (fabs(angle - deg_to_rad(270)) < TOLERANCE || fabs(angle + deg_to_rad(90)) < TOLERANCE) {
		player->direction.x = 0;
		player->direction.y = -1;
	}
}

/*
	la rotation est un peu plus complexe que simplement se mouvoir
	puisque l'on dois changer le vecteur de direction (player.dir)
	et ensuite on recréer le vecteur de camera perpendiculaire
	https://fr.wikipedia.org/wiki/Rotation_vectorielle
*/
void	rotate_left(t_player *player, double speed)
{
	double	tmp;

	tmp = player->direction.x;
	player->direction.x = player->direction.x * cos(-speed)
		- player->direction.y * sin(-speed);
	player->direction.y = tmp * sin(-speed) + player->direction.y
		* cos(-speed);
	fix_rotation(player);
	player->camera = vec2_perpendicular(player->direction, LEFT);
}

void	rotate_right(t_player *player, double speed)
{
	double	tmp;

	tmp = player->direction.x;
	player->direction.x = player->direction.x * cos(speed)
		- player->direction.y * sin(speed);
	player->direction.y = tmp * sin(speed) + player->direction.y
		* cos(speed);
	fix_rotation(player);
	player->camera = vec2_perpendicular(player->direction, LEFT);
}

