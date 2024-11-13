/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_defines.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:35:13 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 03:41:12 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DEFINES_H
# define CUB_DEFINES_H

# define COLOR_RESET "\033[0m"

// Regular Colors
# define COLOR_BLACK "\033[0;30m"
# define COLOR_RED "\033[0;31m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_MAGENTA "\033[0;35m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_WHITE "\033[0;37m"

# define ERR_NB_ARGS "Invalid NB of Arguments\nUsage: ./Cub3D [file.cub]\n"
# define ERR_MAP_LINE "invalide line has been detected in the cub file\n"
# define ERR_CUB_FILE_FORMAT "the map file does not respect the .cub format\n"
# define ERR_MAP_COLOR "color components should be in range [0,255]\n"
# define ERR_MAP_TEXTURE_ACCESS "incorrect or innaccessible texture path\n"

# define ERR_MULTIPLE_PATH "!"

# define N 2
# define W 3
# define S 4
# define E 5
# define SP 6

# define LEFT 0
# define RIGHT 1

# define ERR_TEXTURES "invalid xpm file"

# define ERR_NOFILE "can't open file"
# define ERR_ARG_EXT "Invalid file Extension : .cub required"
# define ERR_PATH_EAST "Path Definition : EAST\n"
# define ERR_PATH_WEST "Path Definition : WEST\n"
# define ERR_PATH_NORTH "Path Definition : NORTH\n"
# define ERR_PATH_SOUTH "Path Definition : SOUTH\n"

#define ERR_KEYCOUNT_NO "Mutiple key detected : NO\n"
#define ERR_KEYCOUNT_SO "Mutiple key detected : SO\n"
#define ERR_KEYCOUNT_WE "Mutiple key detected : WE\n"
#define ERR_KEYCOUNT_EA "Mutiple key detected : EA\n"
#define ERR_KEYCOUNT_F "Mutiple key detected : F\n"
#define ERR_KEYCOUNT_C "Mutiple key detected : C\n"

# define ERR_COLOR_INVALID "Invalid Color, color components should be in range [0,255] and following the format r, g, b\nExemple : 112, 128, 144\n"

# define ERR_MAP_NOSPAWN "No Spawn Point Detected\n"
# define ERR_MAP_UNCLOSED "the map isn't closed properly\n"
# define ERR_MAP_TOOMUCHSPAWM "Multiple SpawnPoint Detected\n"

# define ERR_MAP_UNWANTED_CHAR "Map contains unwanted characters\n"
# define ERR_TEX_INVALID

# define WIDTH 1600
# define HEIGHT 900

# define TOLERANCE 0.1

# define DEBUG 0

#endif