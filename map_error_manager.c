/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:25:11 by wayden            #+#    #+#             */
/*   Updated: 2024/02/13 22:30:04 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

void print_error(char *error)
{
	write(STDERR_FILENO,"Error\n",7);
	write(STDERR_FILENO,error, ft_strlen(error));
	//besoin d'ajouter la gestion de liberation de la memoire et autre probablement
	// a moins que je ne decidee de le faire autre part

	
}