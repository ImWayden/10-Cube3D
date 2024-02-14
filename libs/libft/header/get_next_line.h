/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 07:48:32 by therodri          #+#    #+#             */
/*   Updated: 2024/02/12 23:11:48 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*
# ifdef BUFFER_SIZE
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
/*
	fd = file descriptor from where the line are read
	return the next line in the file;
	multiple call returns nexts line
*/
char		*get_next_line(int fd);

typedef struct s_line
{
	char	*line;
	int		index;
	int		ret_read;
}			t_line;
#endif