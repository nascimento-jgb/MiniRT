/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:33:45 by helneff           #+#    #+#             */
/*   Updated: 2023/05/02 13:38:36 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vec3.h"
#include "shape.h"

t_intersect	sphere_intersect(t_vec3 center, double radius, t_ray ray)
{
	const t_vec3	oc = vec3_subtract(ray.orig, center);
	const double	a = vec3_length_squared(ray.dir);
	const double	half_b = vec3_dot(oc, ray.dir);
	const double	c = vec3_length_squared(oc) - radius * radius;
	const double	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return ((t_intersect){-1.0, {0}});
	else
		return ((t_intersect){(-half_b - sqrt(discriminant)) / a, {0}});
}

void	nearest_intersect_sphere(
	const t_state *state, t_ray ray, t_shape *shape)
{
	t_shape_data	iter;
	t_intersect		intersect;

	iter.sphere = state->scene->spheres;
	while (iter.sphere)
	{
		intersect = sphere_intersect(iter.sphere->pos,
				iter.sphere->diameter / 2.0, ray);
		if (intersect.t > 0 && (shape->hit.t < 0 || intersect.t < shape->hit.t))
		{
			shape->type = SHAPE_SPHERE;
			shape->data.sphere = iter.sphere;
			shape->hit.t = intersect.t;
		}
		iter.sphere = iter.sphere->next;
	}
}
