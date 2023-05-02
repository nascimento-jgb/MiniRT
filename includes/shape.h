/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:23:12 by helneff           #+#    #+#             */
/*   Updated: 2023/05/02 13:35:52 by helneff          ###   ########.fr       */
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
	SHAPE_CYLINDER,
	SHAPE_CONE
}	t_shape_type;

typedef union u_shape_data
{
	t_sphere_data	*sphere;
	t_plane_data	*plane;
	t_cylinder_data	*cylinder;
	t_cone_data		*cone;
}	t_shape_data;

typedef struct s_intersect
{
	double	t;
	t_vec3	ray_color;
}	t_intersect;

typedef struct s_shape
{
	t_shape_type	type;
	t_shape_data	data;
	t_intersect		hit;
}	t_shape;

t_shape		nearest_intersect(const t_state *state, t_ray ray);

t_intersect	sphere_intersect(t_vec3 center, double radius, t_ray ray);
void		nearest_intersect_sphere(
				const t_state *state, t_ray ray, t_shape *shape);

#endif
