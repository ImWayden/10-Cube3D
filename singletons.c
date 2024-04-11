/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:34:32 by wayden            #+#    #+#             */
/*   Updated: 2024/04/11 11:03:59 by wayden           ###   ########.fr       */
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
	if (!sget_init(PLAYER, ISINIT) && sget_init(PLAYER, INIT)) 
    {
		player.Camera = (t_vec2){0,0};
		player.direction = (t_vec2){0,0};
		player.pos = (t_vec2){0,0};
		player.speed = 0.0;
    }
    return &player;
}
