/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 03:07:08 by wayden            #+#    #+#             */
/*   Updated: 2024/02/15 06:32:11 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"
#include <stdio.h>


void	norme_1(char *line, int *ret, int i)
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
	else if (line[i] == ' ')
		ret[i] = SP;
	else
		ret[i] = -1;
}

/*
	parse la ligne et stocke les carctere croiser sous forme d'int
*/
int *make_line(char *line, int size)
{
	int *ret;
	int	i;

	i = -1;
	ret = (int *)malloc(sizeof(int) * size);
	if (ret == NULL)
		return (NULL);
	while (line[++i] && line[i] != '\n' && i < size)
		norme_1(line, ret, i);
	while(i < size)
		ret[i++] = SP;
	return (ret);
}

/*
	check if it's a valid character
*/
int ft_isvalid(char c)
{
	return(c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'\
	 || c == 'E' || c == ' ');
}

/*
	return the size of a line and check for unwanted character
*/
int maplength(char *line)
{
	int i;
	int error;
	
	i = -1;
	error = ft_isvalid(line[++i]);
	while (error)
		error = ft_isvalid(line[++i]);
	if (line[i] && line[i] != '\n')
		return (-1);
	return (i);
}

/*
	alloc l'array 2D reresentant la map puis reparse le fichier .cub
	afin de stocker les caractere sous forme de tableau de int
*/
int **map_maker(int size, t_mapdata *data, int i, int length)
{
	int		j;
	int		fd;
	char	*line;
	int		**map;
	
	j = -1;
	fd = open(data->name_file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = (int **)malloc(sizeof(int *) * length);
	if (map == NULL)
		return (NULL);
	while(++j < i)
		free(get_next_line(fd));
	line = get_next_line(fd);
	j = 0;
	while(line != NULL)
	{
		map[j] = make_line(line, size);
		free(line);
		j++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (map);
}

int **map_parser(char *line, t_mapdata *data, int i, int fd)
{
	int		size;
	int		tmp;
	int		length;
	
	length = 0;
	size = 0;
	line = ft_strdup(line);
	while(line != NULL)
	{
		tmp = maplength(line);
		if(tmp == -1)
			return (free(line), NULL);
		if(tmp > size)
			size = tmp;
		free(line);
		line = get_next_line(fd);
		length++;
	}
	data->length = length;
	data->size = size;
	free(line);
	return (map_maker(size, data, i, length));
}

/*
	renvois une struct t_color former des trois int r g b;
	peux avoir potetntielement autant de whitespace que l'on veut entre 
	les differents composants par contre apres que les trois composant
	ai ete trouver il ne doit pas y avoir d'autre composant present 
*/
t_color get_color(char *line)
{
	int i;
	t_color color;
	
	i = -1;
	while(line[++i] && ft_is_whitespace(line[i]))
		continue ;
	color.r = ft_atoi(&line[i]);
	while(line[i] && ft_isdigit(line[i++]))
		continue ;
	i++;
	color.g = ft_atoi(&line[i]);
	while(line[i] && ft_isdigit(line[i++]))
		continue ;
	i++;
	color.b = ft_atoi(&line[i]);
	while(line[i] && ft_isdigit(line[i++]))
		continue ;
	while(line[++i] && ft_is_whitespace(line[i]))
		continue ;
	if(line[i] && line[i] != '\n')
		color.r = -1;
	return (color);
}

/*
	renvois la chaine de caractere correspondant au path vers la texture
	sinon renvois ERR_MULTIPLE_PATH (! un caractere qui ne peut pas etre un path correct de toute facon)
	probablement besoin d'ajouter la gestion de la redeffinition de la key.
*/
char *get_texture_path(char *line, char *path)
{
	int i;
	int j;
	int k;
	
	if (path && path[0])
		return(free(path), ft_strdup(ERR_MULTIPLE_PATH));
	i = 0;
	while (line[i] && ft_is_whitespace(line[++i]))
		continue ;
	j = i;
	while (line[++i] && !ft_is_whitespace(line[i]) )
		continue ;
	k = i;
	while (line[i] && ft_is_whitespace(line[i++]))
		continue ;
	if (line[i] && line[i] != '\n')
		return (ft_strdup(ERR_MULTIPLE_PATH));
	return (ft_substr(line, j, k));
}

/*
	parse la ligne en cour verifie s'il y a une cle connu,
	si la ligne n'est pas vide et ne contient pas que des whitespaces
	mais aucune cle connu ou bout de map alors on renvois une erreur
*/
int cub_analyzer(char *line, t_mapdata *data, int l, int fd)
{
	int i;

	i = -1;
	while (ft_is_whitespace(line[++i]))
		continue ;
	if(line[i] && line[i + 1])
	{
		if (line[i] == 'N' && line[i + 1] == 'O')
			data->path_no = get_texture_path(&line[i + 1], data->path_no);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			data->path_so = get_texture_path(&line[i + 1], data->path_so);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			data->path_we = get_texture_path(&line[i + 1], data->path_we);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			data->path_ea = get_texture_path(&line[i + 1], data->path_ea);
		else if (line[i] == 'F')
			data->color_floor = get_color(&line[i]);
		else if (line[i] == 'C')
			data->color_ceiling = get_color(&line[i]);
		else if (line[i] == '0' || line[i] == '1')
			data->map = map_parser(line, data, l, fd);
		else
			return (-1);
	}
	return (0);
}


int main( void )
{
	t_mapdata data;
	int y = -1;
	int x = -1;
	int j;
	int fd;
	char *line;
	
	data = (t_mapdata){NULL, 0, 0, NULL,NULL,NULL,NULL,"map.cub",(t_color){0,0,0},(t_color){0,0,0}};
	j = 0;
	fd = open(data.name_file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		cub_analyzer(line, &data, j, fd);
		free(line);
		j++;
		line = get_next_line(fd);
	}
	free(line);
	while(++y < data.length)
	{
		x = -1;
		printf("line [%02d]  ",y);
		while(data.map[y] != NULL && ++x < data.size)
			printf("%d ", data.map[y][x]);
		printf("\n");			
	}
	y = -1;
	x = -1;
	printf("data path ea: %s\n", data.path_ea);
	printf("data path no: %s\n", data.path_no);
	printf("data path so: %s\n", data.path_so);
	printf("data path we: %s\n", data.path_we);
	printf("color floor : %d, %d, %d\n", data.color_floor.r,data.color_floor.g,data.color_floor.b);
	printf("color ceilling : %d, %d, %d\n", data.color_ceiling.r,data.color_ceiling.g,data.color_ceiling.b);
	while(++y < data.length)
		free(data.map[y]);
	free(data.map);
	free(data.path_ea);
	free(data.path_no);
	free(data.path_so);
	free(data.path_we);
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