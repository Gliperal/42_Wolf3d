/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:16:48 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 21:11:47 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "map.h"

static void		copy_data(t_map *old, char *new_data, int new_width)
{
	int y;
	int x;

	y = 0;
	while (y < old->height)
	{
		x = 0;
		while (x < old->width)
		{
			new_data[y * new_width + x] = old->data[y * old->width + x];
			x++;
		}
		y++;
	}
}

static int		add_line(t_map *map, char *line)
{
	int		new_width;
	int		new_height;
	char	*new_data;
	int		x;

	new_width = ft_max(map->width, ft_strlen(line));
	new_height = map->height + 1;
	new_data = malloc(new_width * new_height * sizeof(char));
	ft_bzero(new_data, new_width * new_height * sizeof(char));
	if (new_data == NULL)
		return (-1);
	copy_data(map, new_data, new_width);
	x = 0;
	while (line[x])
	{
		if (line[x] != ' ')
			new_data[(new_height - 1) * new_width + x] = line[x];
		x++;
	}
	map->width = new_width;
	map->height = new_height;
	free(map->data);
	map->data = new_data;
	return (0);
}

static t_map	*fill_map(int fd, t_map *map)
{
	char	*line;
	int		status;

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

t_map			*load_map(void)
{
	int		fd;
	t_map	*map;

	fd = open("map.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Error: Map file could not be opened.\n");
		return (NULL);
	}
	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->data = NULL;
	map->width = 0;
	map->height = 0;
	map = fill_map(fd, map);
	close(fd);
	return (map);
}

void			free_map(t_map *map)
{
	free(map->data);
	free(map);
}
