/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:51:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 18:57:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "screen.h"
#include "../minilibx_macos/mlx.h"
#include "../libft/libft.h"

void		screen_put(t_screen *screen, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= screen->width)
		return ;
	if (y < 0 || y >= screen->height)
		return ;
	offset = (screen->width * y + x) * screen->bpp / 8;
	screen->data[offset] = color & 0xff;
	screen->data[offset + 1] = (color >> 8) & 0xff;
	screen->data[offset + 2] = (color >> 16) & 0xff;
	screen->data[offset + 3] = color >> 24;
}

void		screen_putstr(t_screen *screen, t_point pos, int color, char *str)
{
	mlx_string_put(screen->mlx_ptr, screen->win_ptr, pos.x, pos.y, color, str);
}

t_screen	*new_screen(MLX *mlx_ptr, int width, int height, char *title)
{
	t_screen	*screen;

	screen = (t_screen *)malloc(sizeof(t_screen));
	if (screen == NULL)
		return (NULL);
	screen->mlx_ptr = mlx_ptr;
	screen->win_ptr = mlx_new_window(mlx_ptr, width, height, title);
	if (screen->win_ptr == NULL)
		return (NULL);
	screen->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (screen->img_ptr == NULL)
		return (NULL);
	screen->data = (void *)mlx_get_data_addr(screen->img_ptr, &screen->bpp, \
			&screen->size_line, &screen->endian);
	if (screen->data == NULL)
		return (NULL);
	screen->width = width;
	screen->height = height;
	return (screen);
}

void		destroy_screen(t_screen *screen)
{
	mlx_destroy_window(screen->mlx_ptr, screen->win_ptr);
	mlx_destroy_image(screen->mlx_ptr, screen->img_ptr);
	free(screen);
}
