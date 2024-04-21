/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:33:35 by wayden            #+#    #+#             */
/*   Updated: 2024/04/18 10:22:08 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/includes.h"

double ft_abs_dbl(double x)
{
	if(x < 0)
		return(-x); 			
	return(x);
}

void set_step(t_raydata data, double player_pos, int map_pos)
{
	if(*data.raydir < 0)
	{
		*data.step = -1;
		*data.sidedist = (player_pos - map_pos) * *data.deltadist;
	}
	else
	{
		*data.step = 1;
		*data.sidedist = (map_pos + 1.0 - player_pos) * *data.deltadist;
	}
}

void trace_ray(t_mapdata data, t_rayutils *u)
{
	while(!u->hit)
	{
		if(u->side_dist.x < u->side_dist.y)
		{
			u->side_dist.x += u->delta_dist.x;
      		u->map_x += u->step_x;
     		u->side = 0;
		}
		else
		{
			u->side_dist.y += u->delta_dist.y;
      		u->map_y += u->step_y;
     		u->side = 1;	
		}
		if(data.map[u->map_y][u->map_x] == 1)
			u->hit++;
	}
}

void set_deltadist(double *delta_dist, double ray_dir)
{
	if(!ray_dir)
		*delta_dist = 1.0e+30;
	else
		*delta_dist = (1/ft_abs_dbl(ray_dir));  
}

void calculate_walldist(t_rayutils *u)
{
	if(!u->side)
		u->perp_wall_dist = u->side_dist.x - u->delta_dist.x;
	else
		u->perp_wall_dist = u->side_dist.y - u->delta_dist.y;
}


void cast_ray(t_player *player, t_mapdata data, t_rayutils *u) 
{
	u->hit = 0;
	u->ray_dir.x = player->direction.x + player->camera.x * u->camera_x;
	u->ray_dir.y = player->direction.y + player->camera.y * u->camera_x;
	u->map_x = (int)player->pos.x;
	u->map_y = (int)player->pos.y;
	set_deltadist(&u->delta_dist.x, u->ray_dir.x);
	set_deltadist(&u->delta_dist.y, u->ray_dir.y);
	set_step((t_raydata){&u->delta_dist.x, &u->side_dist.x,\
	&u->ray_dir.x,&u->step_x}, player->pos.x, u->map_x);
	set_step((t_raydata){&u->delta_dist.y, &u->side_dist.y,\
	&u->ray_dir.y,&u->step_y}, player->pos.y, u->map_y);
	trace_ray(data, u);
	calculate_walldist(u);
}

t_xpm_texture *select_wall_texture(t_rayutils u)
{
	if(!u.side && u.step_x < 0) //ouest
		return(get_texture(WE));
	else if(!u.side && u.step_x > 0) // east
		return(get_texture(EA));
	else if(u.side && u.step_y > 0) // south
		return(get_texture(SO));
	else if(u.side && u.step_y < 0) // north
		return(get_texture(NO));
	return(NULL);
}

int get_x_texture(t_player *player, t_xpm_texture *texture, t_rayutils u)
{
	double true_x;
	
	if(u.side == 0)
		true_x = player->pos.y + u.perp_wall_dist * u.ray_dir.y;
	else
		true_x = player->pos.x + u.perp_wall_dist * u.ray_dir.x;
	true_x -= floor(true_x); 
	// on retire la partie entiere a true_x ainsi on obtient un
	//nombre entre 0 et 1 qu'on devra ensuite multiplier par la taille de la texture afin
	// d'avoir la coordoneer du pixel hit. on peut faire un modf sinon
	return(true_x * texture->width);
}

void print_line(t_player *player, int x, t_rayutils *u, t_img *img)
{
	t_xpm_texture *texture;
	t_range r;

	texture = select_wall_texture(*u);
	texture->pos_in.x = get_x_texture(player, texture, *u);
	texture->lineheight = (int)(HEIGHT / u->perp_wall_dist);
	r.start = -texture->lineheight / 2 + HEIGHT / 2;
	r.end = texture->lineheight / 2 + HEIGHT / 2;
    if(r.start < 0) 
		r.start = 0;
    if(r.end >= HEIGHT)
		r.end = HEIGHT;
	ver_line_x(img, get_mapdata(NULL)->c_floor, (t_range){0,r.start}, x);
	tex_ver_line_x(img, texture, r, x);
	ver_line_x(img, get_mapdata(NULL)->c_ceiling, (t_range){r.end, HEIGHT}, x);
}

void update_raycast(t_player *player, t_mapdata *data, t_mlx *mlx, t_img *img)
{
	t_rayutils	u;
	int			x;
	
	x = -1;
	while (++x < WIDTH)
	{
		u.camera_x = 2 * x / (double)WIDTH - 1;
		cast_ray(player, *data, &u);
		print_line(player,x,&u, img);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img, 0, 0);
}


