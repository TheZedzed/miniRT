/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_updater.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:11:53 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 07:38:32 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "inter.h"

void	update_scene_obj(t_scene *env, t_obj *new_node)
{
	new_node->next = NULL;
	if (!env->obj_head)
	{
		env->obj_head = new_node;
		env->obj_tail = new_node;
	}
	else
	{
		env->obj_tail->next = new_node;
		env->obj_tail = new_node;
	}
}

void	update_scene_cam(t_scene *env, t_cam *new_node)
{
	if (!env->cam_head)
	{
		env->cam_head = new_node;
		env->cam_tail = new_node;
		new_node->next = new_node;
		new_node->back = new_node;
	}
	else
	{
		env->cam_tail->next = new_node;
		env->cam_head->back = new_node;
		new_node->back = env->cam_tail;
		new_node->next = env->cam_head;
		env->cam_tail = new_node;
	}
}

void	update_scene_lum(t_scene *env, t_light *new_node)
{
	new_node->next = NULL;
	if (!env->lum_head)
	{
		env->lum_head = new_node;
		env->lum_tail = new_node;
	}
	else
	{
		env->lum_tail->next = new_node;
		env->lum_tail = new_node;
	}
}
