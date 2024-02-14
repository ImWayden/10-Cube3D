/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 02:58:04 by therodri          #+#    #+#             */
/*   Updated: 2024/02/13 23:25:47 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/get_next_line.h"

static void	movebuffer(char *buffer, int index)
{
	int	i;

	i = -1;
	while (buffer && buffer[++index])
		buffer[++i] = buffer[index];
	buffer[i + 1] = 0;
}

static char	*line(char *buffer, int index, char *line)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_substr(buffer, 0, index + 1);
	line = ft_strjoinf(line, tmp, S1);
	free(tmp);
	movebuffer(buffer, index);
	return (line);
}

static char	*get_line(char *buffer, int fd, int keep)
{
	t_line	l;

	l = (t_line){NULL, -1, -1};
	while (l.index == -1 && l.ret_read != 0)
	{
		if (!keep)
		{
			l.ret_read = read(fd, buffer, BUFFER_SIZE);
			if (l.ret_read == -1)
				return (NULL);
			buffer[l.ret_read] = 0;
		}
		l.index = ft_istrchr(buffer, '\n');
		if (l.index == -1)
		{
			l.line = ft_strjoinf(l.line, buffer, S1);
			buffer[0] = 0;
		}
		else
			return (line(buffer, l.index, l.line));
		keep = 0;
	}
	return (l.line);
}

char	*get_next_line(int fd)
{
	static char	buffer[100][BUFFER_SIZE + 1] = {""};
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd][0])
		line = get_line(buffer[fd], fd, 1);
	else
		line = get_line(buffer[fd], fd, 0);
	if (!line[0])
		return (free(line), NULL);
	return (line);
}
