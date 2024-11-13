/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:27:33 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 02:29:47 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** component - Parses a component value from the line.
** @component: Pointer to the component (r, g, or b) to store the value.
** @line: The line containing the component value.
** @i: The index in the line to start parsing from.
**
** This function extracts a numerical component value (0-255) from the line,
** ensuring that it is valid. It skips any leading whitespace, parses the value
** and updates the component. If the value is invalid, it returns 1, otherwise
** it returns 0.
**
** Returns: 0 if the component is valid, 1 if invalid.
*/
char	component(unsigned char *component, char *line, int *i)
{
	int		tmp;
	char	ret;

	tmp = 0;
	while (line[*i] && ft_is_whitespace(line[*i]))
		*i += 1;
	if (ft_err_atoi(line, &tmp, i) == 0 && ft_isinrange((int [2]){0, 255}, tmp))
	{
		*component = tmp;
		ret = 0;
	}
	else
		ret = 1;
	while (line[*i] && ft_is_whitespace(line[*i]))
		*i += 1;
	(void)(line[*i] && (*i += 1));
	return (ret);
}

/**
** get_color - Parses the color from the line into a t_color struct.
** @line: The line containing the color components.
**
** This function parses the RGB components from the line, which can have any
** amount of whitespace between the components. Once all three components are
** parsed, it ensures no further components exist on the line. If parsing fails,
** the color values are set to -1, indicating an error.
**
** Returns: The parsed t_color struct.
*/
static t_color	get_color(char *line)
{
	int		i;
	t_color	color;

	i = 0;
	color = (t_color){-1};
	color.a = (component(&color.b, line, &i) || component(&color.g, line, &i) \
		|| component(&color.r, line, &i) || (line[i] && line[i] != '\n'));
	return (color);
}

/**
** get_texture_path - Extracts the texture path from the line.
** @line: The line containing the texture path.
** @path: The current texture path (if any).
**
** This function checks if a texture path has already been assigned. If so, it
** returns an error message. Otherwise, it parses the path from the line,
** skipping any leading whitespace, and extracts the texture path. It also checks
** that no extra data exists on the line after the path.
**
** Returns: The texture path if valid, or "!" if invalid.
*/
static char	*get_texture_path(char *line, char *path)
{
	int	i;
	int	j;
	int	k;

	if (path && path[0])
		return (free(path), ft_strdup(ERR_MULTIPLE_PATH));
	i = 0;
	while (line[i] && ft_is_whitespace(line[++i]))
		continue ;
	j = i;
	while (line[++i] && !ft_is_whitespace(line[i]) && line[i] != '\n')
		continue ;
	k = i - 1;
	while (line[i] && ft_is_whitespace(line[i]))
		i++;
	if (line[i] && line[i] != '\n')
		return (ft_strdup(ERR_MULTIPLE_PATH));
	return (ft_substr(line, j, --k));
}

/**
** cub_analyzer - Analyzes a line and assigns appropriate data to map.
** @line: The line to analyze.
** @data: The map data structure to store parsed information.
** @fd: The file descriptor used for reading the file.
**
** This function analyzes a line to check for valid keys (like texture paths
** or color definitions). It verifies if the line contains a known key and
** assigns the corresponding data (texture paths or colors). If the line does
** not match any expected pattern, an error is returned.
**
** Returns: 0 if parsing is successful, -1 if an error occurs.
*/
static int	cub_analyzer(char *line, t_mapdata *data, int fd)
{
	int	i;

	i = -1;
	while (ft_is_whitespace(line[++i]))
		continue ;
	if (line[i] && line[i + 1])
	{
		if (line[i] == 'N' && line[i + 1] == 'O' && ++data->keycount[NO])
			data->path[NO] = get_texture_path(&line[i + 1], data->path[NO]);
		else if (line[i] == 'S' && line[i + 1] == 'O' && ++data->keycount[SO])
			data->path[SO] = get_texture_path(&line[i + 1], data->path[SO]);
		else if (line[i] == 'W' && line[i + 1] == 'E' && ++data->keycount[WE])
			data->path[WE] = get_texture_path(&line[i + 1], data->path[WE]);
		else if (line[i] == 'E' && line[i + 1] == 'A' && ++data->keycount[EA])
			data->path[EA] = get_texture_path(&line[i + 1], data->path[EA]);
		else if (line[i] == 'F' && ++data->keycount[EA + 1])
			data->c_floor = get_color(&line[i + 1]);
		else if (line[i] == 'C' && ++data->keycount[EA + 2])
			data->c_ceiling = get_color(&line[i + 1]);
		else if (line[i] == '0' || line[i] == '1')
			data->map = map_parser(line, data, fd);
		else
			return (-1);
	}
	return (0);
}

/**
** cub_parser - Parses the map file and analyzes its contents.
** @fd: The file descriptor for the map file.
** @data: The map data structure to store parsed information.
**
** This function reads the map file line by line, passing each line to the
** analyzer for processing. It ensures that the file is correctly parsed, and
** that no errors occur during the parsing of textures, colors, or map data.
** If an error occurs during parsing, an error manager is called.
*/
void	cub_parser(int fd, t_mapdata *data)
{
	char	*line;
	int		error;
	int		i;

	i = 0;
	error = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (cub_analyzer(line, data, fd) == -1)
			return (free(line), close(fd),
				error_manager(ERRCODE_MAP_LINE, data), (void)0);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	error = check_for_errors(data);
	if (error)
	{
		close(fd),
		error_manager(error, data);
	}
}
