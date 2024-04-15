/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:56:33 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 09:39:29 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "includes.h" 

/*math utils*/
int	cross_product(int a, int b, int c);

/*map checker*/
int		check_map(t_mapdata *data);
int		**map_parser(char *line, t_mapdata *data, int fd);
void	cub_parser(int fd, t_mapdata *data);
int		check_for_errors(t_mapdata *data);
void	free_struct_map(t_mapdata *data);
void	error_manager(int error_code, t_mapdata *data);
int		ft_isvalid(char c);
int		extension_check(char *line);

/*Singletons*/
bool	sget_init(t_init index, int set);
t_img *get_img();
t_mlx *get_mlx();
t_player *get_player();
t_mapdata *get_mapdata(char *file);
t_xpm_texture *get_texture(int index/*,int exec, void *args[4]*/);
/* hook */
void init_hook(void);


/*debug*/
void debug_print_data(t_mapdata *data);

/*mlx utils*/
void ver_line_x(t_img *img, t_color color, t_range range, int x);
void tex_ver_line_x(t_img *img, t_xpm_texture *texture, t_range r, int x);
/* vec2 Utils*/
t_vec2 vec2_perpendicular(t_vec2 vector);

/* raycast */
void update_raycast(t_player *player, t_mapdata *data, t_mlx *mlx, t_img *img);
#endif