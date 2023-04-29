/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonascim <jonascim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:41:36 by helneff           #+#    #+#             */
/*   Updated: 2023/04/29 10:42:57 by jonascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

t_shape	nearest_intersect(const t_state *state, t_ray ray)
{
	t_shape			shape;
	t_shape_data	iter;
	double			nearest_t;
	double			current_t;
	int				flag;

	shape.type = SHAPE_NONE;
	nearest_t = -1;
	iter.sphere = state->scene->spheres;
	while (iter.sphere)
	{
		if (sphere_intersect(iter.sphere->pos,
				iter.sphere->diameter / 2.0, ray, iter.sphere) != -1)
		{
			flag = -1;
			while (++flag < 2)
			{
				if (flag)
					current_t = (- iter.sphere->half_b - iter.sphere->sqrtd) / iter.sphere->a;
				else
					current_t = (- iter.sphere->half_b + iter.sphere->sqrtd) / iter.sphere->a;
				if (current_t >= 0 && (nearest_t < 0 || current_t < nearest_t))
				{
					shape.type = SHAPE_SPHERE;
					shape.data.sphere = iter.sphere;
					shape.t = current_t;
					nearest_t = current_t;
				}
			}
		}
		iter.sphere = iter.sphere->next;
	}
	return (shape);
}
