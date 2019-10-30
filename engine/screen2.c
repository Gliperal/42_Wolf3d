/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:51:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 18:57:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"
#include "../libft/libft.h"

int			is_in_screen(t_point p, t_screen *screen)
{
	return (
			p.x >= 0 && p.y >= 0 &&
			p.x <= screen->width &&
			p.y <= screen->height);
}

t_point		screen_center(t_screen *screen)
{
	t_point center;

	center.x = screen->width / 2;
	center.y = screen->height / 2;
	return (center);
}
