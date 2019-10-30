/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:08:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 18:29:11 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "entity.h"
#include "param.h"
#include "textures.h"

/*
** Using bubble sort, because the list will be almost completely sorted already.
*/

static void	sort_entities(t_entity **entities, int size)
{
	int			i;
	t_entity	*tmp;

	i = 0;
	while (i < size - 1)
	{
		if (entities[i]->dist_to_player < entities[i + 1]->dist_to_player)
		{
			tmp = entities[i];
			entities[i] = entities[i + 1];
			entities[i + 1] = tmp;
			if (i > 0)
				i--;
		}
		else
			i++;
	}
}

#define SFX_GEM "gem.mp3"

static void	collect_gem(t_param *param, int i)
{
	system("afplay " SFX_GEM " 2> /dev/null");
	free(param->entities[i]);
	while (1)
	{
		param->entities[i] = param->entities[i + 1];
		if (param->entities[i] == NULL)
			break ;
		i++;
	}
	param->score++;
}

void	prep_entities(void *p)
{
	t_entity	*entity;
	int			i;
	t_param		*param;

	param = p;
	i = 0;
	while ((entity = param->entities[i]))
	{
		entity->dist_x = entity->x - param->player_x;
		entity->dist_y = entity->y - param->player_y;
		entity->dist_to_player = hypot(entity->dist_x, entity->dist_y);
		if (entity->dist_to_player < 0.5)
		{
			collect_gem(param, i);
			continue;
		}
		entity->depth = fabs((entity->dist_y * cos(param->player_angle)) -
									(entity->dist_x * sin(param->player_angle)));
		entity->angle_from_player = atan2(entity->dist_y, entity->dist_x);
		i++;
	}
	sort_entities(param->entities, i);
}

static void	render_entity(t_param *param, int x, t_entity *entity)
{
	t_ray_collision	collision;
	float			ray_angle;
	float			angle_to_entity;
	float			dist_to_intercept;

	collision.depth = entity->depth;
	ray_angle = param->player_angle + atan2(640, x - 640);
	angle_to_entity = ray_angle - entity->angle_from_player;
	angle_to_entity = fmod((angle_to_entity + 5 * M_PI_2), 2 * M_PI) - M_PI_2;
	if (angle_to_entity >= M_PI_2)
		return ;
	dist_to_intercept = entity->dist_to_player * sin(angle_to_entity);
	if (fabs(dist_to_intercept) < entity->radius)
	{
		collision.texture = param->textures[GEM];
		collision.screen_x = x;
		collision.x_position_on_entity = 0.5 +
									(dist_to_intercept / entity->radius / 2.0);
		texture_render(param->screen, &collision, -0.5, 0.5);
	}
}

void	render_entities(void *p, int x, float dist_to_wall)
{
	t_param *param;
	t_entity *entity;
	int i;

	param = p;
	i = 0;
	while ((entity = param->entities[i]))
	{
		// this is technically comparing the distance from the center of the entity
		// with the distance of the ray collision, but it's close enough for all
		// practical purposes
		if (entity->dist_to_player < dist_to_wall)
			render_entity(param, x, entity);
		i++;
	}
}
