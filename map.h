/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:09:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/26 14:12:41 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct	s_map
{
	char *data;
	int width;
	int height;
}				t_map;

t_map	*load_map();
int		is_wall(t_map *map, int x, int y);

#endif
