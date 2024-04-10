/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:44:54 by wayden            #+#    #+#             */
/*   Updated: 2024/03/27 23:21:17 by wayden           ###   ########.fr       */
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
