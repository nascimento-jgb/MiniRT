/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonascim <jonascim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:26:46 by jonascim          #+#    #+#             */
/*   Updated: 2023/05/03 11:12:03 by jonascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "shape.h"

t_intersect	plane_intersect(t_ray ray, t_plane_data *plane)
{
	t_intersect	intersect;
	t_vec3		to_plane;
	double		denom;

	intersect.t = -1;
	denom = vec3_dot(ray.dir, plane->dir);
	if (fabs(denom) < 1e-6)
		return (intersect);
	to_plane = vec3_subtract(plane->pos, ray.orig);
	intersect.t = vec3_dot(to_plane, plane->dir) / denom;
	intersect.pos = ray_at(ray, intersect.t);
	return (intersect);
}

void	nearest_intersect_plane(const t_state *state, t_ray ray, t_shape *shape)
{
	t_shape_data	iter;
	t_intersect		intersect;

	iter.plane = state->scene->planes;
	while (iter.plane)
	{
		intersect = plane_intersect(ray, iter.plane);
		if (intersect.t > 0 && (shape->hit.t < 0 || intersect.t < shape->hit.t))
		{
			shape->type = SHAPE_SPHERE;
			shape->data.sphere = iter.sphere;
			shape->hit = intersect;
			shape->hit.ray_color = vec3_scalar(iter.sphere->col, 1 / 255.999);
		}
		iter.plane = iter.plane->next;
	}
}
