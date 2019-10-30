/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:02:36 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 21:12:58 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ray_casting.h"
#include "textures.h"

static t_wall	make_wall(int x, int y, int x_normal, int y_normal)
{
	t_wall wall;

	if (x_normal == 1)
	{
		wall.type = WEST;
		wall.position = x;
	}
	else if (x_normal == -1)
	{
		wall.type = EAST;
		wall.position = x + 1;
	}
	else if (y_normal == 1)
	{
		wall.type = NORTH;
		wall.position = y;
	}
	else
	{
		wall.type = SOUTH;
		wall.position = y + 1;
	}
	wall.offset = (x_normal == 0) ? x : y;
	return (wall);
}

static float	ray_x_intercept(t_ray *ray, float y)
{
	float y_dist;
	float x_dist;

	y_dist = y - ray->y;
	x_dist = y_dist / tan(ray->angle);
	return (ray->x + x_dist);
}

static t_wall	get_wall(t_map *map, t_ray *ray)
{
	t_point	grid;
	t_point	dir;
	int		intercept_x;

	grid.y = (int)ray->y;
	grid.x = (int)ray->x;
	dir.x = (ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2) ? 1 : -1;
	dir.y = (ray->angle < M_PI) ? 1 : -1;
	while (1)
	{
		if (dir.y == 1)
			intercept_x = (int)floor(ray_x_intercept(ray, grid.y + 1));
		else
			intercept_x = (int)floor(ray_x_intercept(ray, grid.y));
		while (grid.x != intercept_x)
		{
			grid.x += dir.x;
			if (is_wall(map, grid.x, grid.y))
				return (make_wall(grid.x, grid.y, dir.x, 0));
		}
		grid.y += dir.y;
		if (is_wall(map, grid.x, grid.y))
			return (make_wall(grid.x, grid.y, 0, dir.y));
	}
}

t_wall			get_wall_for_pixel(t_param *param, int x)
{
	t_ray ray;

	ray.angle = param->player_angle + atan2(640, x - 640);
	if (ray.angle > 2 * M_PI)
		ray.angle -= 2 * M_PI;
	if (ray.angle < 0)
		ray.angle += 2 * M_PI;
	ray.x = param->player_x;
	ray.y = param->player_y;
	return (get_wall(param->map, &ray));
}
