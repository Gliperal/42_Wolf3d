/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:09:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 14:11:04 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	key_down(t_input *input, int key)
{
	return (input->key_states[key] == HELD ||
			input->key_states[key] == PRESSED);
}

int	key_pressed(t_input *input, int key)
{
	return (input->key_states[key] == PRESSED);
}

int	button_down(t_input *input, int button)
{
	return (input->button_states[button] == HELD ||
			input->button_states[button] == PRESSED);
}

int	button_pressed(t_input *input, int button)
{
	return (input->button_states[button] == PRESSED);
}
