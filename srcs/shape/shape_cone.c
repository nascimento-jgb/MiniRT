/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonascim <jonascim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:13:40 by jonascim          #+#    #+#             */
/*   Updated: 2023/04/29 15:48:20 by jonascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "shape.h"

//check the value of t compared in the nearest intersection
int	cone_intersect_pt2(t_ray ray, t_cone_data *cone)
{
	t_vec3	pc;
	double	m;

	pc = vec3_add(ray.orig, vec3_scalar(ray.dir, cone->t));
	m = vec3_dot(pc, cone->dir) / vec3_length_squared(cone->dir);
	if (m < 0 || m > vec3_magnitude(cone->dir))
		return (1);
	cone->pc = pc;
	return (0);
	//check if there is necessity to find the normal of pc
}

int	cone_intersect(t_ray ray, t_cone_data *cone)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_subtract(ray.orig, cone->pos);
	a = vec3_length_squared(ray.dir) - pow(vec3_dot(ray.dir, cone->dir), 2);
	b = 2 * (vec3_dot(ray.dir, oc)) - vec3_dot(ray.dir, cone->dir)
		* vec3_dot(oc, cone->dir);
	c = vec3_length_squared(oc) - pow(vec3_dot(oc, cone->dir), 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (1);
	else
	{
		cone->t1 = (-b - sqrt(discriminant)) / (2 * a);
		cone->t2 = (-b + sqrt(discriminant)) / (2 * a);
	}
	return (0);
}

