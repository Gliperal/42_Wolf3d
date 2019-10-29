/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:08:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/28 17:25:25 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "entity.h"
#include "param.h"
#include "textures.h"

void	prep_entities(void *p)
{
	t_entity *entity;
	int i;
	t_param *param = p;

	i = 0;
	while ((entity = param->entities[i]))
	{
		entity->dist_x = entity->x - param->player_x;
		entity->dist_y = entity->y - param->player_y;
		entity->dist_to_player = hypot(entity->dist_x, entity->dist_y);
		entity->depth = fabs((entity->dist_y * cos(param->player_angle)) - (entity->dist_x * sin(param->player_angle)));
		entity->angle_from_player = atan2(entity->dist_y, entity->dist_x);
		i++;
	}
}

void	render_entities(void *p, int x, float dist_to_wall)
{
	t_param *param = p;
	t_ray_collision collision;
	// this is technically comparing the distance from the center of the entity
	// with the distance of the ray collision, but it's close enough for all
	// practical purposes
	if (param->entities[0]->dist_to_player > dist_to_wall)
		return ;
	collision.depth = param->entities[0]->depth;
	float ray_angle = param->player_angle + atan2(640, x - 640);
	float angle_to_entity = ray_angle - param->entities[0]->angle_from_player;
	angle_to_entity = fmod((angle_to_entity + 5 * M_PI_2), 2 * M_PI) - M_PI_2;
	if (angle_to_entity >= M_PI_2)
		return ;
	float dist_to_intercept = param->entities[0]->dist_to_player * sin(angle_to_entity);
	if (fabs(dist_to_intercept) < param->entities[0]->radius)
	{
		collision.texture = param->textures[0];
		collision.screen_x = x;
		collision.x_position_on_entity = 0.5 + (dist_to_intercept / param->entities[0]->radius / 2.0);
		texture_render(param->screen, &collision, -0.5, 0.5);
	}
}
