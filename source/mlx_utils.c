/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:23:25 by wayden            #+#    #+#             */
/*   Updated: 2024/11/12 21:29:04 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** get_pixel_at - Retrieves the memory address of a pixel in an image.
** @img: Pointer to the image structure.
** @x: The x-coordinate of the pixel.
** @y: The y-coordinate of the pixel.
**
** This function calculates the memory address of a pixel at position (x, y)
** in the given image. It uses the image's address, line length, and bits 
** per pixel to determine the location. The address is cast to an 
** `unsigned int *` so the pixel color can be easily accessed or modified.
**
** Returns: Pointer to the pixel at (x, y).
*/
unsigned int	*get_pixel_at(t_img *img, int x, int y)
{
	return ((unsigned int *)(img->addr + (y * img->line_length + x \
				* (img->bits_per_pixel / 8))));
}

/**
** get_pixel_color - Retrieves the color of a pixel in an image.
** @img: Pointer to the image structure.
** @x: The x-coordinate of the pixel.
** @y: The y-coordinate of the pixel.
**
** This function uses `get_pixel_at` to find the pixel at (x, y) and
** dereferences it to get its color value as an `unsigned int`.
**
** Returns: The color of the pixel at (x, y).
*/
unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	return (*get_pixel_at(img, x, y));
}

/**
** ver_line_x - Draws a vertical line on an image with a specified color.
** @img: Pointer to the image structure.
** @color: The color to apply to the line.
** @r: Range struct specifying the start and end y-coordinates of the line.
** @x: The x-coordinate where the line is drawn.
**
** This function draws a vertical line at the x-coordinate `x`, from y-coordinate
** `r.start` to `r.end`, with each pixel set to `color`. It iterates from 
** `r.start` to `r.end`, setting each pixel along the way.
**
** Returns: None
*/
void	ver_line_x(t_img *img, t_color color, t_range r, int x)
{
	int				y;
	unsigned int	*actual_pixel;

	y = r.start;
	while (y < r.end)
	{
		actual_pixel = get_pixel_at(img, x, y);
		*actual_pixel = color.hex;
		y++;
	}
}

/**
** tex_ver_line_x - Draws a textured vertical line on an image.
** @img: Pointer to the image structure where the line is drawn.
** @texture: Pointer to the texture to be applied.
** @r: Range struct specifying the start and end y-coordinates of the line.
** @x: The x-coordinate where the line is drawn.
**
** This function applies a texture to a vertical line at x-coordinate `x`.
** It calculates the texture's y-coordinate with each step, adjusting based
** on the specified line height. It samples the texture at each step and
** applies the pixel color to `img`. 
**
** Returns: None
*/
void	tex_ver_line_x(t_img *img, t_xpm_texture *texture, t_range r, int x)
{
	int				y;
	double			step;
	double			texpos;
	unsigned int	*actual_pixel;
	t_color			texture_pixel;

	step = 1.0 * texture->height / texture->lineheight;
	texpos = (r.start - HEIGHT / 2 + texture->lineheight / 2) * step;
	y = r.start;
	while (y < r.end)
	{
		actual_pixel = get_pixel_at(img, x, y);
		texture->pos_in.y = (int)texpos & (texture->height - 1);
		texpos += step;
		texture_pixel.hex = (\
			get_pixel_color(&texture->img, (int)texture->pos_in.x, \
				(int)texture->pos_in.y));
		*actual_pixel = texture_pixel.hex;
		y++;
	}
}

// void tex_ver_line_x(t_img *img, t_xpm_texture *texture, t_range r, int x)
// {
// 	int y;
// 	unsigned int *actual_pixel;
// 	t_color texture_pixel;

// 	y = r.start;
// 	while(y < r.end)
// 	{
// 		actual_pixel = get_pixel_at(img, x, y);
// 		texture->pos_in.y =
// 		cross_product(y - r.start, r.end - r.start,  texture->height);
// 		if(DEBUG)
// 			printf("\n\ntexture->pos_in.x = %d, texture->pos_in.y =
//					%d\n\n",(int)texture->pos_in.x, (int)texture->pos_in.y);
// 		texture_pixel.hex =
// 		get_pixel_color(&texture->img, (int)texture->pos_in.x,
//			(int)texture->pos_in.y);
// 		*actual_pixel = texture_pixel.hex;
// 		y++;
// 	}
// }