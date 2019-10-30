/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:02:47 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 21:08:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# include "param.h"

typedef struct	s_ray
{
	float x;
	float y;
	float angle;
}				t_ray;

typedef struct	s_wall
{
	char	type;
	int		position;
	int		offset;
}				t_wall;

t_wall			get_wall_for_pixel(t_param *param, int x);

#endif
