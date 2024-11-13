/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:48:11 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 02:12:06 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

# include "includes.h"

enum	e_errorcodes
{
	ERRCODE_NULL,
	ERRCODE_TEXTURES,
	ERRCODE_NOFILE,
	ERRCODE_ARG_EXT,
	ERRCODE_NB_ARGS,
	ERRCODE_PATH_EAST,
	ERRCODE_PATH_WEST,
	ERRCODE_PATH_NORTH,
	ERRCODE_PATH_SOUTH,
	ERRCODE_COLOR_INVALID,
	ERRCODE_MAP_NOSPAWN,
	ERRCODE_MAP_UNCLOSED,
	ERRCODE_MAP_TOOMUCHSPAWM,
	ERRCODE_MAP_LINE,
	ERRCODE_MAP_UNWANTED_CHAR,
	ERRCODE_KEYCOUNT,
	ERRCODE_KEYCOUNT_NO,
	ERRCODE_KEYCOUNT_SO,
	ERRCODE_KEYCOUNT_WE,
	ERRCODE_KEYCOUNT_EA,
	ERRCODE_KEYCOUNT_F,
	ERRCODE_KEYCOUNT_C,
};

typedef enum e_refresh
{
	ISINIT,
	RESET,
	INIT,
	RESETALL
}		t_refresh;

typedef enum e_init
{
	MLX,
	IMG,
	PLAYER,
	MAP,
	TEXTURES,
	INIT_COUNT,
}		t_init;

typedef enum e_textures
{
	NO,
	SO,
	WE,
	EA,
	TEXTURES_COUNT
}		t_e_textures;

// `typedef enum e_texclass
// {
// 	GET,
// 	GETPIXELCOLOR,

// } t_e_class;

typedef enum e_xevent
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}		t_xevent;

#endif