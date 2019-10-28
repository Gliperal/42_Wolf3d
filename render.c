/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/27 20:14:39 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "minilibx_macos/mlx.h"
#include "rendering/rendering.h"
#include "input/input.h"
#include "param.h"

typedef struct	s_ray
{
	float x;
	float y;
	float angle;
}				t_ray;

// TODO REMOVE
#include <stdio.h>
#include <string.h>

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

struct s_wall	{
	char type;
	int position;
	int offset;
};

struct s_wall	make_wall(int x, int y, int x_normal, int y_normal)
{
	struct s_wall wall;

	if (x_normal == 1)
	{
		wall.type = WEST;
		wall.position = x;
		wall.offset = y;
	}
	else if (x_normal == -1)
	{
		wall.type = EAST;
		wall.position = x + 1;
		wall.offset = y;
	}
	else if (y_normal == 1)
	{
		wall.type = NORTH;
		wall.position = y;
		wall.offset = x;
	}
	else
	{
		wall.type = SOUTH;
		wall.position = y + 1;
		wall.offset = x;
	}
	return (wall);
}

struct s_wall	get_wall(t_map *map, t_ray *ray)
{
//	printf("get_wall(%.2f, %.2f, %.2f)\n", ray->x, ray->y, ray->angle);
	int grid_y = (int) ray->y;
	int grid_x = (int) ray->x;
	int dir_x = (ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2) ? 1 : -1;
	int dir_y = (ray->angle < M_PI) ? 1 : -1;
	int intercept_x;
	while (1)
	{
		// possible error if tan(angle) = INF ?
		if (dir_y == 1)
			intercept_x = (int)floor(ray->x + ((float)(grid_y + 1) - ray->y) / tan(ray->angle));
		else
			intercept_x = (int)floor(ray->x + ((float)grid_y - ray->y) / tan(ray->angle));
		while (grid_x != intercept_x)
		{
			grid_x += dir_x;
			if (is_wall(map, grid_x, grid_y))
				return (make_wall(grid_x, grid_y, dir_x, 0));
		}
		grid_y += dir_y;
		if (is_wall(map, grid_x, grid_y))
			return (make_wall(grid_x, grid_y, 0, dir_y));
	}
}

float	depth_to_wall(t_param *param, int x, struct s_wall wall, float *wall_offset)
{
	float angle;
	float dist_x;
	float dist_y;
	float foo;

	angle = param->player_angle + atan2(640, x - 640);
	if (wall.type == WEST || wall.type == EAST)
	{
		dist_x = (float)wall.position - param->player_x;
		dist_y = dist_x * tan(angle);
		foo = param->player_y + dist_y;
		*wall_offset = foo - floor(foo);
	}
	else
	{
		dist_y = (float)wall.position - param->player_y;
		dist_x = dist_y / tan(angle);
		foo = param->player_x + dist_x;
		*wall_offset = foo - floor(foo);
	}
	return (fabs((dist_y * cos(param->player_angle)) - (dist_x * sin(param->player_angle))));
}

void	render_strip(t_param *param, int x, struct s_wall wall)
{
	float wall_offset;
	float depth;
	float height;
	int top;
	int bottom;
	int y;

	depth = depth_to_wall(param, x, wall, &wall_offset);
	height = 200.0 / depth;
	top = 360 - height * 2.5;
	bottom = 360 + height;
	y = 0;
	while (y < top)
	{
		screen_put(param->screen, x, y, 0x66DDFF);
		y++;
	}
	int tex_x = (int)(8.0 * wall_offset);
	while (y < bottom && y < 720)
	{
		int tex_y = (8 * (y - top)) / (bottom - top);
		screen_put(param->screen, x, y, param->textures[wall.type][tex_y * 8 + tex_x]);
		y++;
	}
	while (y < 720)
	{
		screen_put(param->screen, x, y, 0x333333);
		y++;
	}
}

struct s_wall	get_wall_for_pixel(t_param *param, int x)
{
	t_ray ray;

	ray.angle = param->player_angle + atan2(640, x - 640);
	if (ray.angle > 2 * M_PI)
		ray.angle -= 2 * M_PI;
	if (ray.angle < 0)
		ray.angle += 2 * M_PI;
	ray.x = param->player_x;
	ray.y = param->player_y;
	return get_wall(param->map, &ray);
}

void	render_swath(t_param *param, int left, struct s_wall *lwall, int right, struct s_wall *rwall)
{
	struct s_wall wall_left;
	struct s_wall wall_right;

	if (lwall == NULL)
	{
		wall_left = get_wall_for_pixel(param, left);
		lwall = &wall_left;
	}
	if (rwall == NULL)
	{
		wall_right = get_wall_for_pixel(param, right);
		rwall = &wall_right;
	}
	if (left + 1 >= right)
	{
		render_strip(param, left, *lwall);
		return ;
	}
	if (memcmp(lwall, rwall, sizeof(struct s_wall)) == 0)
	{
		for (int x = left; x < right; x++)
			render_strip(param, x, *lwall);
		return ;
	}
	int mid = (left + right) / 2;
	render_swath(param, left, lwall, mid, NULL);
	render_swath(param, mid, NULL, right, rwall);
}

void	render(t_param *param)
{
	render_swath(param, 0, 0, 1280, 0);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
}
