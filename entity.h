/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:21:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/28 17:25:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

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

#endif
