/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:21:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 20:54:36 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "map.h"

typedef struct	s_entity
{
	float		x;
	float		y;
	float		radius;
	float		dist_x;
	float		dist_y;
	float		dist_to_player;
	float		angle_from_player;
	float		depth;
}				t_entity;

void			prep_entities(void *param);
void			render_entities(void *param, int x, float dist_to_wall);
void			free_entities(t_entity **entities);
t_entity		**extract_entities(t_map *map);

#endif
