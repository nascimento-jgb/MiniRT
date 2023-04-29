/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonascim <jonascim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:26:46 by jonascim          #+#    #+#             */
/*   Updated: 2023/04/29 14:10:11 by jonascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "shape.h"

int	plane_intersect(t_ray ray, t_plane_data *plane)
{
	t_vec3	to_plane;
	double	denom;
	double	t;

	denom = vec3_dot(ray.dir, plane->dir);
	if (fabs(denom) < 1e-6)
		return (1); //ray is parallel to plane
	to_plane = vec3_subtract(plane->pos, ray.orig);
	t = vec3_dot(to_plane, plane->dir) / denom;
	plane->t = t;
	plane->ray_pos = ray_at(ray, t);
	return (0);
}
