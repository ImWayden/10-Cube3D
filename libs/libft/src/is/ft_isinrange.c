/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinrange.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:01:31 by wayden            #+#    #+#             */
/*   Updated: 2024/02/15 23:02:43 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"
/*
	renvoie 1 si la valeur se trouve dans la range [min_max[0],min_max[1]]
*/
int ft_isinrange(int min_max[2], int i)
{
	return(i >= min_max[0] && i <= min_max[1]);
}
