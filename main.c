/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:54:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 21:13:37 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "engine/engine.h"
#include "param.h"
#include "textures.h"
#include "libft/libft.h"
#include "world.h"
#include "misc.h"

static void	on_update(void *p)
{
	t_param		*param;
	t_input		*input;

	param = p;
	input = param->input;
	if (input->key_states[ESC] == PRESSED)
	{
		free_textures(param->textures);
		free_map(param->map);
		free_entities(param->entities);
		free(param->input);
		destroy_screen(param->screen);
		free(param);
		exit(0);
	}
	player_move(param, input);
	player_rotate(param, input);
	if (input->exposed)
	{
		render(param);
		input->exposed = 0;
	}
}

static int	param_init2(t_param *param)
{
	param->textures = load_textures();
	if (param->textures == NULL)
	{
		ft_putstr("Failed to load textures.\n");
		return (-1);
	}
	param->entities = extract_entities(param->map);
	if (param->entities == NULL)
	{
		free_textures(param->textures);
		return (-1);
	}
	return (0);
}

static int	param_init(t_param *param)
{
	param->input = input_new(&on_update, param, param->screen);
	if (param->input == NULL)
		return (-1);
	param->map = load_map();
	if (param->map == NULL)
	{
		free(param->input);
		return (-1);
	}
	if (param_init2(param) == -1)
	{
		free_map(param->map);
		free(param->input);
		return (-1);
	}
	param->player_x = 8.5;
	param->player_y = 11.5;
	param->player_angle = 0.0;
	param->score = 0;
	return (0);
}

int			main(void)
{
	void	*mlx_ptr;
	t_param	*param;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (1);
	param = malloc(sizeof(t_param));
	if (param == NULL)
		return (1);
	param->screen = new_screen(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Wolf3D");
	if (param->screen == NULL)
	{
		free(param);
		return (1);
	}
	if (param_init(param) == -1)
	{
		destroy_screen(param->screen);
		free(param);
		return (1);
	}
	input_clock_init(param->input);
	mlx_loop(mlx_ptr);
}
