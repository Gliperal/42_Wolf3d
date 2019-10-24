/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:57:37 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/23 20:04:30 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../libft/libft.h"
# include "../rendering/mlx_util.h"

# define UPDATE_INTERVAL 16666666L
# define NSEC_IN_SEC 1000000000L

typedef char		t_button_state;

# define NOT_HELD 0
# define HELD 1
# define PRESSED 2
# define RELEASED 3

typedef struct		s_input
{
	t_button_state	button_states[MAX_BUTTONS + 1];
	t_button_state	key_states[MAX_KEYS + 1];
	int				mouse_yet_to_move;
	t_point			mouse;
	t_point			mouse_moved;
	struct timespec	last_update_at;
	struct timespec	next_update_at;
	float			fps;
	int				exposed;
	void			(*on_update)(void *);
	void			*param;
}					t_input;

typedef	void		(*t_func)(void *);

t_input				*input_new(t_func on_update, void *param, t_screen *screen);
void				input_clock_init(t_input *input);
int					input_handle_loop(t_input *input);
int					key_down(t_input *input, int key);
int					key_pressed(t_input *input, int key);
int					button_down(t_input *input, int button);
int					button_pressed(t_input *input, int button);

#endif
