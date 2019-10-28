/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:59 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/28 15:19:21 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_H
# define PARAM_H

# include "map.h"
# include "input/input.h"
# include "rendering/rendering.h"
# include "textures.h"

typedef struct		s_param
{
	t_input			*input;
	t_screen		*screen;
	float			player_x;
	float			player_y;
	float			player_angle;
	t_map			*map;
	t_texture		**textures;
	float			entity_x;
	float			entity_y;
	float			entity_radius;
}					t_param;

#endif
