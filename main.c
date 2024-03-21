/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:50:40 by wayden            #+#    #+#             */
/*   Updated: 2024/03/20 21:27:22 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	void *mlx_ptr;
	void *mlx_win;


	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr,1920,1080,"Cube3D");
	mlx_loop(mlx_ptr);

	return (0);	
}

int update(void *param)
{

}

static int keyboard_manager(int keycode, void *param)
{
	
}

static int mouse_manager(int keycode, void *param)
{

}


int	destroy_app(t_mlx *mlx)
{
    mlx_destroy_image(mlx->mlx_ptr, get_img(1)->img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
	return (0);
}

void init_hook(void)
{
    t_mlx *mlx;
    mlx = get_mlx(1);
    mlx_mouse_hook(mlx->win_ptr, &mouse_manager, NULL);
    mlx_key_hook(mlx->win_ptr, &keyboard_manager, NULL);
    mlx_hook(mlx->win_ptr, 17, 0, destroy_app, mlx);
    mlx_loop_hook(mlx->mlx_ptr, &update, NULL);
}

//mlx_mouse_get_pos