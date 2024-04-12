/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:34:32 by wayden            #+#    #+#             */
/*   Updated: 2024/04/12 05:47:10 by wayden           ###   ########.fr       */
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

t_img *get_img()
{
    static t_img img;

    if (!sget_init(IMG, ISINIT) && sget_init(IMG, INIT)) 
    {
        img.img = mlx_new_image(get_mlx(1)->mlx_ptr, WIDTH, HEIGHT);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
        &img.line_length, &img.endian);
    }
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
	static t_mapdata data = {NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL,\
		NULL, (t_color){0}, (t_color){0}, (t_vec2){0,0}, (t_vec2){0,0}};
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

