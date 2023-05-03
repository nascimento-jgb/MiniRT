/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonascim <jonascim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:33:45 by helneff           #+#    #+#             */
/*   Updated: 2023/05/03 11:59:23 by jonascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vec3.h"
#include "shape.h"

#include <stdio.h>

t_intersect	sphere_intersect(t_vec3 center, double radius, t_ray ray)
{
	const t_vec3	oc = vec3_subtract(ray.orig, center);
	const double	a = vec3_length_squared(ray.dir);
	const double	half_b = vec3_dot(oc, ray.dir);
	const double	discriminant = half_b * half_b - a
		* (vec3_length_squared(oc) - radius * radius);
	t_intersect		intersect;

	intersect.t = -1;
	if (discriminant < 0)
		return (intersect);
	intersect.t = (-half_b - sqrt(discriminant)) / a;
	intersect.pos = vec3_add(ray.orig, vec3_scalar(ray.dir, intersect.t));
	//intersect.normal = vec3_unit(vec3_subtract(center, intersect.pos));
	intersect.normal = vec3_scalar(vec3_subtract(intersect.pos, center), 1/radius);
	if (vec3_dot(ray.dir, intersect.normal) > 0)
		intersect.normal = vec3_scalar(intersect.normal, -1);
	return (intersect);
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
			shape->hit = intersect;
			shape->hit.ray_color = vec3_scalar(iter.sphere->col, 1 / 255.999);
		}
		iter.sphere = iter.sphere->next;
	}
}
