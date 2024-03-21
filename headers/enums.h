/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:48:11 by wayden            #+#    #+#             */
/*   Updated: 2024/03/20 21:49:18 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

# include "includes.h"

enum errorcodes{
	ERRCODE_PATH_EAST = 1,
	ERRCODE_PATH_WEST,
	ERRCODE_PATH_NORTH,
	ERRCODE_PATH_SOUTH,
	ERRCODE_COLOR_INVALID,
	ERRCODE_MAP_NOSPAWN,
	ERRCODE_MAP_UNCLOSED,
	ERRCODE_MAP_TOOMUCHSPAWM,
	ERRCODE_MAP_LINE,
	ERRCODE_MAP_UNWANTED_CHAR,
	ERRCODE_PATH_EAST2,
	ERRCODE_PATH_WEST2,
	ERRCODE_PATH_NORTH2,
	ERRCODE_PATH_SOUTH2,
};

typedef enum e_refresh
{
	NOP,
	REFRESH,
	SET,
	REFRESHALL
}	t_refresh;

typedef enum e_init
{
	MLX,
}	t_init;

#endif