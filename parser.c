/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:03:44 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/03 14:52:39 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <float.h>

void	calculate_2d(t_coord *c, t_limits *l)
{
	int	s[3] = {3, 3, 3};

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
		new = new_coord(x * 10, y, z * 10);
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

int	main(int argc, char **argv)
{
	int			fd;
	t_coord		*map;
	t_coord		*list_h;
	t_coord		*new;
	t_limits	*limits;

	limits = ft_calloc(1, sizeof(t_limits));
	limits->min_x = DBL_MAX;
	limits->min_y = DBL_MAX;
	limits->max_x = DBL_MIN;
	limits->max_y = DBL_MIN;
	map = NULL;
	if (argc != 2)
	{
		ft_printerr("Error: Wrong number of args\n");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error reading file");
		exit(EXIT_FAILURE);
	}
	if (parse_map(&map, fd, limits))
	{
		ft_printerr("Error parsing map\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
	if (!map)
	{
		ft_printerr("Error parsing map\n");
		exit(EXIT_FAILURE);
	}
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
		printf("\n");
		list_h = list_h->next_x;
	}
	printf("min x: %2.4f, min y: %2.4f\nmax x: %2.4f, max y: %2.4f\n",
		limits->min_x, limits->min_y, limits->max_x, limits->max_y);
	mlx_main(map, limits);
	free_coords(&map);
	free(limits);
}
