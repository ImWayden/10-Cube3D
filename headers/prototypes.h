/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:56:33 by wayden            #+#    #+#             */
/*   Updated: 2024/04/11 12:49:36 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "includes.h" 
/*map checker*/
int		check_map(t_mapdata *data);
int		**map_parser(char *line, t_mapdata *data, int fd);
void	cub_parser(int fd, t_mapdata *data);
int		check_for_errors(t_mapdata *data);
void	free_struct_map(t_mapdata *data);
void	error_manager(int error_code, t_mapdata *data);
int		ft_isvalid(char c);

/*Singletons*/
bool	sget_init(t_init index, int set);
t_img *get_img();
t_mlx *get_mlx();
t_player *get_player();

/* hook */
void init_hook(void);


/*debug*/
void debug_print_data(t_mapdata *data);

/*mlx utils*/
void ver_line_x(t_img *img, t_lineinfo line);

#endif