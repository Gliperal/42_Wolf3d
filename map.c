/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:16:48 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/26 14:22:48 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "map.h"

static int		add_line(t_map *map, char *line)
{
	int new_width;
	int new_height;
	char *new_data;
	int x;

	new_width = ft_max(map->width, ft_strlen(line));
	new_height = map->height + 1;
	new_data = malloc(new_width * new_height * sizeof(char));
	ft_bzero(new_data, new_width * new_height * sizeof(char));
	if (new_data == NULL)
		return (-1);
	for (int y = 0; y < map->height; y++)
		for (x = 0; x < map->width; x++)
			new_data[y * new_width + x] = map->data[y * map->width + x];
	x = 0;
	while (line[x])
	{
		if (line[x] != ' ')
			new_data[(new_height - 1) * new_width + x] = 1;
		x++;
	}
	map->width = new_width;
	map->height = new_height;
	free(map->data);
	map->data = new_data;
	return (0);
}

static t_map	*load_map2(int fd)
{
	char *line;
	int status;

	t_map *map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->data = NULL;
	map->width = 0;
	map->height = 0;
	while ((status = get_next_line(fd, &line)) > 0)
	{
		if (add_line(map, line) == -1)
		{
			free(map->data);
			free(map);
			free(line);
			return (NULL);
		}
		free(line);
	}
	if (status == -1)
	{
		ft_putstr("Error in reading from map file.\n");
		return (NULL);
	}
	return (map);
}

t_map	*load_map()
{
	int fd;
	t_map *map;

	fd = open("map.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Error: Map file could not be opened.\n");
		return (NULL);
	}
	map = load_map2(fd);
	close(fd);
	return (map);
}

int	is_wall(t_map *map, int x, int y)
{
	if (x < 0 || y < 0)
		return 1;
	if (x >= map->width || y >= map->height)
		return 1;
	return map->data[y * map->width + x];
}