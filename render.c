/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/28 16:45:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "minilibx_macos/mlx.h"
#include "rendering/rendering.h"
#include "input/input.h"
#include "param.h"
#include "textures.h"
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

void	render_entities(t_param *param, int x, float dist_to_wall)
{
	t_ray_collision collision;
	// this can be calculated in advance:
	collision.dist_x = param->entity_x - param->player_x; // TODO this is different from the collision dist
	collision.dist_y = param->entity_y - param->player_y;
	collision.depth = fabs((collision.dist_y * cos(param->player_angle)) - (collision.dist_x * sin(param->player_angle)));
	float dist_to_center = hypot(collision.dist_x, collision.dist_y);
	// this is technically comparing the distance from the center of the entity
	// with the distance of the ray collision, but it's close enough for all
	// practical purposes
	if (dist_to_center > dist_to_wall)
		return ;
	// ---
	float ray_angle = param->player_angle + atan2(640, x - 640);
	float angle_to_entity = ray_angle - atan2(collision.dist_y, collision.dist_x);
	angle_to_entity = fmod((angle_to_entity + 5 * M_PI_2), 2 * M_PI) - M_PI_2;
	if (angle_to_entity >= M_PI_2)
		return ;
	float dist_to_intercept = dist_to_center * sin(angle_to_entity);
	if (fabs(dist_to_intercept) < param->entity_radius)
	{
		collision.texture = param->textures[NORTH];
		collision.screen_x = x;
		collision.x_position_on_entity = 0.5 + (dist_to_intercept / param->entity_radius / 2.0);
		texture_render(param->screen, &collision, -0.5, 0.5);
	}
}

void	render_strip(t_param *param, int x, t_wall wall)
{
	t_ray_collision collision;
	float angle;
	float foo;

	angle = param->player_angle + atan2(640, x - 640);
	if (wall.type == WEST || wall.type == EAST)
	{
		collision.dist_x = (float)wall.position - param->player_x;
		collision.dist_y = collision.dist_x * tan(angle);
		foo = param->player_y + collision.dist_y;
		collision.x_position_on_entity = foo - floor(foo);
	}
	else
	{
		collision.dist_y = (float)wall.position - param->player_y;
		collision.dist_x = collision.dist_y / tan(angle);
		foo = param->player_x + collision.dist_x;
		collision.x_position_on_entity = foo - floor(foo);
	}
	collision.depth = fabs((collision.dist_y * cos(param->player_angle)) - (collision.dist_x * sin(param->player_angle)));
	collision.texture = param->textures[wall.type];
	collision.screen_x = x;
	texture_render(param->screen, &collision, -1.0, 2.5);
	render_entities(param, x, hypot(collision.dist_x, collision.dist_y));
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

# define VANISHING_Y 360

void	render(t_param *param)
{
	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < VANISHING_Y; y++)
			screen_put(param->screen, x, y, COLOR_SKY);
		for (int y = VANISHING_Y; y < 720; y++)
			screen_put(param->screen, x, y, COLOR_GROUND);
	}
	render_swath(param, 0, 0, 1280, 0);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
}
