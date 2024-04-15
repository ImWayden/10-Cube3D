/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:34:32 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 12:16:55 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

bool	sget_init(t_init index, int set)
{
	static bool	init_tab[INIT_COUNT];

	if (set == RESET)
		init_tab[index] = false;
	else if (set == INIT)
		init_tab[index] = true;
	else if (set == RESETALL)
		ft_memset(&init_tab, false, sizeof(bool) * INIT_COUNT);
	return (init_tab[index]);
}


t_mlx *get_mlx()
{
	static t_mlx mlx;
	if (!sget_init(MLX, ISINIT) && sget_init(MLX, INIT))
	{
		mlx.mlx_ptr = mlx_init();
        mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	}
	return &mlx;
}



void construct_img(t_img *img)
{
    img->img = mlx_new_image(get_mlx()->mlx_ptr, WIDTH, HEIGHT);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, 
    &img->line_length, &img->endian);
}


t_img *get_img()
{
    static t_img img;

    if (!sget_init(IMG, ISINIT) && sget_init(IMG, INIT)) 
		construct_img(&img);
    return &img;
}

t_player *get_player()
{
	static t_player player;
	t_mapdata *data;
	
	if (!sget_init(PLAYER, ISINIT) && sget_init(PLAYER, INIT)) 
    {
		data = get_mapdata(NULL);	
		player.direction = data->spawndir;
		player.pos = (t_vec2){data->spawnpoint.x + 0.5, data->spawnpoint.y + 0.5};
		player.camera = vec2_perpendicular(data->spawndir);
		player.speed = 1.0;
    }
    return &player;
}

t_mapdata *get_mapdata(char *file)
{
	static t_mapdata data;
	if (!sget_init(MAP, ISINIT) && sget_init(MAP, INIT) && file) 
    {
		data.fd = open(file, O_RDONLY);
		if (data.fd == -1)
			error_manager(ERRCODE_NOFILE, NULL);
		data.name_file = file;
		cub_parser(data.fd, &data);
		close(data.fd);
	}
	return &data;
}

// void *class_tex_execute(t_img *texture, int exec, void * args[4])
// {
// 	if(exec == GET)
// 		return (texture);
// 	else if(exec == GETPIXELCOLOR)
// 		return (class_tex_getpixelcolor(texture, (int *)args[0], (int*)args[1]));
	


	
// }


void construct_texture(t_xpm_texture *t,char *path)
{
	if(DEBUG)
		printf("before addresse texture = %ld, path %s , addr %ld\n", &t, path, t->img.addr);
	t->img.img = mlx_xpm_file_to_image(get_mlx()->mlx_ptr, path,\
	&t->width, &t->height);
    t->img.addr = mlx_get_data_addr(t->img.img,\
	&t->img.bits_per_pixel, &t->img.line_length, &t->img.endian);
	if(DEBUG)
		printf("path = %s, %lld\n", path, t->img.addr);
}

t_xpm_texture *get_texture(int index/*,int exec, void *args[4]*/)
{
	static t_xpm_texture	textures[TEXTURES_COUNT];
	t_mapdata				*data;
	int						i;
	
	if (!sget_init(TEXTURES, ISINIT) && sget_init(TEXTURES, INIT)) 
    {
		data = get_mapdata(NULL);
		i = -1;
		while(++i < TEXTURES_COUNT)
		{
			if(DEBUG)
				printf("before addresse texture = %ld, path %s , addr %ld\n", &textures[i], data->path[i], textures[i].img.addr);
			construct_texture(&textures[i], data->path[i]);
			if(DEBUG)
				printf("after addresse texture = %ld, path %s, addr %ld \n\n\n", &textures[i], data->path[i], textures[i].img.addr);
		}

	}
	return (&textures[index]);
	// return (texclass_execute(&textures[index], exec, args));
}


