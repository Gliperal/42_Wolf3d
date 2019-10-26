/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:22:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/26 16:29:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "textures.h"

# define TEXTURE_SIZE 8

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

static int	*load_texture(const char *filename)
{
	int fd;
	int *texture;
	int status;

	texture = malloc(TEXTURE_SIZE * TEXTURE_SIZE * sizeof(int));
	if (texture == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(texture);
		return (NULL);
	}
	status = read(fd, texture, TEXTURE_SIZE * TEXTURE_SIZE * sizeof(int));
	if (status == -1)
	{
		free(texture);
		close(fd);
		return (NULL);
	}
	return (texture);
}

int	**load_textures()
{
	int **textures = malloc(4 * sizeof(int *));
	if (textures == NULL)
		return (NULL);
	textures[0] = load_texture("textures/north.bin");
	textures[1] = load_texture("textures/south.bin");
	textures[2] = load_texture("textures/east.bin");
	textures[3] = load_texture("textures/west.bin");
	// TODO catch errors
	return (textures);
}
