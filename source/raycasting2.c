/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:53 by therodri          #+#    #+#             */
/*   Updated: 2024/11/12 19:45:21 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/includes.h"

/**
** cast_ray - Casts a ray from the player's position and direction to 
** determine the point of intersection with a wall in the game world.
** @player: The player instance containing position and direction information.
** @data: The map data, including information about the level and walls.
** @u: A pointer to the ray utility structure holding ray-related data.
**
** This function computes the direction and step sizes for the ray, then
** traces the ray through the map grid, updating the intersection point.
** It calculates the distance to the wall and stores the results in the 
** provided ray utility structure.
*/
void	cast_ray(t_player *player, t_mapdata data, t_rayutils *u)
{
	u->hit = 0;
	u->ray_dir.x = player->direction.x + player->camera.x * u->camera_x;
	u->ray_dir.y = player->direction.y + player->camera.y * u->camera_x;
	u->map_x = (int)player->pos.x;
	u->map_y = (int)player->pos.y;
	set_deltadist(&u->delta_dist.x, u->ray_dir.x);
	set_deltadist(&u->delta_dist.y, u->ray_dir.y);
	set_step((t_raydata){&u->delta_dist.x, &u->side_dist.x, &u->ray_dir.x,
		&u->step_x}, player->pos.x, u->map_x);
	set_step((t_raydata){&u->delta_dist.y, &u->side_dist.y, &u->ray_dir.y,
		&u->step_y}, player->pos.y, u->map_y);
	trace_ray(data, u);
	calculate_walldist(u);
}

/**
** select_wall_texture - Selects the correct texture based on the side of the 
** wall that the ray intersects.
** @u: The ray utility structure holding ray-related data such as the side of 
** the wall and step direction.
**
** This function selects one of the four textures (north, south, east, west) 
** based on the side of the wall hit by the ray.
**
** Returns: A pointer to the selected texture, or NULL if no texture is 
** found.
*/
t_xpm_texture	*select_wall_texture(t_rayutils u)
{
	if (!u.side && u.step_x < 0)
		return (get_texture(WE));
	else if (!u.side && u.step_x > 0)
		return (get_texture(EA));
	else if (u.side && u.step_y > 0)
		return (get_texture(SO));
	else if (u.side && u.step_y < 0)
		return (get_texture(NO));
	return (NULL);
}

/**
** get_x_texture - Calculates the x-coordinate in the texture for a given 
** vertical column in the rendered image.
** @player: The player instance, used to determine the player's position.
** @texture: The texture to be used for the current wall.
** @u: The ray utility structure containing the ray's properties and distance 
** to the wall.
**
** This function calculates the exact x-coordinate in the texture based on 
** the player's position and the perpendicular wall distance.
**
** Returns: The calculated x-coordinate in the texture (a value between 0 and 
** the texture width).
*/
int	get_x_texture(t_player *player, t_xpm_texture *texture, t_rayutils u)
{
	double	true_x;

	if (u.side == 0)
		true_x = player->pos.y + u.perp_wall_dist * u.ray_dir.y;
	else
		true_x = player->pos.x + u.perp_wall_dist * u.ray_dir.x;
	true_x -= floor(true_x);
	return (true_x * texture->width);
}

/**
** print_line - Draws a vertical line in the image for the current column, 
** including the wall texture, ceiling, and floor.
** @player: The player instance, used to determine position and direction.
** @x: The x-coordinate of the vertical line to be drawn.
** @u: The ray utility structure containing ray-related data.
** @img: The image instance where the rendered scene is drawn.
**
** This function selects the appropriate texture based on the ray's intersection
** with a wall, calculates the texture coordinates, and then draws the wall, 
** ceiling, and floor at the corresponding position on the screen.
*/
void	print_line(t_player *player, int x, t_rayutils *u, t_img *img)
{
	t_xpm_texture	*texture;
	t_range			r;

	texture = select_wall_texture(*u);
	texture->pos_in.x = get_x_texture(player, texture, *u);
	texture->lineheight = (int)(HEIGHT / u->perp_wall_dist);
	r.start = -texture->lineheight / 2 + HEIGHT / 2;
	r.end = texture->lineheight / 2 + HEIGHT / 2;
	if (r.start < 0)
		r.start = 0;
	if (r.end >= HEIGHT)
		r.end = HEIGHT;
	ver_line_x(img, get_mapdata(NULL)->c_ceiling, (t_range){0, r.start}, x);
	tex_ver_line_x(img, texture, r, x);
	ver_line_x(img, get_mapdata(NULL)->c_floor, (t_range){r.end, HEIGHT}, x);
}

/**
** update_raycast - Updates the raycasting and renders the scene.
** @player: The player instance, used to determine position and view direction.
** @data: The map data, containing the level information.
** @mlx: The MinilibX instance used for rendering.
** @img: The image instance where the rendered scene is drawn.
**
** This function casts rays for every vertical column on the screen, 
** calculates the intersection points, selects the appropriate textures, 
** and draws the walls, ceiling, and floor. After rendering each column, 
** it updates the image in the MinilibX window.
*/
void	update_raycast(t_player *player, t_mapdata *data, t_mlx *mlx,
		t_img *img)
{
	t_rayutils	u;
	int			x;

	x = -1;
	while (++x < WIDTH)
	{
		u.camera_x = 2 * x / (double)WIDTH - 1;
		cast_ray(player, *data, &u);
		print_line(player, x, &u, img);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img, 0, 0);
}
