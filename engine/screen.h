/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:41:46 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 18:55:07 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H

# include "mlx_util.h"
# include "../libft/libft.h"

typedef struct	s_screen
{
	int			width;
	int			height;
	MLX			*mlx_ptr;
	MLX_WIN		*win_ptr;
	MLX_IMG		*img_ptr;
	t_byte		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_screen;

t_screen		*new_screen(MLX *mlx_ptr, int width, int height, char *title);
void			screen_put(t_screen *screen, int x, int y, int color);
void			screen_putstr(t_screen *s, t_point pos, int color, char *str);
int				is_in_screen(t_point p, t_screen *screen);
t_point			screen_center(t_screen *screen);
void			destroy_screen(t_screen *screen);

#endif
