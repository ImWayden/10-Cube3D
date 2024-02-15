/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 03:07:08 by wayden            #+#    #+#             */
/*   Updated: 2024/02/15 03:13:32 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"
#include <stdio.h>
int ft_isvalid(char c)
{
	return(c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'\
	 || c == 'E' || c == ' ');
}
/*
	return the size of a line and check for unwanted character
*/
int maplength(char *line)
{
	int i;
	int error;
	
	i = -1;
	error = ft_isvalid(line[++i]);
	while (error)
		error = ft_isvalid(line[++i]);
	if (line[i] && line[i] != '\n')
		return (-1);
	return (i);
}

int main( void )
{
	char *line;

	line = "    011 11 1  1 1N00000 1";
	printf("%d\n", maplength(line));
	line = "A0000000000000001    1 01";
	printf("%d\n", maplength(line));
	line = "    011 11 1  1 1N00000 1\n";
	printf("%d\n", maplength(line));
	line = "0000000A000000001    1 01\n";
	printf("%d\n", maplength(line));
	line = "0000000NWES000000001    1 01\n";
	printf("%d\n", maplength(line));
}