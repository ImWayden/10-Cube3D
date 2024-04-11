/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:27:33 by wayden            #+#    #+#             */
/*   Updated: 2024/04/11 15:59:57 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

char component(char *component, char *line, int *i)
{
	int tmp;
	char ret;
	
	tmp = 0;
	while(line[*i] && ft_is_whitespace(line[*i]))
		*i += 1;
	if(ft_err_atoi(line, &tmp, i) == 0 && ft_isinrange((int[2]){0,255}, tmp))
	{
		if(DEBUG)
			printf("line = %s, tmp = %d\n", line , tmp);
		*component = tmp;
		ret = 0;
	}
	else
		ret = 1;
	if(DEBUG)
		printf("line = %s, tmp = %d\n", line , tmp);
	while(line[*i] && ft_is_whitespace(line[*i]))
		*i += 1;
	(void)(line[*i] && (*i += 1));
	return (ret);
}

/*
	renvois une struct t_color former des trois int r g b;
	peux avoir potetntielement autant de whitespace que l'on veut entre 
	les differents composants par contre apres que les trois composant
	ai ete trouver il ne doit pas y avoir d'autre composant present 
*/
static t_color get_color(char *line)
{
	int i;
	t_color color;
	
	i = 0;
	color = (t_color){-1};
		
	color.a = component(&color.r,line, &i) \
	|| component(&color.g,line, &i) \
	|| component(&color.b,line, &i)
	|| (line[i] && line[i] != '\n');
	if(DEBUG)
		printf(" color.a = %d\n", color.a);
	return (color);
}

/*
	renvois la chaine de caractere correspondant au path vers la texture
	sinon renvois ERR_MULTIPLE_PATH (! un caractere qui ne peut pas etre un path correct de toute facon)
	probablement besoin d'ajouter la gestion de la redeffinition de la key.
	
	to debug:
		petit probleme avec le \n de fin se faiasant enregistrer
*/
static char *get_texture_path(char *line, char *path)
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
	while (line[++i] && !ft_is_whitespace(line[i]) && line[i] != '\n')
		continue ;
	k = i - 1;
	while (line[i] && ft_is_whitespace(line[i++]))
		continue ;
	if (line[i] && line[i] != '\n')
		return (ft_strdup(ERR_MULTIPLE_PATH));
	return (ft_substr(line, j, --k));
}

/*
	parse la ligne en cour verifie s'il y a une cle connu,
	si la ligne n'est pas vide et ne contient pas que des whitespaces
	mais aucune cle connu ou bout de map alors on renvois une erreur
*/
static int cub_analyzer(char *line, t_mapdata *data, int fd)
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
			data->color_floor = get_color(&line[i + 1]);
		else if (line[i] == 'C')
			data->color_ceiling = get_color(&line[i + 1]);
		else if (line[i] == '0' || line[i] == '1')
			data->map = map_parser(line, data, fd);
		else
			return (-1);
	}
	return (0);
}

void cub_parser(int fd, t_mapdata *data)
{
	char	*line;
	int 	error;
	int		i;

	i = 0;
	error = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if(cub_analyzer(line, data, fd) == -1)
			return(free(line), error_manager(ERRCODE_MAP_LINE, data), (void)0);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	error = check_for_errors(data);
	if (error)
		error_manager(error, data);
}