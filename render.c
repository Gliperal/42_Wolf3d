/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/27 21:47:34 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "minilibx_macos/mlx.h"
#include "rendering/rendering.h"
#include "input/input.h"
#include "param.h"
#include "libft/libft.h"

typedef struct	s_ray
{
	float x;
	float y;
	float angle;
}				t_ray;

# define COLOR_SKY 0x66DDFF
# define COLOR_GROUND 0x333333
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct	s_wall
{
	char type;
	int position;
	int offset;
}				t_wall;

t_wall	make_wall(int x, int y, int x_normal, int y_normal)
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

t_wall	get_wall(t_map *map, t_ray *ray)
{
	t_point grid;
	t_point dir;
	int intercept_x;

	grid.y = (int)ray->y;
	grid.x = (int)ray->x;
	dir.x = (ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2) ? 1 : -1;
	dir.y = (ray->angle < M_PI) ? 1 : -1;
	while (1)
	{
		if (dir.y == 1)
			intercept_x = (int)floor(ray->x + ((float)(grid.y + 1) - ray->y) / tan(ray->angle));
		else
			intercept_x = (int)floor(ray->x + ((float)grid.y - ray->y) / tan(ray->angle));
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

float	depth_to_wall(t_param *param, int x, t_wall wall, float *wall_offset)
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

void	render_entities(t_param *param, int x, float depth_to_wall)
{
	// this can be calculated in advance:
	float dist_x = param->entity_x - param->player_x;
	float dist_y = param->entity_y - param->player_y;
	float dist_to_center = hypot(dist_x, dist_y); // TODO greater than dist to wall = discard
	// ---
	float ray_angle = param->player_angle + atan2(640, x - 640);
	float angle_to_entity = ray_angle - atan2(dist_y, dist_x);
	angle_to_entity = fmod((angle_to_entity + 5 * M_PI_2), 2 * M_PI) - M_PI_2;
	if (angle_to_entity >= M_PI_2)
		return ;
	float dist_to_intercept = dist_to_center * sin(angle_to_entity);
	if (fabs(dist_to_intercept) < param->entity_radius)
	{
		float depth = fabs((dist_y * cos(param->player_angle)) - (dist_x * sin(param->player_angle)));
		float height = 350.0 * param->entity_radius / depth;
		int top = 360 - height * 2.5;
		int bottom = 360 + height;
		for (int y = top; y < bottom; y++)
			screen_put(param->screen, x, y, 0x2E159A);
	}
}

void	render_strip(t_param *param, int x, t_wall wall)
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
		screen_put(param->screen, x, y, COLOR_SKY);
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
		screen_put(param->screen, x, y, COLOR_GROUND);
		y++;
	}
	render_entities(param, x, depth);
}

t_wall	get_wall_for_pixel(t_param *param, int x)
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

void	render_swath(t_param *param, int left, t_wall *lwall, int right, t_wall *rwall)
{
	t_wall wall_left;
	t_wall wall_right;
	int mid;

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
	if (left + 1 >= right || ft_memcmp(lwall, rwall, sizeof(t_wall)) == 0)
	{
		for (int x = left; x < right; x++)
			render_strip(param, x, *lwall);
		return ;
	}
	mid = (left + right) / 2;
	render_swath(param, left, lwall, mid, NULL);
	render_swath(param, mid, NULL, right, rwall);
}

void	render(t_param *param)
{
	render_swath(param, 0, 0, 1280, 0);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
}
