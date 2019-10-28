/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:59 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/27 20:37:45 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_H
# define PARAM_H

# include "map.h"
# include "input/input.h"

typedef struct		s_param
{
	t_input			*input;
	t_screen		*screen;
	float			player_x;
	float			player_y;
	float			player_angle;
	t_map			*map;
	int				**textures;
}					t_param;

#endif
