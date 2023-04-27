/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:58:11 by jonascim          #+#    #+#             */
/*   Updated: 2023/04/27 13:41:40 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <mlx.h>
#include <libft.h>

#include "state.h"
#include "parser.h"
#include "window.h"
#include "camera.h"

#define IMG_WIDTH	1280
#define IMG_HEIGHT	720

static void	print_scene_values(const t_scene_data *scene)
{
	t_sphere_data	*sphere;
	t_plane_data	*plane;
	t_cylinder_data	*cylinder;

	printf("------------------------------------------\n");
	printf("Camera: (%.1f, %.1f, %.1f) (%.1f, %.1f, %.1f) (%.1f)\n",
		scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z,
		scene->camera.dir.x, scene->camera.dir.y, scene->camera.dir.z,
		scene->camera.fov);
	printf("Ambient: (%.1f) (%.1f, %.1f, %.1f)\n",
		scene->ambient.ratio,
		scene->ambient.col.x, scene->ambient.col.x, scene->ambient.col.x);
	printf("Light: (%.1f, %.1f, %.1f) (%.1f) (%.1f, %.1f, %.1f)\n\n",
		scene->light.pos.x, scene->light.pos.y, scene->light.pos.z,
		scene->light.ratio,
		scene->light.col.x, scene->light.col.x, scene->light.col.x);
	sphere = scene->spheres;
	while (sphere)
	{
		printf("Sphere: (%.1f, %.1f, %.1f) (%.1f) (%.1f, %.1f, %.1f)\n",
			sphere->pos.x, sphere->pos.y, sphere->pos.z,
			sphere->diameter,
			sphere->col.x, sphere->col.y, sphere->col.z);
		sphere = sphere->next;
	}
	plane = scene->planes;
	while (plane)
	{
		printf("Plane: (%.1f, %.1f, %.1f) (%.1f, %.1f, %.1f) (%.1f, %.1f, %.1f)\n",
			plane->pos.x, plane->pos.y, plane->pos.z,
			plane->dir.x, plane->dir.y, plane->dir.z,
			plane->col.x, plane->col.y, plane->col.z);
		plane = plane->next;
	}
	cylinder = scene->cylinders;
	while (cylinder)
	{
		printf("Cylinder: (%.1f, %.1f, %.1f) (%.1f, %.1f, %.1f) (%.1f) (%.1f) (%.1f, %.1f, %.1f)\n",
			cylinder->pos.x, cylinder->pos.y, cylinder->pos.z,
			cylinder->dir.x, cylinder->dir.y, cylinder->dir.z,
			cylinder->diameter,
			cylinder->height,
			cylinder->col.x, cylinder->col.y, cylinder->col.z);
		cylinder = cylinder->next;
	}
	printf("------------------------------------------\n");
}

static void	panic(int return_value, char *err_msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	exit(return_value);
}

static int	expose_hook(void *param)
{
	static t_image	*image = NULL;
	t_state			*state;

	state = param;
	if (!image)
		image = render(state->camera, state);
	if (!image || !image->mlx_img)
		panic(1, "Failed to render image");
	mlx_put_image_to_window(
		state->window->mlx_ptr, state->window->win_ptr, image->mlx_img, 0, 0);
	return (0);
}

int	main(void)
{
	static t_window		window;
	static t_scene_data	scene;
	static t_camera		camera;
	static t_state		state = {&window, &scene, &camera};

	if (parse_scene_file(&scene, "test.rt") == -1)
		panic(1, "Failed to parse scene file");
	print_scene_values(&scene);
	if (init_mlx_window(&window, "MiniRT", IMG_WIDTH, IMG_HEIGHT) == -1)
		panic(1, "Failed to initialize MLX window");
	init_camera(&camera, (double)IMG_WIDTH / IMG_HEIGHT);
	mlx_expose_hook(window.win_ptr, expose_hook, &state);
	mlx_loop(window.mlx_ptr);
	return (0);
}
