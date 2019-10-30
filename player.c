/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:32:24 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 18:45:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "param.h"
#include "engine/engine.h"

#define PLAYER_SPEED 0.04
#define PLAYER_TURN_SPEED 0.04
#define SHIFT_MODIFIER 2
#define PLAYER_RADIUS 0.15
#define SOLID_BIT 1

static int	collision(t_param *param)
{
	int left;
	int right;
	int top;
	int bottom;

	left = (int)floor(param->player_x - PLAYER_RADIUS);
	right = (int)floor(param->player_x + PLAYER_RADIUS);
	top = (int)floor(param->player_y - PLAYER_RADIUS);
	bottom = (int)floor(param->player_y + PLAYER_RADIUS);
	return ((is_wall(param->map, left, top) & SOLID_BIT)
		|| (is_wall(param->map, left, bottom) & SOLID_BIT)
		|| (is_wall(param->map, right, top) & SOLID_BIT)
		|| (is_wall(param->map, right, bottom) & SOLID_BIT));
}

void		player_move(t_param *param, t_input *input)
{
	int		front_back;
	int		left_right;
	float	angle;
	float	speed;

	front_back = 0;
	left_right = 0;
	if (key_down(input, KEY_W))
		front_back++;
	if (key_down(input, KEY_A))
		left_right--;
	if (key_down(input, KEY_S))
		front_back--;
	if (key_down(input, KEY_D))
		left_right++;
	speed = PLAYER_SPEED;
	if (key_down(input, SHIFT) || key_down(input, RSHIFT))
		speed *= SHIFT_MODIFIER;
	if (left_right || front_back)
	{
		angle = param->player_angle + atan2(front_back, left_right);
		param->player_y += speed * sin(angle);
		if (collision(param))
			param->player_y -= speed * sin(angle);
		param->player_x += speed * cos(angle);
		if (collision(param))
			param->player_x -= speed * cos(angle);
		input->exposed = 1;
	}
}

void		player_rotate(t_param *param, t_input *input)
{
	float speed;

	speed = PLAYER_TURN_SPEED;
	if (key_down(input, SHIFT) || key_down(input, RSHIFT))
		speed *= SHIFT_MODIFIER;
	if (key_down(input, ARROW_RIGHT))
	{
		param->player_angle -= speed;
		if (param->player_angle < 0)
			param->player_angle += 2 * M_PI;
		input->exposed = 1;
	}
	if (key_down(input, ARROW_LEFT))
	{
		param->player_angle += speed;
		if (param->player_angle > 2 * M_PI)
			param->player_angle -= 2 * M_PI;
		input->exposed = 1;
	}
}
