/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 06:31:55 by therodri          #+#    #+#             */
/*   Updated: 2024/02/12 23:00:04 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"
/*
	protected version of strlen
	if str = NULL return 0 instead of segfault.
*/
size_t	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		continue ;
	return (i);
}
