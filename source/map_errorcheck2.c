/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errorcheck2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:59:19 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 02:17:35 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

static int	check_colors(t_mapdata *data)
{
	if (data->c_ceiling.a + data->c_floor.a)
		return (ERRCODE_COLOR_INVALID);
	return (0);
}

static int	check_textures(t_mapdata *data)
{
	int	fd;

	fd = open(data->path[WE], O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_WEST);
	close(fd);
	fd = open(data->path[EA], O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_EAST);
	close(fd);
	fd = open(data->path[SO], O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_SOUTH);
	close(fd);
	fd = open(data->path[NO], O_RDONLY);
	if (fd == -1)
		return (ERRCODE_PATH_NORTH);
	close(fd);
	return (0);
}

int check_keycount(t_mapdata *data)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if(data->keycount[i] > 1 || data->keycount[i++] == 0)
			return (ERRCODE_KEYCOUNT + i); 
	}
	return (0);
}

int	check_for_errors(t_mapdata *data)
{
	int			i;
	int			error;
	static int	(*checkers[4])(t_mapdata *) =\
		{check_colors, check_map, check_keycount, check_textures};

	error = 0;
	i = -1;
	while (++i < 4)
	{
		error = checkers[i](data);
		if (error)
			return (error);
	}
	return (0);
}

int	extension_check(char *line)
{
	int	len;

	len = ft_strlen(line);
	return (line[len - 1] != 'b' || line[len - 2] != 'u' || line[len - 3] != 'c'
		|| line[len - 4] != '.');
}