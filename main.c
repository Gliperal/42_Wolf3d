/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:54:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/23 21:03:28 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO -WWW

// TODO Remove
#include <stdio.h>

#include "minilibx_macos/mlx.h"
#include "rendering/rendering.h"
#include "input/input.h"

typedef struct		s_param
{
	t_input			*input;
	t_screen		*screen;
}					t_param;

void	move(t_input *input)
{
	int front_back;
	int left_right;

	front_back = 0;
	left_right = 0;
	if (key_down(input, KEY_W) || key_down(input, ARROW_UP))
		front_back++;
	if (key_down(input, KEY_A) || key_down(input, ARROW_LEFT))
		left_right--;
	if (key_down(input, KEY_S) || key_down(input, ARROW_DOWN))
		front_back--;
	if (key_down(input, KEY_D) || key_down(input, ARROW_RIGHT))
		left_right++;
	if (front_back != 0 || left_right != 0)
		input->exposed = 1;
}

void	render(t_param *param)
{
	char map[7][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 0, 1, 1, 0, 0, 1, 0, 1},
		{1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
//	for (int x = 0; x < 1280; x++)
	for (int y = 0; y < 7; y++)
		for (int x = 0; x < 10; x++)
			if (map[y][x])
				screen_put(param->screen, x, y, 0x7700FF);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
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
	input_clock_init(param->input);
	mlx_loop(mlx_ptr);
}
