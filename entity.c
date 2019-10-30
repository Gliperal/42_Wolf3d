/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:52:19 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 20:54:39 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "entity.h"

static void	add_entity(t_entity ***list, int *size, float x, float y)
{
	t_entity	*entity;
	t_entity	**new_list;
	int			i;

	entity = malloc(sizeof(t_entity));
	if (entity == NULL)
		return ;
	new_list = malloc((*size + 2) * sizeof(t_entity *));
	if (new_list == NULL)
	{
		free(entity);
		return ;
	}
	i = -1;
	while (++i < *size)
		new_list[i] = (*list)[i];
	new_list[*size] = entity;
	new_list[*size + 1] = NULL;
	*size += 1;
	entity->x = x;
	entity->y = y;
	entity->radius = 0.2;
	free(*list);
	*list = new_list;
}

t_entity	**extract_entities(t_map *map)
{
	t_entity	**entities;
	int			size;
	int			y;
	int			x;

	entities = malloc(sizeof(t_entity *));
	if (entities == NULL)
		return (NULL);
	entities[0] = NULL;
	size = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->data[y * map->width + x] == 'o')
			{
				add_entity(&entities, &size, x + 0.5, y + 0.5);
				map->data[y * map->width + x] = 0;
			}
		}
	}
	return (entities);
}

void		free_entities(t_entity **entities)
{
	int i;

	i = 0;
	while (entities[i])
	{
		free(entities[i]);
		i++;
	}
	free(entities);
}
