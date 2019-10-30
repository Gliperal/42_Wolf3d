/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:10:50 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 21:11:57 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	is_wall(t_map *map, int x, int y)
{
	if (x < 0 || y < 0)
		return (1);
	if (x >= map->width || y >= map->height)
		return (1);
	return (map->data[y * map->width + x]);
}
