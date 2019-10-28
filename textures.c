/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:22:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/28 16:39:24 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include "textures.h"

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define VANISHING_Y 360

static int			read_texture(int fd, t_texture *texture)
{
	size_t	bytes_read;
	size_t	data_size;

	bytes_read = read(fd, &(texture->width), sizeof(int));
	if (bytes_read != sizeof(int))
		return (-1);
	bytes_read = read(fd, &(texture->height), sizeof(int));
	if (bytes_read != sizeof(int))
		return (-1);
	texture->data = malloc(texture->width * texture->height * sizeof(int));
	if (texture->data == NULL)
		return (-1);
	data_size = texture->width * texture->height * sizeof(int);
	bytes_read = read(fd, texture->data, data_size);
	if (bytes_read != data_size)
	{
		free(texture->data);
		return (-1);
	}
	return (0);
}

static t_texture	*load_texture(const char *filename)
{
	t_texture	*texture;
	int			fd;
	int			status;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	texture = malloc(sizeof(t_texture));
	status = read_texture(fd, texture);
	close(fd);
	if (status == -1)
	{
		free(texture);
		return (NULL);
	}
	return (texture);
}

t_texture			**load_textures(void)
{
	t_texture **textures;

	textures = malloc(4 * sizeof(t_texture *));
	if (textures == NULL)
		return (NULL);
	textures[NORTH] = load_texture("textures/north.bin");
	textures[SOUTH] = load_texture("textures/south.bin");
	textures[EAST] = load_texture("textures/east.bin");
	textures[WEST] = load_texture("textures/west.bin");
	if (textures[NORTH] && textures[SOUTH] && textures[EAST] && textures[WEST])
		return (textures);
	free(textures[NORTH]);
	free(textures[SOUTH]);
	free(textures[EAST]);
	free(textures[WEST]);
	return (NULL);
}

void				texture_render(t_screen *screen, t_ray_collision *info, float bottom, float top)
{
	int render_top;
	int render_bottom;
	int render_height;
	int y;
	int tex_x;
	int tex_y;

	render_top = VANISHING_Y - top * 200.0 / info->depth;
	render_bottom = VANISHING_Y - bottom * 200.0 / info->depth;
	render_height = render_bottom - render_top;
	tex_x = (int)(info->x_position_on_entity * info->texture->width);
	y = ft_max(0, render_top);
	while (y < render_bottom && y < 720)
	{
		tex_y = (info->texture->height * (y - render_top)) / render_height;
		screen_put(screen, info->screen_x, y, info->texture->data[tex_y * info->texture->width + tex_x]);
		y++;
	}
}
