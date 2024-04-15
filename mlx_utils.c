/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:23:25 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 12:26:01 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

unsigned int *get_pixel_at(t_img *img, int x, int y)
{
	
	return ((unsigned int *)(img->addr + (y * img->line_length + x 
                * (img->bits_per_pixel / 8))));
}

unsigned int get_pixel_color(t_img img, int x, int y)
{
    // Calculez l'index du pixel dans le tableau d'adresses en fonction de x et y
    int index = (y * img.line_length) + (x * (img.bits_per_pixel / 8));

    // Accédez à l'adresse du pixel dans l'image et convertissez-la en unsigned int
    unsigned int color = *((unsigned int *)(img.addr + index));

    // Retournez la couleur du pixel
    return color;
}

/*
	color avec la couleur passer en parametre 
	une colone de pixel sur l'image passer en parametre
	allant de start.y a end.y
*/
void ver_line_x(t_img *img, t_color color, t_range r, int x)
{
	int y;
	unsigned int *actual_pixel;
	
	y = r.start;
	while(y < r.end)
	{
		actual_pixel = get_pixel_at(img, x, y);
		*actual_pixel = color.hex;
		y++;
	}
}

void tex_ver_line_x(t_img *img, t_xpm_texture *texture, t_range r, int x)
{
	int y;
	unsigned int *actual_pixel;
	t_color texture_pixel;

	y = r.start;
	while(y < r.end)
	{
		actual_pixel = get_pixel_at(img, x, y);
		texture->pos_in.y = \
		cross_product(y - r.start, r.end - r.start,  texture->height);
		if(DEBUG)
			printf("\n\ntexture->pos_in.x = %d, texture->pos_in.y = %d\n\n",(int)texture->pos_in.x, (int)texture->pos_in.y);
		texture_pixel.hex = \
		get_pixel_color(texture->img, (int)texture->pos_in.x, (int)texture->pos_in.y);
		*actual_pixel = texture_pixel.hex;
		y++;
	}
}