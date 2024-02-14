/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:09:57 by wayden            #+#    #+#             */
/*   Updated: 2024/02/14 16:47:21 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

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
	while (line[++i])
		norme_1(line, ret, i);
	while(i < size)
		ret[i++] = SP;
	return (ret);
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
	while(++j <= i)
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
	return (map);
}


int ft_isvalid(char c)
{
	return(c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'\
	 || c == 'E' || c == ' ');
}

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
	return un array int 2D ou NULL si la map contient des caracteres invalides
	TODO, besoin de mieux gerer les free de line lors d'erreur risque de double free
	ptetre besoin de passer directment par le gestionnaire d'erreur plutot que de renvoyer NULL
*/
int **map_parser(char *line, t_mapdata *data, int i, int fd)
{
	int		size;
	int		tmp;
	int		length;
	
	length = 0;
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
	
	if (path[0])
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
	return (ft_substr(line, j, i));
}

/*
	parse la ligne en cour verifie s'il y a une cle connu,
	si la ligne n'est pas vide et ne contient pas que des whitespaces
	mais aucune cle connu ou bout de map alors on renvois une erreur
*/
int cub_analyzer(char *line, t_mapdata *data, int i, int fd)
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
			data->map = map_parser(line, data, i, fd);
		else
			return (-1);
	}
	return (0);
}


/*
parse ligne par ligne le fichier map si celui ci est de la bonne extension et lisible
la verification ce fera probablement dans la fonction appelante
*/
void cub_parser(int fd, t_mapdata *data)
{
	char	*line;
	char	*error;
	int		i;

	i = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if(map_analyzer(line, &data, i, fd) == -1)
			free(line), print_error(ERR_MAP_LINE);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	error = check_for_errors(data);
	if (error)
		print_error(error);
}





/* TODO

on a plusieur chose a verifier:

le fichier doit avoir l'extension .cub

les cles doivent etre uniques et ne doivent donc pas etre definis plusieurs fois dans le meme fichier map.cub

les chemins vers les textures : 
-doivent etre accessible et les fichiers lisibles
-les definitions ne doivent contenir q'un seul chemin
-le chemin peut etre separer par autant de whitespace que l'on veut de la cle

les couleurs pour le sol et le plafond doivent etre des couleur valide, donc chaque element doit etre compris dans la range [0,255]

la map:
-doit etre ferme par des mur(des 1) on vas probablement avoir besoin de faire de la recursivitee afin de verifier que tout est bien ferme
-ne doit pas contenir d'autre caracter que N,S,W,E,0,1 
-doit avoir au moins un point de spawn possible


*/
