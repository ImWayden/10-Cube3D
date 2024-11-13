/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:31:27 by wayden            #+#    #+#             */
/*   Updated: 2024/11/12 21:39:17 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** maplength - Calculates the length of a line and checks for unwanted characters.
** @line: The line to check.
**
** This function checks each character in the line to ensure it is valid.
** If any invalid character is found, it returns -1. Otherwise, it returns
** the length of the line, excluding any newline character at the end.
**
** Returns: The length of the line if valid, -1 if invalid.
*/
static int	maplength(char *line)
{
	int	i;
	int	error;

	i = -1;
	error = ft_isvalid(line[++i]);
	while (error)
		error = ft_isvalid(line[++i]);
	if (line[i] && line[i] != '\n')
		return (-1);
	return (i);
}

/**
** norme_1 - Maps characters in the line to their corresponding map values.
** @line: The current line being parsed.
** @ret: The array where the parsed values will be stored.
** @i: The current index in the line.
**
** This function interprets specific characters as map elements and assigns
** values to each in the `ret` array. Walls are mapped to 1, spaces to 0, 
** player directions (N, S, W, E) to their respective constants, and whitespace 
** to SP. Any other character sets the value to -1, indicating an error.
**
** Returns: None
*/
static void	norme_1(char *line, int *ret, int i)
{
	if (line[i] == '1')
		ret[i] = 1;
	else if (line[i] == '0')
		ret[i] = 0;
	else if (line[i] == 'N')
		ret[i] = N;
	else if (line[i] == 'S')
		ret[i] = S;
	else if (line[i] == 'W')
		ret[i] = W;
	else if (line[i] == 'E')
		ret[i] = E;
	else if (ft_is_whitespace(line[i]))
		ret[i] = SP;
	else
		ret[i] = -1;
}

/**
** make_line - Parses a line and stores characters as integer map elements.
** @line: The line to parse.
** @size: The size of the line to store.
** @k: Pointer to the current line index.
**
** This function allocates an array of integers `ret` and fills it with
** values representing map elements based on the characters in `line`. If the
** line ends before reaching `size`, remaining elements are set to SP. 
** If the allocation fails, `*k` is set to -1.
**
** Returns: Pointer to the integer array `ret`.
*/
static int	*make_line(char *line, int size, int *k)
{
	int	*ret;
	int	i;

	i = -1;
	ret = (int *)malloc(sizeof(int) * size);
	if (ret == NULL)
		return (*k = -1, NULL);
	while (line[++i] && line[i] != '\n' && i < size)
		norme_1(line, ret, i);
	*k = i;
	if (i == size && line[i] && line[i] != '\n')
		while (i > 0)
			ret[--i] = -1;
	else
		while (i < size)
			ret[i++] = SP;
	return (ret);
}

/**
** map_maker - Allocates and initializes a 2D map array.
** @data: The map data structure to populate.
**
** This function allocates a 2D integer array to represent the map, then
** parses each line of the `.cub` file, converting characters into integers
** and storing them in the map. Returns NULL if allocation fails.
**
** Returns: Pointer to the 2D integer array `map`.
*/
static int	**map_maker(t_mapdata *data)
{
	int	i;
	int	j;
	int	k;
	int	**map;

	map = (int **)malloc(sizeof(int *) * data->length);
	if (map == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (data->char_map[++i])
	{
		map[j] = make_line(&data->char_map[i], data->size, &k);
		i += k;
		if (!data->char_map[i])
			break ;
		j++;
	}
	return (map);
}

/**
** map_parser - Parses the map and concatenates lines into a single string.
** @line: The initial line of the map.
** @data: The map data structure to populate.
** @fd: The file descriptor for the .cub file.
**
** This function reads each line of the `.cub` file, checks its length and
** validity with `maplength`, then appends it to a single string `char_map`.
** It also updates `data->length` and `data->size` based on line counts and
** maximum line width.
**
** Returns: Pointer to the 2D integer array `map`.
*/
int	**map_parser(char *line, t_mapdata *data, int fd)
{
	int	size;
	int	tmp;
	int	length;

	length = 0;
	size = 0;
	line = ft_strdup(line);
	while (line != NULL)
	{
		tmp = maplength(line);
		if (tmp > size)
			size = tmp;
		data->char_map = ft_strjoinf(data->char_map, line, S1 | S2);
		line = get_next_line(fd);
		length++;
	}
	data->length = length;
	data->size = size;
	free(line);
	return (map_maker(data));
}
