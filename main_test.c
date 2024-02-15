/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 03:07:08 by wayden            #+#    #+#             */
/*   Updated: 2024/02/15 18:37:53 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"
#include <stdio.h>

void free_struct_map(t_mapdata *data)
{
	int y;
	
	y = -1;
	while(++y < data->length)
		free(data->map[y]);
	free(data->map);
	free(data->path_ea);
	free(data->path_no);
	free(data->path_so);
	free(data->path_we);
}

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
	return 0  si tout c'est bien passer
	return -1 si aucun nbr n'a ete trouver
	return -2 si le nombre overflow un int
	
	l'utilisation d'un t_3int est la uniquement pour respecter
	la norme et les 25 lignes, ca rend tout ca ilisible a souhait mais bon  
*/
int ft_err_atoi(const char *nptr, int *ret, int *j)
{
	t_3int var;
    unsigned int res;

	var = (t_3int){1, *j, 0};
    res = 0;
    while ((nptr[var.g] >= 9 && nptr[var.g] <= 13) || nptr[var.g] == ' ')
        var.g++;
    if (nptr[var.g] == '+' || nptr[var.g] == '-')
    {
        if (nptr[var.g] == '-')
            var.r = -var.r;
        var.g++;
    }
    while (nptr[var.g] >= '0' && nptr[var.g] <= '9' && ++var.b)
    {
        if ((int)res > (INT_MAX - (nptr[var.g] - '0')) / 10)
            return -2;
        res = res * 10 + nptr[var.g] - '0';
        var.g++;
    }
	*j = var.g;
	if(!var.b)
		return (-1);
    *ret = res * var.r;
    return 0;
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
	
	i = 0;
	color = (t_color){-1,-1,-1};
	ft_err_atoi(line, &color.r, &i);
	(void)(line[i] && i++);
	ft_err_atoi(line, &color.g, &i);
	(void)(line[i] && i++);
	ft_err_atoi(line, &color.b, &i);
	(void)(line[i] && i++);
	while(line[i] && ft_is_whitespace(line[i]))
		i++;
	if(line[i] && line[i] != '\n')
		color.r = -1;
	return (color);
}

/*
	renvois la chaine de caractere correspondant au path vers la texture
	sinon renvois ERR_MULTIPLE_PATH (! un caractere qui ne peut pas etre un path correct de toute facon)
	probablement besoin d'ajouter la gestion de la redeffinition de la key.
	
	to debug:
		petit probleme avec le \n de fin se faiasant enregistrer
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
			data->color_floor = get_color(&line[i + 1]);
		else if (line[i] == 'C')
			data->color_ceiling = get_color(&line[i + 1]);
		else if (line[i] == '0' || line[i] == '1')
			data->map = map_parser(line, data, l, fd);
		else
			return (-1);
	}
	return (0);
}

void print_error(const char *error)
{
	write(STDERR_FILENO,"Error\n",7);
	write(STDERR_FILENO,error, ft_strlen(error));
	//besoin d'ajouter la gestion de liberation de la memoire et autre probablement
	// a moins que je ne decidee de le faire autre part

	
}

void error_manager(int error_code, t_mapdata *data)
{
	static const char *errors[] = {NULL, ERR_PATH_EAST, ERR_PATH_WEST,\
	ERR_PATH_NORTH, ERR_PATH_SOUTH, ERR_COLOR_INVALID, ERR_MAP_NOSPAWN,\
	ERR_MAP_UNCLOSED, ERR_MAP_TOOMUCHSPAWM, ERR_MAP_LINE};

	print_error(errors[error_code]);
	free_struct_map(data);
	exit(error_code);
}


int ft_isinrange(int min_max[2], int i)
{
	return(i >= min_max[0] && i <= min_max[1]);
}

int check_colors(t_mapdata *data)
{
	t_color color;
	int		i;
	int		check;

	check = 0;
	i = -1;
	color = data->color_ceiling;
	while(++i < 2)
	{
		check += !ft_isinrange((int[2]){0,255}, color.r);
		check += !ft_isinrange((int[2]){0,255}, color.g);
		check += !ft_isinrange((int[2]){0,255}, color.b);
		color = data->color_floor;
	}
	if(check)
		return(ERRCODE_COLOR_INVALID);
	return (0);
}

int check_textures(t_mapdata *data)
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


int ft_isvoid(int actual)
{

	return ((actual == 0 || (actual >= N && actual < SP)));
}

int check_wall(t_mapdata *data, int y, int x, int actual)
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

int check_char(int c, t_cubvar *vars)
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

void debug_print_data(t_mapdata *data)
{
	int y = -1;
	int x = -1;
	printf("size(x) = %d\n", data->size);
	printf("length(y) = %d\n", data->length);
	while(++y < data->length)
	{
		x = -1;
		printf("line [%02d]  ",y);
		while(data->map[y] != NULL && ++x < data->size)
			printf("%d ", data->map[y][x]);
		printf("\n");			
	}
	printf("data path ea: %s\n", data->path_ea);
	printf("data path no: %s\n", data->path_no);
	printf("data path so: %s\n", data->path_so);
	printf("data path we: %s\n", data->path_we);
	printf("color floor : %d, %d, %d\n", data->color_floor.r,data->color_floor.g,data->color_floor.b);
	printf("color ceilling : %d, %d, %d\n", data->color_ceiling.r,data->color_ceiling.g,data->color_ceiling.b);
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
		if(cub_analyzer(line, data, i, fd) == -1)
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




int main( void )
{
	t_mapdata data;
	int fd;
	
	data = (t_mapdata){NULL, 0, 0, NULL,NULL,NULL,NULL,"map.cub",(t_color){0,0,0},(t_color){0,0,0}};
	fd = open(data.name_file, O_RDONLY);
	cub_parser(fd, &data);
	debug_print_data(&data);
	free_struct_map(&data);
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
	//printf("length = %d, size = %d x = %d y = %d \n",data->length, data->size, x,y);
	/*
		
		to debug : get_color not working properly and not storing coolor components in the good variable for some reason
		
	*/