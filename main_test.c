/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 03:07:08 by wayden            #+#    #+#             */
/*   Updated: 2024/03/19 17:36:35 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			printf("%d ", data->map[y][x]);
		printf("\n");			
	}
	printf("data path ea: %s\n", data->path_ea);
	printf("data path no: %s\n", data->path_no);
	printf("data path so: %s\n", data->path_so);
	printf("data path we: %s\n", data->path_we);
	printf("color floor : %d, %d, %d\n", data->color_floor.r,data->color_floor.g,data->color_floor.b);
	printf("color ceilling : %d, %d, %d\n", data->color_ceiling.r,data->color_ceiling.g,data->color_ceiling.b);
}

int main( void )
{
	t_mapdata data;
	int fd;
	
	data = (t_mapdata){NULL, 0, 0, NULL,NULL,NULL,NULL,"map.cub",(t_color){0,0,0},(t_color){0,0,0}};
	fd = open(data.name_file, O_RDONLY);
	cub_parser(fd, &data);
	debug_print_data(&data);
	free_struct_map(&data);
	close(fd);
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


	