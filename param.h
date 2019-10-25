/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:59 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/24 20:46:49 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct		s_param
{
	t_input			*input;
	t_screen		*screen;
	float			player_x;
	float			player_y;
	float			player_angle;
}					t_param;
