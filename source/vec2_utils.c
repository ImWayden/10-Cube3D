/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: therodri <therodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:21:59 by wayden            #+#    #+#             */
/*   Updated: 2024/04/21 17:47:35 by therodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

t_vec2	vec2_perpendicular(t_vec2 vector, int dir)
{
	if (dir == LEFT)
		return ((t_vec2){-vector.y, vector.x});
	return ((t_vec2){vector.y, -vector.x});
}

t_vec2	vec2_addition(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x + v2.x, v1.y + v2.y});
}

t_vec2	vec2_substract(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x - v2.x, v1.y - v2.y});
}

t_vec2	vec2_speed(t_vec2 vector, double speed)
{
	return ((t_vec2){vector.x * speed, vector.y * speed});
}
