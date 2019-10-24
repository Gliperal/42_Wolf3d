/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:39:46 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/23 20:07:00 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "../minilibx_macos/mlx.h"
#include "input_handlers.h"

static int	handle_key_press(int key, t_input *input)
{
	if (key < 0 || key > MAX_KEYS)
		return (1);
	input->key_states[key] = PRESSED;
	input_handle_loop(input);
	return (0);
}

static int	handle_expose(t_input *input)
{
	input->exposed = 1;
	input_handle_loop(input);
	return (0);
}

static int	handle_exit(void)
{
	exit(0);
}

static void	reset_all_keys_buttons(t_input *input)
{
	int i;

	i = 0;
	while (i < MAX_BUTTONS + 1)
	{
		input->button_states[i] = NOT_HELD;
		i++;
	}
	i = 0;
	while (i < MAX_KEYS + 1)
	{
		input->key_states[i] = NOT_HELD;
		i++;
	}
}

t_input		*input_new(void (*on_update)(void *), void *param, t_screen *screen)
{
	t_input	*input;

	input = (t_input *)malloc(sizeof(t_input));
	if (input == NULL)
		return (NULL);
	reset_all_keys_buttons(input);
	input->mouse_yet_to_move = 1;
	input->on_update = on_update;
	input->param = param;
	input->exposed = 0;
	input_clock_init(input);
	mlx_hook(screen->win_ptr, 2, 0, &handle_key_press, input);
	mlx_hook(screen->win_ptr, 3, 0, &input_handle_key_release, input);
	mlx_hook(screen->win_ptr, 4, 0, &input_handle_mouse_press, input);
	mlx_hook(screen->win_ptr, 5, 0, &input_handle_mouse_release, input);
	mlx_hook(screen->win_ptr, 6, 0, &input_handle_mouse_move, input);
	mlx_hook(screen->win_ptr, 12, 0, &handle_expose, input);
	mlx_hook(screen->win_ptr, 17, 0, &handle_exit, NULL);
	mlx_loop_hook(screen->mlx_ptr, &input_handle_loop, input);
	return (input);
}
