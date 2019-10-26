/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/26 15:06:01 by nwhitlow         ###   ########.fr       */
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

struct s_wall	get_wall(t_map *map, t_ray *ray)
{
//	printf("get_wall(%.2f, %.2f, %.2f)\n", ray->x, ray->y, ray->angle);
	int grid_y = (int) ray->y;
	int grid_x = (int) ray->x;
	struct s_wall wall;
	if (ray->angle < M_PI)
		while (1)
		{
			// possible error if tan(angle) = INF ?
			int intercept_x = (int)floor(ray->x + ((float)(grid_y + 1) - ray->y) / tan(ray->angle));
			while (grid_x != intercept_x)
			{
				grid_x += (intercept_x - grid_x) / abs(intercept_x - grid_x);
				if (is_wall(map, grid_x, grid_y))
				{
					if (ray->angle < M_PI_2)
					{
						wall.type = WEST;
						wall.position = grid_x;
						wall.offset = grid_y;
					}
					else
					{
						wall.type = EAST;
						wall.position = grid_x + 1;
						wall.offset = grid_y;
					}
					return wall;
				}
			}
			grid_y++;
			if (is_wall(map, grid_x, grid_y))
			{
				wall.type = NORTH;
				wall.position = grid_y;
				wall.offset = grid_x;
				return wall;
			}
		}
	else
		while (1)
		{
			int intercept_x = (int)floor(ray->x + ((float)grid_y - ray->y) / tan(ray->angle));
			while (grid_x != intercept_x)
			{
				grid_x += (intercept_x - grid_x) / abs(intercept_x - grid_x);
				if (is_wall(map, grid_x, grid_y))
				{
					if (ray->angle > 3 * M_PI_2)
					{
						wall.type = WEST;
						wall.position = grid_x;
						wall.offset = grid_y;
					}
					else
					{
						wall.type = EAST;
						wall.position = grid_x + 1;
						wall.offset = grid_y;
					}
					return wall;
				}
			}
			grid_y--;
			if (is_wall(map, grid_x, grid_y))
			{
				wall.type = SOUTH;
				wall.position = grid_y + 1;
				wall.offset = grid_x;
				return wall;
			}
		}
}

void	render_strip(t_param *param, int x, struct s_wall wall)
{
	float angle = param->player_angle + atan2(640, x - 640);
	float dist_x, dist_y;
	if (wall.type == WEST || wall.type == EAST)
	{
		dist_x = (float)wall.position - param->player_x;
		dist_y = dist_x * tan(angle);
	}
	else
	{
		dist_y = (float)wall.position - param->player_y;
		dist_x = dist_y / tan(angle);
	}
	float depth = fabs((dist_y * cos(param->player_angle)) - (dist_x * sin(param->player_angle)));
	float height = 200.0 / depth;
	int colors[4] = {0x7700FF, 0x00FF77, 0xCC0077, 0x55CC00};
	int low = 360 - height * 2.5;
	if (low < 0) low = 0;
	int high = 360 + height;
	if (high > 720)
		high = 720;
	for (int y = low; y < high; y++)
		screen_put(param->screen, x, y, colors[wall.type]);
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
	for (int y = 0; y < 360; y++)
		for (int x = 0; x < 1280; x++)
			screen_put(param->screen, x, y, 0x66DDFF);
	for (int y = 360; y < 720; y++)
		for (int x = 0; x < 1280; x++)
			screen_put(param->screen, x, y, 0x333333);
	render_swath(param, 0, 0, 1280, 0);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
}
