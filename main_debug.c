/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:44:54 by wayden            #+#    #+#             */
/*   Updated: 2024/04/12 05:39:42 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//debug function do not compile final project with it
#include "headers/includes.h"
#include <stdio.h>

void debug_print_data(t_mapdata *data)
{
	int y = -1;
	int x = -1;
	printf("size(x) = %d\n", data->size);
	printf("length(y) = %d\n", data->length);
	while(++y < data->length)
	{
		x = -1;
		printf("line [%02d]  ",y);
		while(data->map[y] != NULL && ++x < data->size)
		{
			if (data->map[y][x] == 1)
				printf(COLOR_CYAN"\u25A0 "COLOR_RESET);
			else if (data->map[y][x] == 0)
				printf(COLOR_WHITE"\u25A0 "COLOR_RESET);
			else if (data->map[y][x] >= N && data->map[y][x] <= E)
				printf(COLOR_GREEN"\u25A0 "COLOR_RESET);
			else
				printf(COLOR_BLACK"\u25A0 "COLOR_RESET);
		}
		printf("\n");			
	}
	printf("data path ea: %s\n", data->path_ea);
	printf("data path no: %s\n", data->path_no);
	printf("data path so: %s\n", data->path_so);
	printf("data path we: %s\n", data->path_we);
	printf("color floor : %d, %d, %d\n", data->color_floor.r,data->color_floor.g,data->color_floor.b);
	printf("color ceilling : %d, %d, %d\n", data->color_ceiling.r,data->color_ceiling.g,data->color_ceiling.b);
}


void debug_print_player(t_player *player)
{
	printf("player.pos.x = %f\n, player.pos.y = %f\n\
player.dir.x = %f\n, player.dir.y = %f\n\
player.Camera.x = %f\n, player.camera.y = %f\n\
player.speed = %f\n", player->pos.x, player->pos.y, player->direction.x, player->direction.y\
, player->camera.x, player->camera.y, player->speed);
}


int main( int argc, char **argv )
{
	t_mapdata *data;
	t_player  *player;
	if (argc != 2)
		error_manager(ERRCODE_NB_ARGS, NULL);
	if (extension_check(argv[1]))
		error_manager(ERRCODE_ARG_EXT, NULL);
	sget_init(INIT_COUNT - 1, RESETALL);
	data = get_mapdata(argv[1]);
	player = get_player();
	if(DEBUG)\
	{
		debug_print_data(data);
		debug_print_player(player);
	}
	init_hook();
	mlx_loop(get_mlx()->mlx_ptr);
	free_struct_map(data);
	
	return (0);
}