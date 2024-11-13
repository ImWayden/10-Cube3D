/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:34:32 by wayden            #+#    #+#             */
/*   Updated: 2024/11/13 01:52:33 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** sget_init - Manages initialization and reinitialization of singletons.
** @index: Enum t_init representing a specific singleton.
** @set: Action to perform, can be RESET, INIT, or RESETALL.
**
** t_init is an enum where each element represents a singleton.
** set determines the action:
**   - RESET: Resets the singleton at index.
**   - INIT: Initializes the singleton at index.
**   - RESETALL: Resets all singletons.
** Returns the initialization state of the singleton at the specified index.
*/
bool	sget_init(t_init index, int set)
{
	static bool	init_tab[INIT_COUNT];

	if (set == RESET)
		init_tab[index] = false;
	else if (set == INIT)
		init_tab[index] = true;
	else if (set == RESETALL)
		ft_memset(&init_tab, false, sizeof(bool) * INIT_COUNT);
	return (init_tab[index]);
}

/*
** get_mlx - Initializes and returns a singleton instance of t_mlx.
** This function creates and manages the main MLX instance required
** to use the MinilibX graphics library. It also creates the main window
** for the application on the first call.
**
** Returns: A pointer to the initialized t_mlx instance. If already initialized,
** simply returns the existing instance. NULL is returned if initialization fails.
*/
t_mlx	*get_mlx( void )
{
	static t_mlx	mlx;

	if (!sget_init(MLX, ISINIT) && sget_init(MLX, INIT))
	{
		mlx.mlx_ptr = mlx_init();
		mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	}
	return (&mlx);
}

/*
** get_player - Initializes and returns a singleton instance of t_player.
** This function sets up the player instance, defining initial position,
** direction, and other relevant attributes based on map data from the
** t_mapdata structure.
**
** This function pulls data such as spawn point and spawn direction from
** the t_mapdata singleton. It also sets the player's initial speed and
** mouse lock status.
**
** Returns: A pointer to the initialized t_player instance. On subsequent calls,
** returns the existing instance.
*/
t_player	*get_player( void )
{
	static t_player	player;
	t_mapdata		*data;

	if (!sget_init(PLAYER, ISINIT) && sget_init(PLAYER, INIT))
	{
		data = get_mapdata(NULL);
		player.direction = data->spawndir;
		player.pos = (t_vec2){data->spawnpoint.x + 0.5, data->spawnpoint.y
			+ 0.5};
		player.camera = vec2_perpendicular(data->spawndir, LEFT);
		player.speed = 0.1;
		player.is_mouselock = 0;
	}
	return (&player);
}

/**
** get_mapdata - Initializes and returns a singleton instance of t_mapdata
** containing parsed information from the .cub file.
** @file: The path to the .cub file to be parsed (used only on first call).
**
** This function relies on cub_parser to parse the .cub file and manage
** any encountered errors. Upon encountering a critical error, cub_parser
** will invoke error_manager to handle cleanup and terminate execution.
**
** Returns: A pointer to the initialized t_mapdata instance, or NULL if an
** error occurred during file opening.
*/
t_mapdata	*get_mapdata(char *file)
{
	static t_mapdata	data;

	if (!sget_init(MAP, ISINIT) && sget_init(MAP, INIT) && file)
	{
		data.fd = open(file, O_RDONLY);
		if (data.fd == -1)
			error_manager(ERRCODE_NOFILE, NULL);
		data.name_file = file;
		ft_memset(&data.keycount, false, sizeof(int) * 6);
		cub_parser(data.fd, &data);
		close(data.fd);
	}
	return (&data);
}
