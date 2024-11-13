/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:53:39 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 02:06:12 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

void	free_struct_map(t_mapdata *data)
{
	int	y;

	y = -1;
	while (++y < data->length)
		free(data->map[y]);
	free(data->map);
	free(data->char_map);
	y = -1;
	while (++y < TEXTURES_COUNT)
		free(data->path[y]);
}

static void	print_error(const char *error)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error, ft_strlen(error));
}

/**
** error_manager - Manages errors by printing a message and freeing memory.
** @error_code: Error code corresponding to a message in `errors[]`.
** @data: Pointer to the map data structure (`t_mapdata`).
**
** This function displays an error message based on `error_code` and
** frees allocated memory as needed. It checks error codes to
** ensure only necessary allocations are freed. For critical errors,
** the function calls `exit` to terminate execution.
**
** - errors[] : Static array of error messages used for each code.
** - ERRCODE_TEXTURES : Error code requiring app destruction.
** - ERRCODE_NB_ARGS : Threshold after which `free_struct_map` is called.
*/
void	error_manager(int error_code, t_mapdata *data)
{
	static const char	*errors[] = {NULL, ERR_TEXTURES, ERR_NOFILE, \
	ERR_ARG_EXT, \
	ERR_NB_ARGS, ERR_PATH_EAST, ERR_PATH_WEST, ERR_PATH_NORTH, ERR_PATH_SOUTH, \
	ERR_COLOR_INVALID, ERR_MAP_NOSPAWN, ERR_MAP_UNCLOSED, ERR_MAP_TOOMUCHSPAWM, \
	ERR_MAP_LINE, ERR_MAP_UNWANTED_CHAR, ERR_KEYCOUNT_NO, ERR_KEYCOUNT_SO,\
	ERR_KEYCOUNT_WE, ERR_KEYCOUNT_EA, ERR_KEYCOUNT_F, ERR_KEYCOUNT_C};

	print_error(errors[error_code]);
	if (error_code == ERRCODE_TEXTURES)
		destroy_app(get_mlx());
	else if (error_code > ERRCODE_NB_ARGS)
		free_struct_map(data);
	if (sget_init(TEXTURES, ISINIT))
		destroy_textures(get_texture(0), get_mlx());
	exit(error_code);
}
