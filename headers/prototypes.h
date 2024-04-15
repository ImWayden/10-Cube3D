/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:56:33 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 19:57:52 by wayden           ###   ########.fr       */
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


/*textures*/
t_xpm_texture *get_texture(int index/*,int exec, void *args[4]*/);
void destroy_textures(t_xpm_texture *t, t_mlx *mlx);

/* hook */
void init_hook(void);

/* movements */
void move_forward(t_player *player, int **map);
void move_backward(t_player *player, int **map);
void move_left(t_player *player, int **map);
void move_right(t_player *player, int **map);
void rotate_left(t_player *player);
void rotate_right(t_player *player);
/*debug*/
void debug_print_data(t_mapdata *data);

/*mlx utils*/
void ver_line_x(t_img *img, t_color color, t_range range, int x);
void tex_ver_line_x(t_img *img, t_xpm_texture *texture, t_range r, int x);
/* vec2 Utils*/
t_vec2 vec2_perpendicular(t_vec2 vector, int dir);
t_vec2 vec2_addition(t_vec2 v1, t_vec2 v2);
t_vec2 vec2_substract(t_vec2 v1, t_vec2 v2);
t_vec2 vec2_speed(t_vec2 vector, double speed);

double ft_abs_dbl(double x);

/* raycast */
void update_raycast(t_player *player, t_mapdata *data, t_mlx *mlx, t_img *img);
#endif