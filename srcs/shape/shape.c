/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:41:36 by helneff           #+#    #+#             */
/*   Updated: 2023/04/28 15:23:12 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

t_shape	nearest_intersect(const t_state *state, t_ray ray)
{
	t_shape			shape;
	t_shape_data	iter;
	double			nearest_t;
	double			current_t;

	shape.type = SHAPE_NONE;
	nearest_t = -1;
	iter.sphere = state->scene->spheres;
	while (iter.sphere)
	{
		current_t = sphere_intersect(iter.sphere->pos,
				iter.sphere->diameter / 2.0, ray);
		if (current_t > 0 && (nearest_t < 0 || current_t < nearest_t))
		{
			shape.type = SHAPE_SPHERE;
			shape.data.sphere = iter.sphere;
			shape.t = current_t;
			nearest_t = current_t;
		}
		iter.sphere = iter.sphere->next;
	}
	return (shape);
}
