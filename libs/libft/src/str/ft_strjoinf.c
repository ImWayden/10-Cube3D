/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:53:50 by wayden            #+#    #+#             */
/*   Updated: 2024/02/12 23:58:43 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strjoinf(char *s1, char *s2, int tofree)
{
	size_t	size;
	size_t	len_s1;
	size_t	len_s2;
	char	*ret;
	int		i;

	i = -1;
	ret = NULL;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	size = len_s1 + len_s2;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		return (NULL);
	while (s1 && s1[++i])
		ret[i] = s1[i];
	i = -1;
	while (s2 && s2[++i])
		ret[len_s1 + i] = s2[i];
	ret[size] = 0;
	if (s1 && tofree & S1)
		free(s1);
	if (s2 && tofree & S2)
		free(s2);
	return (ret);
}
