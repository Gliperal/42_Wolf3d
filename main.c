/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:54:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/27 20:28:48 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO -WWW

// TODO Remove
#include <stdio.h>

#include "minilibx_macos/mlx.h"
#include "rendering/rendering.h"
#include "input/input.h"
#include "param.h"
#include "textures.h"

void	render(t_param *param);

#define PLAYER_SPEED 0.04
#define PLAYER_TURN_SPEED 0.04
#define PLAYER_RADIUS 0.15

#include <math.h>

int		collision(t_param *param)
{
	int left;
	int right;
	int top;
	int bottom;

	left = (int)floor(param->player_x - PLAYER_RADIUS);
	right = (int)floor(param->player_x + PLAYER_RADIUS);
	top = (int)floor(param->player_y - PLAYER_RADIUS);
	bottom = (int)floor(param->player_y + PLAYER_RADIUS);
	return (is_wall(param->map, left, top)
		|| is_wall(param->map, left, bottom)
		|| is_wall(param->map, right, top)
		|| is_wall(param->map, right, bottom));
}

void	move(t_param *param, t_input *input)
{
	int front_back;
	int left_right;
	float angle;

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
	if (left_right || front_back)
	{
		angle = param->player_angle + atan2(front_back, left_right);
		param->player_y += PLAYER_SPEED * sin(angle);
		if (collision(param))
			param->player_y -= PLAYER_SPEED * sin(angle);
		param->player_x += PLAYER_SPEED * cos(angle);
		if (collision(param))
			param->player_x -= PLAYER_SPEED * cos(angle);
		input->exposed = 1;
	}
}

void rotate(t_param *param, t_input *input)
{
	if (key_down(input, ARROW_RIGHT))
	{
		param->player_angle -= PLAYER_TURN_SPEED;
		if (param->player_angle > 2 * M_PI)
			param->player_angle -= 2 * M_PI;
		input->exposed = 1;
	}
	if (key_down(input, ARROW_LEFT))
	{
		param->player_angle += PLAYER_TURN_SPEED;
		if (param->player_angle < 0)
			param->player_angle += 2 * M_PI;
		input->exposed = 1;
	}
}

void	on_update(void *p)
{
	t_param		*param;
	t_input		*input;

	param = p;
	input = param->input;
	if (input->key_states[ESC] == PRESSED)
		exit(0);
	move(param, input);
	rotate(param, input);
	if (input->exposed)
	{
		render(param);
		input->exposed = 0;
	}
}

int			main(int argc, char **argv)
{
	int		*types;
	int		i;
	void	*mlx_ptr;
	t_param	*param;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		exit(1);
	param = malloc(sizeof(t_param));
	if (param == NULL)
		exit(1);
	param->screen = new_screen(mlx_ptr, 1280, 720, "Wolf3D");
	param->input = input_new(&on_update, param, param->screen);
	param->player_x = 4.5;
	param->player_y = 0.5;
	param->player_angle = 0;
	param->map = load_map();
	if (param->map == NULL)
	{
		free(param);
		return 1;
	}
	param->textures = load_textures(); // catch errors
	input_clock_init(param->input);
	mlx_loop(mlx_ptr);
}
