/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:41:36 by helneff           #+#    #+#             */
/*   Updated: 2023/05/02 13:14:05 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

t_shape	nearest_intersect(const t_state *state, t_ray ray)
{
	t_shape			shape;
	double			nearest_t;

	shape.type = SHAPE_NONE;
	nearest_t = -1;
	nearest_intersect_sphere(state, ray, &nearest_t, &shape);

	return (shape);
}
