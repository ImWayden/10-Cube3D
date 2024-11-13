/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:57:57 by therodri          #+#    #+#             */
/*   Updated: 2024/11/12 19:37:55 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** construct_img - Creates a new image using MinilibX and stores its data.
** @img: A pointer to the t_img structure that will hold the created image.
**
** This function creates a new image 
** with dimensions defined by WIDTH and HEIGHT
** using the `mlx_new_image` function from MinilibX. 
** The image data is stored in the provided `img` structure.
*/
void	construct_img(t_img *img)
{
	img->img = mlx_new_image(get_mlx()->mlx_ptr, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

/**
** get_img - Returns a singleton instance of t_img, initializing it if needed.
** 
** This function ensures that only one instance of t_img is used throughout
** the program. It calls `construct_img` to initiliaze the instance.
** to create a new image. It then returns a pointer to the initialized image.
**
** The img is the one that will be printed to the screen using the MiniLibX 
** 
** Returns: A pointer to the singleton t_img instance.
*/
t_img	*get_img( void )
{
	static t_img	img;

	if (!sget_init(IMG, ISINIT) && sget_init(IMG, INIT))
		construct_img(&img);
	return (&img);
}

/**
** destroy_textures - Destroys all textures loaded into memory.
** @t: The array of t_xpm_texture structures containing 
** the textures to be destroyed.
** @mlx: A pointer to the t_mlx instance for the MinilibX context.
** 
** This function iterates over the array of textures 
** and calls `mlx_destroy_image`
** to free the memory allocated for each texture image that has been loaded 
** (i.e., whose `img.addr` are not NULL).
*/
void	destroy_textures(t_xpm_texture *t, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_COUNT && t[i].img.addr != NULL)
		mlx_destroy_image(mlx->mlx_ptr, t[i].img.img);
}

/**
** construct_texture - Loads a texture from a given path and stores it in a t_xpm_texture.
** @t: The t_xpm_texture structure where the texture will be stored.
** @path: The path to the texture file (usually a .xpm file).
**
** This function loads a texture from a file using `mlx_xpm_file_to_image`. If the texture
** is successfully loaded, the function retrieves the texture data and stores it in the provided
** `t_xpm_texture` structure. If loading the texture fails, it calls `error_manager` to handle
** the error.
*/
void	construct_texture(t_xpm_texture *t, char *path)
{
	t->img.img = mlx_xpm_file_to_image(get_mlx()->mlx_ptr, path, &t->width,
			&t->height);
	if (t->img.img != NULL)
	{
		t->img.addr = mlx_get_data_addr(t->img.img,
				&t->img.bits_per_pixel,
				&t->img.line_length,
				&t->img.endian);
	}
	else
		return (error_manager(ERRCODE_TEXTURES, get_mapdata(NULL)));
}

/**
** get_texture - Returns a singleton instance of a texture by index.
** @index: The index of the texture to retrieve.
**
** This function manages the loading of all textures. It initializes the textures
** if they haven't been loaded already, calling `construct_texture` for each one.
** It returns a pointer to the texture at the specified index in the textures array.
** 
** Returns: A pointer to the texture at the specified index.
*/
t_xpm_texture	*get_texture(int index)
{
	static t_xpm_texture	textures[TEXTURES_COUNT];
	t_mapdata				*data;
	int						i;

	if (!sget_init(TEXTURES, ISINIT) && sget_init(TEXTURES, INIT))
	{
		data = get_mapdata(NULL);
		i = -1;
		while (++i < TEXTURES_COUNT)
			construct_texture(&textures[i], data->path[i]);
	}
	return (&textures[index]);
}
