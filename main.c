/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:54:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/25 15:20:16 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO -WWW

// TODO Remove
#include <stdio.h>

#include "minilibx_macos/mlx.h"
#include "rendering/rendering.h"
#include "input/input.h"
#include "param.h"

void	render(t_param *param);

#define PLAYER_SPEED 0.016
#define PLAYER_SPEED_DIAG 0.0113

#include <math.h>

void	move(t_input *input)
{
	int front_back;
	int left_right;
	t_param *param = input->param;

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
//	param->player_x += PLAYER_SPEED
	if (key_down(input, ARROW_RIGHT))
	{
		param->player_angle -= 0.016;
		if (param->player_angle > 2 * M_PI)
			param->player_angle -= 2 * M_PI;
		input->exposed = 1;
	}
	if (key_down(input, ARROW_LEFT))
	{
		param->player_angle += 0.016;
		if (param->player_angle < 0)
			param->player_angle += 2 * M_PI;
		input->exposed = 1;
	}
	if (front_back != 0 || left_right != 0)
		input->exposed = 1;
}

void	on_update(void *p)
{
	t_param		*param;
	t_input		*input;

	param = p;
	input = param->input;
	if (input->key_states[ESC] == PRESSED)
		exit(0);
	move(input);
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
	param->player_x = 5.5;
	param->player_y = 1.5;
	param->player_angle = 0;
	input_clock_init(param->input);
	mlx_loop(mlx_ptr);
}
