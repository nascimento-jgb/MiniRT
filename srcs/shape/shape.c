/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:41:36 by helneff           #+#    #+#             */
/*   Updated: 2023/05/02 16:36:49 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

#include <stdio.h>

t_shape	nearest_intersect(const t_state *state, t_ray ray)
{
	t_shape			shape;

	shape.type = SHAPE_NONE;
	shape.hit.t = -1;
	nearest_intersect_sphere(state, ray, &shape);
	return (shape);
}
