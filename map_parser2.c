/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:31:27 by wayden            #+#    #+#             */
/*   Updated: 2024/04/11 15:54:42 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers/includes.h"

/*
	return the size of a line and check for unwanted character
*/
static int	maplength(char *line)
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
	else if (line[i] == ' ')
		ret[i] = SP;
	else
		ret[i] = -1;
}

/*
	parse la ligne et stocke les carctere croisé sous forme d'int
*/
static int	*make_line(char *line, int size, int *k)
{
	int *ret;
	int	i;

	i = -1;
	ret = (int *)malloc(sizeof(int) * size);
	if (ret == NULL)
		return (*k = -1, NULL);
	while (line[++i] && line[i] != '\n' && i < size)
		norme_1(line, ret, i);
	*k = i;
	if(i == size && line[i] && line[i] != '\n')
		while(i > 0)
			ret[--i] = -1;
	else		
		while(i < size)
			ret[i++] = SP;
	return (ret);
}

/*
	alloc l'array 2D reresentant la map puis reparse le fichier .cub
	afin de stocker les caractere sous forme de tableau de int
*/
static int	**map_maker(t_mapdata *data)
{
	int		i;
	int		j;
	int		k;
	int		**map;
	
	map = (int **)malloc(sizeof(int *) * data->length);
	if(map == NULL)
		return  (NULL);
	i = -1;
	j = 0;
	while(data->char_map[++i])
	{
		map[j] = make_line(&data->char_map[i], data->size, &k);
		i += k;
		if(!data->char_map[i])
			break;
		j++;
	}
	return (map);
}
/* 
	parse la map et concat toute les lignes la composant en une seule chaine de caractere
	\n inclus ainsi on obtient la length de la map et la size max
*/
int **map_parser(char *line, t_mapdata *data, int fd)
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
		if(tmp > size)
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

/*

static int	**map_maker(int size, t_mapdata *data, int i, int length)
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
	//la partie suivante peut potentiellement etre remplace par un seul read de tout les caracteres
	//jusqu'a la ligne voulu pour ca il suffirait de stocker le nombre de caractere lu jusqu'a attaindre la map
	//avoir atteint la map;
	while(++j < i)
		free(get_next_line(fd));
	//de la meme maniere peut etre que je peut faire un simple read de toute la map 
	//plutot que de faire plein de getnext line ce qui ferait beaucoup moins d'appel
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
		// if(tmp == -1)
		// 	return (free(line), NULL);
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
*/
