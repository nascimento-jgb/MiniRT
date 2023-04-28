/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:33:45 by helneff           #+#    #+#             */
/*   Updated: 2023/04/28 15:23:10 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "shape.h"

int	sphere_intersect(t_vec3 center, double radius, t_ray ray)
{
	const t_vec3	oc = vec3_subtract(ray.orig, center);
	const double	a = vec3_length_squared(ray.dir);
	const double	half_b = vec3_dot(oc, ray.dir);
	const double	c = vec3_length_squared(oc) - radius * radius;
	const double	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (-1.0);
	else
		return ((-half_b - sqrt(discriminant)) / a);
}
