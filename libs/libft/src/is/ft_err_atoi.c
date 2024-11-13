/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: therodri <therodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:08:04 by wayden            #+#    #+#             */
/*   Updated: 2024/04/21 17:11:22 by therodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

/*
	return 0  si tout c'est bien passé
	return -1 si aucun nbr n'a ete trouver
	return -2 si le nombre overflow un int
	
	l'utilisation d'un t_3int est la uniquement pour respecter
	la norme et les 25 lignes, ca rend tout ca ilisible a souhait mais bon  
*/
int	ft_err_atoi(const char *nptr, int *ret, int *j)
{
	t_3int			var;
	unsigned int	res;

	var = (t_3int){1, *j, 0};
	res = 0;
	while ((nptr[var.j] >= 9 && nptr[var.j] <= 13) || nptr[var.j] == ' ')
		var.j++;
	if (nptr[var.j] == '+' || nptr[var.j] == '-')
	{
		if (nptr[var.j] == '-')
			var.i = -var.i;
		var.j++;
	}
	while (nptr[var.j] >= '0' && nptr[var.j] <= '9' && ++var.k)
	{
		if ((int)res > (INT_MAX - (nptr[var.j] - '0')) / 10)
			return (-2);
		res = res * 10 + nptr[var.j] - '0';
		var.j++;
	}
	*j = var.j;
	if (!var.k)
		return (-1);
	*ret = res * var.i;
	return (0);
}
