/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:23:12 by helneff           #+#    #+#             */
/*   Updated: 2023/05/02 12:40:00 by helneff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "parser.h"
# include "state.h"
# include "ray.h"

typedef enum e_shape_type
{
	SHAPE_NONE,
	SHAPE_SPHERE,
	SHAPE_PLANE,
	SHAPE_CYLINDER
}	t_shape_type;

typedef union u_shape_data
{
	t_sphere_data	*sphere;
	t_plane_data	*plane;
	t_cylinder_data	*cylinder;
}	t_shape_data;

typedef struct s_shape
{
	t_shape_type	type;
	t_shape_data	data;
	double			t;
}	t_shape;

t_shape	nearest_intersect(const t_state *state, t_ray ray);

double	sphere_intersect(t_vec3 center, double radius, t_ray ray);

#endif
