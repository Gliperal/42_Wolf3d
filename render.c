/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/25 15:50:13 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minilibx_macos/mlx.h"
#include "rendering/rendering.h"
#include "input/input.h"
#include "param.h"

typedef struct	s_coord
{
	float x;
	float y;
}				t_coord;

typedef struct	s_ray
{
	float x;
	float y;
	float angle;
}				t_ray;

struct s_wall
{
	float x1, x2, y1, y2;
};

// TODO REMOVE
#include <stdio.h>

void	render_strips(t_param *param, int left, int right, struct s_wall wall)
{
	t_coord step;
	t_coord strip;
	strip.x = wall.x1;
	strip.y = wall.y1;
	step.x = (wall.x2 - wall.x1) / (right - left);
	step.y = (wall.y2 - wall.y1) / (right - left);

	for (int x = left; x <= right; x++)
	{
		float diff_x = strip.x - param->player_x;
		float diff_y = strip.y - param->player_y;
		float distance = sqrt(diff_x * diff_x + diff_y * diff_y);
		float height = 1000.0 / distance;
		for (int y = 360 - height * 2.5; y < 360 + height; y++)
		{
			screen_put(param->screen, x, y, 0x7700FF);
		}
		strip.x += step.x;
		strip.y += step.y;
		if (x == 300)
		{
			printf("x = %d\n", x);
			printf("diff_x = %.2f\n", diff_x);
			printf("diff_y = %.2f\n", diff_y);
			printf("distance = %.2f\n", distance);
			printf("height = %.2f\n", height);
		}
	}
}

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

struct s_wall2	{
	char type;
	int position;
};

struct s_wall2	get_wall(t_param *param, t_ray *ray)
{
//	printf("get_wall(%.2f, %.2f, %.2f)\n", ray->x, ray->y, ray->angle);
	int grid_y = (int) ray->y;
	int grid_x = (int) ray->x;
	struct s_wall2 wall;
	if (ray->angle < M_PI)
		while (1)
		{
			// possible error if tan(angle) = INF ?
			int intercept_x = (int) (param->player_x + ((float)(grid_y + 1) - param->player_y) / tan(ray->angle));
			while (grid_x != intercept_x)
			{
				grid_x += (intercept_x - grid_x) / abs(intercept_x - grid_x);
				if (param->map[grid_y][grid_x])
				{
					if (ray->angle < M_PI_2)
					{
						wall.type = WEST;
						wall.position = grid_x;
					}
					else
					{
						wall.type = EAST;
						wall.position = grid_x + 1;
					}
					return wall;
				}
			}
			grid_y++;
			if (param->map[grid_y][grid_x])
			{
				wall.type = NORTH;
				wall.position = grid_y;
				return wall;
			}
		}
	else
		while (1)
		{
			int intercept_x = (int) (param->player_x + ((float)grid_y - param->player_y) / tan(ray->angle));
			while (grid_x != intercept_x)
			{
				grid_x += (intercept_x - grid_x) / abs(intercept_x - grid_x);
				if (param->map[grid_y][grid_x])
				{
					if (ray->angle > 3 * M_PI_2)
					{
						wall.type = WEST;
						wall.position = grid_x;
					}
					else
					{
						wall.type = EAST;
						wall.position = grid_x + 1;
					}
					return wall;
				}
			}
			grid_y--;
			if (param->map[grid_y][grid_x])
			{
				wall.type = SOUTH;
				wall.position = grid_y + 1;
				return wall;
			}
		}
}

void	render_pixel(t_param *param, int x)
{
	t_ray ray;

	ray.angle = param->player_angle + atan2(640, x - 640);
	if (ray.angle > 2 * M_PI)
		ray.angle -= 2 * M_PI;
	if (ray.angle < 0)
		ray.angle += 2 * M_PI;
	ray.x = param->player_x;
	ray.y = param->player_y;
	struct s_wall2 wall = get_wall(param, &ray);
	float dist;
	if (wall.type == WEST || wall.type == EAST)
	{
		float dist_x = wall.position - param->player_x;
		dist = fabs(dist_x / cos(ray.angle));
	}
	else
	{
		float dist_y = wall.position - param->player_y;
		dist = fabs(dist_y / sin(ray.angle));
	}
	float height = 200.0 / dist;
	int colors[4] = {0x7700FF, 0x00FF77, 0xCC0077, 0x55CC00};
	for (int y = 360 - height * 2.5; y < 360 + height; y++)
		screen_put(param->screen, x, y, colors[wall.type]);
}

void	render(t_param *param)
{
	for (int y = 0; y < 720; y++)
		for (int x = 0; x < 1280; x++)
			screen_put(param->screen, x, y, 0x333333);
	for (int x = 0; x < 1280; x++)
		render_pixel(param, x);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
}
