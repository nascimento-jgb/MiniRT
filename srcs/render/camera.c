/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:51:58 by helneff           #+#    #+#             */
/*   Updated: 2023/04/27 13:38:17 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>

#include "camera.h"
#include "parser.h"
#include "color.h"

int	hit_sphere(t_vec3 center, double radius, t_ray ray)
{
	const t_vec3	oc = vec3_subtract(ray.orig, center);
	const double	a = vec3_dot(ray.dir, ray.dir);
	const double	b = 2.0 * vec3_dot(oc, ray.dir);
	const double	c = vec3_dot(oc, oc) - radius * radius;
	const double	discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}

static int	ray_color(const t_state *state, t_ray ray)
{
	const t_vec3	unit_dir = vec3_unit(ray.dir);
	const double	t = 0.5 * (unit_dir.y + 1.0);
	const t_vec3	color = vec3_add(
			vec3_scalar((t_vec3){1.0, 1.0, 1.0}, 1.0 - t),
			vec3_scalar((t_vec3){0.5, 0.7, 1.0}, t));

	if (hit_sphere((t_vec3){0, 0, -5}, 1, ray))
		return (int2col(state, 0x00FF0000));
	return (vec2col(state, color, 0));
}

static void	iterate_pixels(
	const t_state *state, t_camera *cam, t_ray_trace_func rtf)
{
	t_ray	r;
	int		x;
	int		y;
	double	u;
	double	v;

	y = 0;
	while (y < state->window->height)
	{
		x = 0;
		while (x < state->window->width)
		{
			u = (double)x / (state->window->width - 1);
			v = (double)y / (state->window->height - 1);
			r = (t_ray){cam->orig, vec3_subtract(vec3_add(vec3_add(
							cam->ll_corner, vec3_scalar(cam->hori, u)),
						vec3_scalar(cam->vert, v)),
					cam->orig)};
			set_pixel(&cam->image, x, y, rtf(state, r));
			x++;
		}
		y++;
	}
}

void	init_camera(t_camera *camera, double aspect_ratio)
{
	camera->orig = (t_vec3){0.0, 0.0, 0.0};
	camera->dir = (t_vec3){0.0, 0.0, -1.0};
	camera->aspect_ratio = aspect_ratio;
	camera->focal_length = 1;
	camera->height = 2;
	camera->width = camera->height * aspect_ratio;
	camera->hori = (t_vec3){camera->width, 0, 0};
	camera->vert = (t_vec3){0, camera->height, 0};
	camera->ll_corner = vec3_subtract(vec3_subtract(vec3_subtract(
					camera->orig, vec3_scalar(camera->hori, 0.5)),
				vec3_scalar(camera->vert, 0.5)),
			(t_vec3){0, 0, camera->focal_length});
}

t_image	*render(t_camera *camera, const t_state *state)
{
	const int		background = int2col(state, 0x00ABCDEF);

	if (init_image(&camera->image, state->window) == -1)
		return (NULL);
	fill_color(&camera->image, background);
	iterate_pixels(state, camera, ray_color);
	return (&camera->image);
}
