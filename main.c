/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:50:40 by wayden            #+#    #+#             */
/*   Updated: 2024/02/13 23:25:16 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	void *mlx_ptr;
	void *mlx_win;


	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr,1920,1080,"Cube3D");
	mlx_loop(mlx_ptr);

	return (0);	
}
