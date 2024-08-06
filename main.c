/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:30:47 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/06 11:53:50 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void get_map(int argc, char **argv, t_limits *limits, t_coord **map)
{
	int		fd;

	if (argc != 2)
	{
		ft_printerr("Error: Wrong number of args\n");
		free(limits);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error reading file");
		free(limits);
		exit(EXIT_FAILURE);
	}
	if (parse_map(map, fd, limits))
	{
		ft_printerr("Error parsing map\n");
		free(limits);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	t_coord		*map;
	t_limits	*limits;

	limits = init_limits();
	if (!limits)
	{
		ft_printerr("Error: couldn't allocate memory for limits\n");
		exit(EXIT_FAILURE);
	}
	get_map(argc, argv, limits, map);
	if (!map)
	{
		ft_printerr("Error parsing map\n");
		exit(EXIT_FAILURE);
	}
	normalize_proj(map, limits);
	mlx_main(map, limits);
	free_coords(&map);
	free(limits);
}
