/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:39:46 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/05 13:24:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	update_mouse_position(t_input *input, int x, int y)
{
	if (input->mouse_yet_to_move)
	{
		input->mouse_moved.x = 0;
		input->mouse_moved.y = 0;
		input->mouse_yet_to_move = 0;
	}
	else
	{
		input->mouse_moved.x += x - input->mouse.x;
		input->mouse_moved.y += y - input->mouse.y;
	}
	input->mouse.x = x;
	input->mouse.y = y;
	return (input->mouse_moved.x != 0 || input->mouse_moved.y != 0);
}

int			input_handle_key_release(int key, t_input *input)
{
	if (key < 0 || key > MAX_KEYS)
		return (1);
	input->key_states[key] = RELEASED;
	input_handle_loop(input);
	return (0);
}

int			input_handle_mouse_press(int button, int x, int y, t_input *input)
{
	if (button < 0 || button > MAX_BUTTONS)
		return (1);
	input->button_states[button] = PRESSED;
	update_mouse_position(input, x, y);
	input_handle_loop(input);
	return (0);
}

int			input_handle_mouse_release(int button, int x, int y, t_input *input)
{
	if (button < 0 || button > MAX_BUTTONS)
		return (1);
	input->button_states[button] = RELEASED;
	update_mouse_position(input, x, y);
	input_handle_loop(input);
	return (0);
}

int			input_handle_mouse_move(int x, int y, t_input *input)
{
	int moved;

	moved = update_mouse_position(input, x, y);
	if (moved)
		input_handle_loop(input);
	return (0);
}
