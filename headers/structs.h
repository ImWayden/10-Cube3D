/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:16:01 by wayden            #+#    #+#             */
/*   Updated: 2024/03/20 21:20:04 by wayden           ###   ########.fr       */
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


typedef union s_color {
	unsigned int hex;
	struct
	{
		char	b;
		char	g;
		char	r;
		char	a;
	};
}	t_color;

typedef struct s_mapdata
{
	int		**map;
	int		size;
	int		length;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	*name_file;
	t_color	color_floor;
	t_color	color_ceiling;
}	t_mapdata;

typedef struct s_cubvar
{
	int no;
	int so;
	int we;
	int ea;

} t_cubvar;


typedef struct s_position
{
	int x;
	int y;	
} t_position;

typedef struct s_player
{
	t_position pos;
	
} t_player;

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;

}   t_mlx;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

#endif