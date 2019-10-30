/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:13:52 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/29 21:13:53 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISC_H
# define MISC_H

void	render(t_param *param);
void	player_move(t_param *param, t_input *input);
void	player_rotate(t_param *param, t_input *input);

#endif
