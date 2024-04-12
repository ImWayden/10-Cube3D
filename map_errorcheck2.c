/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errorcheck2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:59:19 by wayden            #+#    #+#             */
/*   Updated: 2024/04/12 00:08:01 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

static int check_colors(t_mapdata *data)
{
	if(data->color_ceiling.a + data->color_floor.a)
		return(ERRCODE_COLOR_INVALID);
	return (0);
}

static int check_textures(t_mapdata *data)
{
	int fd;

	fd = open(data->path_we, O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_WEST);
	close(fd);
	fd = open(data->path_ea, O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_EAST);
	close(fd);
	fd = open(data->path_so, O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_SOUTH);
	close(fd);
	fd = open(data->path_no, O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_NORTH);
	close(fd);
	return (0);
}

int check_for_errors(t_mapdata *data)
{
	static int (*checkers[3])(t_mapdata *) =\
	{check_colors, check_textures, check_map};
	int			i;
	int			error;

	error = 0;
	i = -1;
	while (++i < 3)
	{
		error = checkers[i](data);
		if (error)
			return error;
	}
	return (0);
}

int extension_check(char *line)
{
	int len;

	len = ft_strlen(line);
	return (line[len-1] != 'b'\
	|| line[len - 2] != 'u'\
	|| line[len - 3] != 'c'\
	|| line[len - 4] != '.');
}