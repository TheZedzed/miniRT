#include "minirt.h"

int	free_all(t_scene *el)
{
	free_scene_cam(el);
	free_scene_lum(el);
	free_scene_obj(el);
	if (el->mlx)
	{
		if (el->img)
			mlx_destroy_image(el->mlx, el->img);
		if (el->win)
			mlx_destroy_window(el->mlx, el->win);
		mlx_destroy_display(el->mlx);
		free(el->mlx);
	}
	exit(0);
}

void	free_scene_cam(t_scene *env)
{
	t_cam	*next;
	t_cam	*current;

	current = env->cam_head;
	if (current)
	{
		while (current != env->cam_tail)
		{
			next = current->next;
			free(current);
			current = next;
		}
		free(current);
	}
}

void	free_scene_lum(t_scene *env)
{
	t_light	*next;
	t_light	*current;

	current = env->lum_head;
	if (current)
	{
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
		}
	}
}

void	free_scene_obj(t_scene *env)
{
	t_obj	*next;
	t_obj	*current;

	current = env->obj_head;
	if (current)
	{
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
		}
	}
}
