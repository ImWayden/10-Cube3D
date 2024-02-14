/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:16:01 by wayden            #+#    #+#             */
/*   Updated: 2024/02/14 16:32:09 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
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

#endif