/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:39:46 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/05 13:24:32 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLERS_H
# define INPUT_HANDLERS_H

int	input_handle_key_release(int key, t_input *input);
int	input_handle_mouse_press(int button, int x, int y, t_input *input);
int	input_handle_mouse_release(int button, int x, int y, t_input *input);
int	input_handle_mouse_move(int x, int y, t_input *input);

#endif
