/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:23:25 by wayden            #+#    #+#             */
/*   Updated: 2024/04/11 08:41:48 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

void ver_line_x(t_img *img, t_lineinfo line)
{
	int y;

	y = line.start;
	while(y < line.end)
	{
		*(unsigned int *)(img->addr + (y * img->line_length + line.x 
                * (img->bits_per_pixel / 8))) = line.color.hex;
		y++;
	}
}