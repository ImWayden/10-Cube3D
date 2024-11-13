/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:16:01 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 01:51:04 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// union u_color
// {
// 	struct s_color
// 	{
// 		int	r;
// 		int	g;
// 		int	b;
// 	};

// }
typedef struct s_int_range
{
	int					start;
	int					end;

}						t_range;

typedef struct s_vec2
{
	double				x;
	double				y;
}						t_vec2;

typedef union s_color
{
	unsigned int		hex;
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	a;
	};
}						t_color;

typedef struct s_spawnpoints
{
	t_vec2				n;
	t_vec2				s;
	t_vec2				w;
	t_vec2				e;
}						t_spawnpoints;

typedef struct s_mapdata
{
	int					**map;
	int					size;
	int					length;
	int					fd;
	int					keycount[6];
	char				*char_map;
	char				*path[4];
	char				*name_file;
	t_color				c_floor;
	t_color				c_ceiling;
	t_vec2				spawnpoint;
	t_vec2				spawndir;
}						t_mapdata;

typedef struct s_cubvar
{
	int					no;
	int					so;
	int					we;
	int					ea;
}						t_cubvar;

typedef struct s_player
{
	t_vec2				pos;
	t_vec2				direction;
	t_vec2				camera;
	double				speed;
	int					is_mouselock;
}						t_player;

typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;

}						t_mlx;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_img;

typedef struct s_keybinds
{
	int					walk_up;
	int					walk_left;
	int					walk_right;
	int					walk_down;
}						t_keybinds;

typedef struct s_raydata
{
	double				*deltadist;
	double				*sidedist;
	double				*raydir;
	int					*step;

}						t_raydata;

typedef struct s_rayutils
{
	double				camera_x;
	int					map_x;
	int					map_y;
	t_vec2				ray_dir;
	t_vec2				side_dist;
	t_vec2				delta_dist;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
}						t_rayutils;

typedef struct s_xpm_texture
{
	t_img				img;
	int					width;
	int					height;
	t_vec2				pos_in;
	double				lineheight;
}						t_xpm_texture;

typedef struct s_lineinfo
{
	int					start;
	int					end;
	int					x;
	int					tex_x;
	int					tex_y;
	t_xpm_texture		*texture;
	t_color				color;
}						t_lineinfo;

#endif