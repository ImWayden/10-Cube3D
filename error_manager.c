/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:53:39 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 11:58:11 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"


void free_struct_map(t_mapdata *data)
{
	int y;
	
	y = -1;
	while(++y < data->length)
		free(data->map[y]);
	free(data->map);
	free(data->char_map);
	y = -1;
	while(++y < TEXTURES_COUNT)
		free(data->path[y]);
}

static void print_error(const char *error)
{
	write(STDERR_FILENO,"Error\n",7);
	write(STDERR_FILENO,error, ft_strlen(error));
	//besoin d'ajouter la gestion de liberation de la memoire et autre probablement
	// a moins que je ne decidee de le faire autre part
}

void error_manager(int error_code, t_mapdata *data)
{
	static const char *errors[] = {NULL, ERR_NOFILE, ERR_ARG_EXT, ERR_NB_ARGS,\
	ERR_PATH_EAST, ERR_PATH_WEST, ERR_PATH_NORTH, ERR_PATH_SOUTH,\
	ERR_COLOR_INVALID, ERR_MAP_NOSPAWN, ERR_MAP_UNCLOSED, ERR_MAP_TOOMUCHSPAWM,\
	ERR_MAP_LINE, ERR_MAP_UNWANTED_CHAR};
	
	print_error(errors[error_code]);	
	if(error_code > ERRCODE_NB_ARGS)
		free_struct_map(data);
	exit(error_code);
}
