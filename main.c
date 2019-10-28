/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:54:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/28 15:19:44 by nwhitlow         ###   ########.fr       */
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
void	player_move(t_param *param, t_input *input);
void	player_rotate(t_param *param, t_input *input);

void	on_update(void *p)
{
	t_param		*param;
	t_input		*input;

	param = p;
	input = param->input;
	if (input->key_states[ESC] == PRESSED)
		exit(0);
	player_move(param, input);
	player_rotate(param, input);
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
	param->entity_x = 5.5;
	param->entity_y = 3.5;
	param->entity_radius = 0.2;
	param->map = load_map();
	if (param->map == NULL)
	{
		free(param);
		return (1);
	}
	param->textures = load_textures();
	if (param->textures == NULL)
	{
		ft_putstr("Failed to load textures.\n");
		free(param->map);
		free(param);
		return (1);
	}
	input_clock_init(param->input);
	mlx_loop(mlx_ptr);
}
