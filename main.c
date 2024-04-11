/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 03:07:08 by wayden            #+#    #+#             */
/*   Updated: 2024/04/11 12:54:46 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"
#include <stdio.h>

int main( void )
{
	t_mapdata data;
	int fd;
	
	data = (t_mapdata){NULL, 0, 0, NULL, NULL,NULL,NULL,NULL,"map.cub",(t_color){0},(t_color){0},(t_spawnpoints){{0,0},{0,0},{0,0},{0,0}}};
	fd = open(data.name_file, O_RDONLY);
	sget_init(INIT_COUNT - 1, RESETALL);
	cub_parser(fd, &data);
	close(fd);
	// init_hook();
	// mlx_loop(get_mlx()->mlx_ptr);
	free_struct_map(&data);
	
	return (0);
}

	// //debug
	// printf("debug\n");	
	// for (int y = 0; y < size; y++)
	// 	printf("%d ",map[j][y]);
	// //debug
	// //debug
	// printf("%s",line); //debug
	// //
	//printf("length = %d, size = %d x = %d y = %d \n",data->length, data->size, x,y);
	/*
		
		to debug : get_color not working properly and not storing coolor components in the good variable for some reason
		
	*/\


	