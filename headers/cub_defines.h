/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_defines.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:35:13 by wayden            #+#    #+#             */
/*   Updated: 2024/02/14 15:03:56 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DEFINES_H
# define CUB_DEFINES_H


# define ERR_MAP_LINE "invalide line has been detected in the cub file"
# define ERR_MAP_FILE_FORMAT "the map file does not respect the .cub format"
# define ERR_MAP_UNCLOSED "the map isn't closed properly"
# define ERR_MAP_COLOR "color components should be in range [0,255]"
# define ERR_MAP_TEXTURE_ACCESS "incorrect or innaccessible texture path"

# define ERR_MULTIPLE_PATH "!"

# define N 2
# define W 3
# define S 4
# define E 5
# define SP 6

#endif