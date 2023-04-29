/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonascim <jonascim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:33:45 by helneff           #+#    #+#             */
/*   Updated: 2023/04/29 09:51:14 by jonascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "shape.h"

int	sphere_intersect(t_vec3 center, double radius, t_ray ray,
	t_sphere_data *sphere)
{
	const t_vec3	oc = vec3_subtract(ray.orig, center);
	const double	a = vec3_length_squared(ray.dir);
	const double	half_b = vec3_dot(oc, ray.dir);
	const double	c = vec3_length_squared(oc) - radius * radius;
	const double	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (-1.0);
	else
	{
		sphere->a = a;
		sphere->half_b = half_b;
		sphere->sqrtd = sqrt(discriminant);
	}
	return (1);
}
