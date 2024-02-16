/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:55:42 by wayden            #+#    #+#             */
/*   Updated: 2024/02/15 23:42:42 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

static int ft_isvoid(int actual)
{
	return ((actual == 0 || (actual >= N && actual < SP)));
}

static int check_wall(t_mapdata *data, int y, int x, int actual)
{
	if((y == 0 || x == 0 || y == data->length || x == data->size )\
	 && ft_isvoid(actual))
			return (ERRCODE_MAP_UNCLOSED);
	if(actual == SP &&\
	((x < data->size - 1 && ft_isvoid(data->map[y][x + 1]))\
	|| (x > 0 && ft_isvoid(data->map[y][x - 1]))\
	|| (y < data->length - 1 && ft_isvoid(data->map[y + 1][x]))\
	|| (y > 0 && ft_isvoid(data->map[y - 1][x]))))
			return (ERRCODE_MAP_UNCLOSED);
	return (0);	
}

static int check_char(int c, t_cubvar *vars)
{
	if(c == N && ++vars->no > 1)
		return (ERRCODE_MAP_TOOMUCHSPAWM);
	if(c == S && ++vars->so > 1)
		return (ERRCODE_MAP_TOOMUCHSPAWM);
	if(c == E && ++vars->ea > 1)
		return (ERRCODE_MAP_TOOMUCHSPAWM);
	if(c == W && ++vars->we > 1)
		return (ERRCODE_MAP_TOOMUCHSPAWM);
	return(0);
}

int check_map(t_mapdata *data)
{
	int			y;
	int			x;
	int			error;
	t_cubvar	vars;
	
	y = -1;
	x = -1;
	error = 0;
	vars = (t_cubvar){0, 0, 0, 0};
	while(++y < data->length)
	{
		x = -1;
		while(++x < data->size)
		{
			error = check_char(data->map[y][x], &vars);
			if (error)
				return (error);
			error = check_wall(data, y, x, data->map[y][x]);
			if (error)
				return (error);
		}
	}
	if (!vars.ea && !vars.no && !vars.so && !vars.we)
		error = ERRCODE_MAP_NOSPAWN;
	return (error);
}