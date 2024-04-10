/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:34:32 by wayden            #+#    #+#             */
/*   Updated: 2024/03/27 18:37:35 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

bool	sget_init(t_init index, int set)
{
	static bool	init_tab[7] = {false, false, false, false, false, false, false};

	if (set == REFRESH)
		init_tab[index] = false;
	else if (set == SET)
		init_tab[index] = true;
	else if (set == REFRESHALL)
		ft_memset(&init_tab, false, sizeof(bool) * 7);
	return (init_tab[index]);
}


t_mlx *get_mlx()
{
	static t_mlx mlx;
	if (!sget_init(MLX, NOP) && sget_init(MLX, SET))
	{
		mlx.mlx_ptr = mlx_init();
        mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	}
	return &mlx;
}

t_img *get_img()
{
    static t_img img;

    if (!sget_init(IMG, NOP) && sget_init(IMG, SET)) 
    {
        img.img = mlx_new_image(get_mlx(1)->mlx_ptr, WIDTH, HEIGHT);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
        &img.line_length, &img.endian);
    }
    return &img;
}

