/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:21:39 by wayden            #+#    #+#             */
/*   Updated: 2024/10/28 08:35:02 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

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
	player->camera = vec2_perpendicular(player->direction, LEFT);
}
