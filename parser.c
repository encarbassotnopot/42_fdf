/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:03:44 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/06 11:45:00 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_2d(t_coord *c, t_limits *l)
{
	int	s[3];

	s[0] = 30;
	s[1] = -30;
	s[2] = 30;
	c->proj_x = (c->x * s[0] - c->z * s[2]) * cos(M_PI / 6);
	c->proj_y = c->y * s[1] + (c->x * s[0] + c->z * s[2]) * sin(M_PI / 6);
	if (c->proj_x < l->min_x)
		l->min_x = c->proj_x;
	if (c->proj_x > l->max_x)
		l->max_x = c->proj_x;
	if (c->proj_y < l->min_y)
		l->min_y = c->proj_y;
	if (c->proj_y > l->max_y)
		l->max_y = c->proj_y;
}

int	parse_line(t_coord **map, char *line, int z, t_limits *l)
{
	char	**split;
	int		x;
	int		y;
	t_coord	*new;

	split = ft_split(line, ' ');
	if (!split)
		return (1);
	x = -1;
	while (split[++x])
	{
		y = ft_atoi(split[x]);
		new = new_coord(x, y, z);
		if (!new)
		{
			ft_free_arr(split);
			return (1);
		}
		append_coord(map, new);
		calculate_2d(new, l);
	}
	ft_free_arr(split);
	return (0);
}

int	parse_map(t_coord **map, int fd, t_limits *l)
{
	char	*line;
	int		line_num;

	line_num = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_num++;
		if (parse_line(map, line, line_num, l))
		{
			free(line);
			free_coords(map);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

void	normalize_proj(t_coord *map, t_limits *limits)
{
	t_coord	*list_h;
	t_coord	*new;

	list_h = map;
	while (list_h)
	{
		new = list_h;
		while (new)
		{
			new->proj_x -= limits->min_x;
			new->proj_y -= limits->min_y;
			new = new->next_z;
		}
		list_h = list_h->next_x;
	}
}

t_limits	*init_limits(void)
{
	t_limits	*limits;

	limits = ft_calloc(1, sizeof(t_limits));
	if (!limits)
		return (NULL);
	limits->min_x = DBL_MAX;
	limits->min_y = DBL_MAX;
	limits->max_x = DBL_MIN;
	limits->max_y = DBL_MIN;
	return (limits);
}
