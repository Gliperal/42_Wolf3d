/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:39:46 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/05 13:16:52 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include "input.h"

static void				send_update(t_input *input)
{
	int key;
	int button;

	(*input->on_update)(input->param);
	button = 0;
	while (button < MAX_BUTTONS)
	{
		if (input->button_states[button] == PRESSED)
			input->button_states[button] = HELD;
		else if (input->button_states[button] == RELEASED)
			input->button_states[button] = NOT_HELD;
		button++;
	}
	key = 0;
	while (key < MAX_KEYS)
	{
		if (input->key_states[key] == PRESSED)
			input->key_states[key] = HELD;
		else if (input->key_states[key] == RELEASED)
			input->key_states[key] = NOT_HELD;
		key++;
	}
	input->mouse_moved.x = 0;
	input->mouse_moved.y = 0;
}

static long				time_subtract(struct timespec a, struct timespec b)
{
	return ((a.tv_sec - b.tv_sec) * NSEC_IN_SEC + a.tv_nsec - b.tv_nsec);
}

static struct timespec	time_add(struct timespec t, long n)
{
	t.tv_nsec += n;
	while (t.tv_nsec < 0)
	{
		t.tv_sec--;
		t.tv_nsec += NSEC_IN_SEC;
	}
	while (t.tv_nsec > NSEC_IN_SEC)
	{
		t.tv_sec++;
		t.tv_nsec -= NSEC_IN_SEC;
	}
	return (t);
}

int						input_handle_loop(t_input *input)
{
	struct timespec	time;
	long			diff;

	clock_gettime(CLOCK_REALTIME, &time);
	diff = time_subtract(time, input->next_update_at);
	if (diff > 0)
	{
		send_update(input);
		input->fps = (float)NSEC_IN_SEC / \
				time_subtract(input->next_update_at, input->last_update_at);
		input->last_update_at = input->next_update_at;
		if (diff > UPDATE_INTERVAL)
			input->next_update_at = time;
		else
			input->next_update_at = time_add(input->next_update_at, \
					UPDATE_INTERVAL);
	}
	return (0);
}

void					input_clock_init(t_input *input)
{
	clock_gettime(CLOCK_REALTIME, &input->next_update_at);
}
