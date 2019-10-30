/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 21:09:38 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "minilibx_macos/mlx.h"
#include "engine/engine.h"
#include "param.h"
#include "textures.h"
#include "libft/libft.h"
#include "world.h"
#include "ray_casting.h"

static void	render_strip(t_param *param, int x, t_wall wall)
{
	t_ray_collision	collision;
	float			angle;
	float			foo;

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
	collision.depth = fabs((collision.dist_y * cos(param->player_angle)) -
								(collision.dist_x * sin(param->player_angle)));
	collision.texture = param->textures[(int)wall.type];
	collision.screen_x = x;
	texture_render(param->screen, &collision, -1.0, 2.5);
	render_entities(param, x, hypot(collision.dist_x, collision.dist_y));
}

#define LEFT 0
#define RIGHT 1

static void	render_swath(t_param *param, int range[2],
												t_wall *lwall, t_wall *rwall)
{
	t_wall	wall_left;
	t_wall	wall_right;
	int		mid;

	if (lwall == NULL)
	{
		wall_left = get_wall_for_pixel(param, range[LEFT]);
		lwall = &wall_left;
	}
	if (rwall == NULL)
	{
		wall_right = get_wall_for_pixel(param, range[RIGHT]);
		rwall = &wall_right;
	}
	if (range[LEFT] + 1 >= range[RIGHT] ||
								ft_memcmp(lwall, rwall, sizeof(t_wall)) == 0)
	{
		while (range[LEFT] < range[RIGHT])
			render_strip(param, range[LEFT]++, *lwall);
		return ;
	}
	mid = (range[LEFT] + range[RIGHT]) / 2;
	render_swath(param, (int[2]){range[LEFT], mid}, lwall, NULL);
	render_swath(param, (int[2]){mid, range[RIGHT]}, NULL, rwall);
}

static void	render_hud(t_param *param)
{
	t_point	pos;
	char	score[10];

	if (param->score != 0)
	{
		pos.x = 10;
		pos.y = 10;
		ft_strcpy(score, "Score: ##");
		score[7] = '0' + param->score / 10;
		score[8] = '0' + param->score % 10;
		screen_putstr(param->screen, pos, 0xFFFFFF, score);
	}
	if (param->score == 42)
	{
		pos.x = 600;
		pos.y = 352;
		screen_putstr(param->screen, pos, 0xFFFFFF, "You win!");
	}
}

void		render(t_param *param)
{
	int x;
	int y;

	prep_entities(param);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < VANISHING_Y)
		{
			screen_put(param->screen, x, y, COLOR_SKY);
			y++;
		}
		while (y < SCREEN_HEIGHT)
		{
			screen_put(param->screen, x, y, COLOR_GROUND);
			y++;
		}
		x++;
	}
	render_swath(param, (int[2]){0, SCREEN_WIDTH}, 0, 0);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr,
												param->screen->img_ptr, 0, 0);
	render_hud(param);
}
