/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:22:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/28 16:37:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

#include "rendering/rendering.h"

typedef struct	s_texture
{
	int			*data;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_ray_collision
{
	int			screen_x;
	t_texture	*texture;
	float		dist_x;
	float		dist_y;
	float		dist;
	float		depth;
	float		x_position_on_entity;
}				t_ray_collision;

t_texture		**load_textures();
void			texture_render(t_screen *screen, t_ray_collision *info, float bottom, float top);

#endif
