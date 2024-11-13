/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 03:07:08 by wayden            #+#    #+#             */
/*   Updated: 2024/11/12 18:34:09 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

int	destroy_app(t_mlx *mlx)
{
	destroy_textures(get_texture(0), mlx);
	mlx_destroy_image(mlx->mlx_ptr, get_img()->img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free_struct_map(get_mapdata(NULL));
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mapdata	*data;

	if (argc != 2)
		error_manager(ERRCODE_NB_ARGS, NULL);
	if (extension_check(argv[1]))
		error_manager(ERRCODE_ARG_EXT, NULL);
	sget_init(INIT_COUNT - 1, RESETALL);
	data = get_mapdata(argv[1]);
	get_player();
	get_texture(0);
	init_hook();
	mlx_loop(get_mlx()->mlx_ptr);
	free_struct_map(data);
	return (0);
}
