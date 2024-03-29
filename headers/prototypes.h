/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:56:33 by wayden            #+#    #+#             */
/*   Updated: 2024/03/20 21:49:48 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "includes.h" 
/*map checker*/
int		check_map(t_mapdata *data);
int		**map_parser(char *line, t_mapdata *data, int i, int fd);
void	cub_parser(int fd, t_mapdata *data);
int		check_for_errors(t_mapdata *data);
void	free_struct_map(t_mapdata *data);
void	error_manager(int error_code, t_mapdata *data);
int		ft_isvalid(char c);
#endif