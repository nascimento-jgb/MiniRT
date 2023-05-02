/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonascim <jonascim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:12:14 by jonascim          #+#    #+#             */
/*   Updated: 2023/04/29 15:37:25 by jonascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "shape.h"

// the check below need to be done in the nearest intersect function and after return to pt2
	// t = -1;
	// if (t1 >= info->t_min && t1 <= info->t_max)
	// 	t = t1;
	// else if (t2 >= info->t_min && t2 <= info->t_max)
	// 	t = t2;
	// else
	// 	return (1);

int	cylinder_intersect_pt2(t_ray ray, t_cylinder_data *cylinder)
{
	t_vec3	p;
	double	y;

	p = ray_at(ray, cylinder->t);
	y = vec3_dot(vec3_subtract(p, cylinder->pos), cylinder->dir);
	if (y < 0 || y > cylinder->height)
		return (1);
	cylinder->ray_pos = p;
	// condiser normal only if the drawing needs the normal
	// cylidner->normal = vec3_unit(vec3_subtract(p, vec3_add(cylinder->pos, vec3_scalar(cylinder->dir, y))));
	return (0);
}

int	cylinder_intersect(t_ray ray, t_cylinder_data *cylinder)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_subtract(ray.orig, cylinder->pos);
	a = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cylinder->dir), 2);
	b = 2 * (vec3_dot(ray.dir, oc) - vec3_dot(ray.dir, cylinder->dir)
			* vec3_dot(oc, cylinder->dir));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cylinder->dir), 2)
		- pow((cylinder->diameter / 2), 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (1);
	else
	{
		cylinder->t1 = (-b - sqrt(discriminant)) / (2 * a);
		cylinder->t2 = (-b + sqrt(discriminant)) / (2 * a);
	}
	return (0);

}
