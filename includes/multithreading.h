/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:10:37 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/09 10:28:48 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREADING_H
# define MULTITHREADING_H

void setup_multithreading(t_scene daddy, t_scene *childs);
void lunch_multithreading(t_scene *childs);
#endif
