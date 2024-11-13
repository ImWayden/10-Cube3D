/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errorcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:55:42 by wayden            #+#    #+#             */
/*   Updated: 2024/11/12 18:33:26 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

static int	ft_isvoid(int actual)
{
	return ((actual == 0 || (actual >= N && actual < SP)));
}

static int	check_wall(t_mapdata *data, int y, int x, int actual)
{
	if ((y == 0 || x == 0 || y == data->length || x == data->size)
		&& ft_isvoid(actual))
		return (ERRCODE_MAP_UNCLOSED);
	if (actual == SP && \
		((x < data->size - 1 && ft_isvoid(data->map[y][x + 1])) || (x > 0
			&& ft_isvoid(data->map[y][x - 1])) || (y < data->length - 1 \
			&& ft_isvoid(data->map[y + 1][x])) || (y > 0 \
			&& ft_isvoid(data->map[y - 1][x]))))
		return (ERRCODE_MAP_UNCLOSED);
	return (0);
}

static int	check_char(int c, int *nb_spawn, t_mapdata *data, t_vec2 coords)
{
	if (c >= N && c <= E)
	{
		if (++*nb_spawn > 1)
			return (ERRCODE_MAP_TOOMUCHSPAWM);
		else
		{
			if (c == N)
				data->spawndir = (t_vec2){0, -1};
			if (c == S)
				data->spawndir = (t_vec2){0, 1};
			if (c == W)
				data->spawndir = (t_vec2){-1, 0};
			if (c == E)
				data->spawndir = (t_vec2){1, 0};
			data->spawnpoint = coords;
		}
	}
	if (c == -1)
		return (ERRCODE_MAP_UNWANTED_CHAR);
	return (0);
}

int	check_map(t_mapdata *data)
{
	int	y;
	int	x;
	int	error;
	int	spawn;

	y = -1;
	x = -1;
	error = 0;
	spawn = 0;
	while (++y < data->length)
	{
		x = -1;
		while (++x < data->size)
		{
			error = check_char(data->map[y][x], &spawn, data, (t_vec2){x, y});
			if (error)
				return (error);
			error = check_wall(data, y, x, data->map[y][x]);
			if (error)
				return (error);
		}
	}
	if (!spawn)
		error = ERRCODE_MAP_NOSPAWN;
	return (error);
}
