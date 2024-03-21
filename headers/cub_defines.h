/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_defines.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:35:13 by wayden            #+#    #+#             */
/*   Updated: 2024/03/20 22:06:01 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DEFINES_H
# define CUB_DEFINES_H


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

# define ERR_PATH_EAST "Path east err placeholder"
# define ERR_PATH_WEST "Path west err placeholder"
# define ERR_PATH_NORTH "Path north err placeholder"
# define ERR_PATH_SOUTH "Path South err placeholder"

# define ERR_PATH_EAST2 "Path east err placeholder"
# define ERR_PATH_WEST2 "Path west err placeholder"
# define ERR_PATH_NORTH2 "Path north err placeholder"
# define ERR_PATH_SOUTH2 "Path South err placeholder"

# define ERR_COLOR_INVALID "invalid Color placeholder"

# define ERR_MAP_NOSPAWN "err map spawnpoint placeholder"
# define ERR_MAP_UNCLOSED "the map isn't closed properly"
# define ERR_MAP_TOOMUCHSPAWM "too much spawn point error placeholder"

# define ERR_MAP_UNWANTED_CHAR "Map contains unwanted characters"

# define WIDTH 1920
# define HEIGHT 1080

#endif