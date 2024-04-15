/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_defines.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:35:13 by wayden            #+#    #+#             */
/*   Updated: 2024/04/15 12:18:16 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DEFINES_H
# define CUB_DEFINES_H

#define COLOR_RESET "\033[0m"

// Regular Colors
#define COLOR_BLACK "\033[0;30m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_WHITE "\033[0;37m"

# define ERR_NB_ARGS "Invalid NB of Arguments\nUsage: ./Cub3D [file.cub]"
# define ERR_MAP_LINE "invalide line has been detected in the cub file"
# define ERR_CUB_FILE_FORMAT "the map file does not respect the .cub format"
# define ERR_MAP_COLOR "color components should be in range [0,255]"
# define ERR_MAP_TEXTURE_ACCESS "incorrect or innaccessible texture path"

# define ERR_MULTIPLE_PATH "!"

# define N 2
# define W 3
# define S 4
# define E 5
# define SP 6

# define ERR_NOFILE "can't open file"
# define ERR_ARG_EXT "Invalid file Extension : .cub required"
# define ERR_PATH_EAST "Path east err placeholder"
# define ERR_PATH_WEST "Path west err placeholder"
# define ERR_PATH_NORTH "Path north err placeholder"
# define ERR_PATH_SOUTH "Path South err placeholder"

# define ERR_PATH_EAST2 "Path east err placeholder"
# define ERR_PATH_WEST2 "Path west err placeholder"
# define ERR_PATH_NORTH2 "Path north err placeholder"
# define ERR_PATH_SOUTH2 "Path South err placeholder"

# define ERR_COLOR_INVALID "invalid Color placeholder"

# define ERR_MAP_NOSPAWN "No Spawn Point Detected"
# define ERR_MAP_UNCLOSED "the map isn't closed properly"
# define ERR_MAP_TOOMUCHSPAWM "Multiple SpawnPoint Detected"

# define ERR_MAP_UNWANTED_CHAR "Map contains unwanted characters"

# define WIDTH 1920
# define HEIGHT 1080

# define DEBUG 0

#endif