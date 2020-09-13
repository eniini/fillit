/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetrimino.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholopai <jholopai@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:41:12 by jholopai          #+#    #+#             */
/*   Updated: 2020/09/13 20:55:53 by jholopai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Returns the amount of connections to other blocks one coordinate links to.
*/

static int	check_coordinates(char **array, size_t y, size_t x)
{
	size_t	connections;

	connections = 0;
	if (x > 0 && array[y][x - 1] == '#')
		connections++;
	if (x < 3 && array[y][x + 1] == '#')
		connections++;
	if (y < 3 && array[y + 1][x] == '#')
		connections++;
	if (y > 0 && array[y - 1][x] == '#')
		connections++;
	return (connections);
}

/*
**	Goes through the array one tetrimino at a time. When a '#' is found, checks
**	how many other '#'s it's connected to. Returns [0] if the sum of connections
**	is not 6 or 8 with 4 double connections.
*/

static int	check_tetrimino(char **array, size_t y, size_t x)
{
	size_t	result;
	size_t	connections;
	size_t	double_connections;

	connections = 0;
	double_connections = 0;
	while (y < 4)
	{
		while (array[y][x] != '\0')
		{
			if (array[y][x] == '#')
			{
				if ((result = check_coordinates(array, y, x)) == 2)
					double_connections++;
				connections += result;
			}
			x++;
		}
		x = 0;
		y++;
	}
	if ((connections == 6 || (connections == 8 && double_connections == 4)))
		return (1);
	return (0);
}

/*
**	Moves a given tetrimino's coordinates to start from 0.0
**	to make it easier to place them on the board later on.
*/

static void	move_to_meridian(t_tetri *tetri)
{
	int		y;
	int		x;
	int		i;

	i = 1;
	y = tetri->coordinates[0][0];
	x = tetri->coordinates[0][1];
	while (i < 4)
	{
		if (tetri->coordinates[i][0] < y)
			y = tetri->coordinates[i][0];
		if (tetri->coordinates[i][1] < x)
			x = tetri->coordinates[i][1];
		i++;
	}
	while (i >= 0)
	{
		tetri->coordinates[i][0] -= y;
		tetri->coordinates[i][1] -= x;
		i--;
	}
}

/*
**	Goes through the tetrimino assuming it is valid. When a #
**	is found, saves its coordinates to the given tetrimino.
*/

static void	gather_tetrimino(char **array, t_tetri *tetri)
{
	size_t	x;
	size_t	y;
	size_t	round;

	x = 0;
	y = 0;
	round = 0;
	while (y < 4)
	{
		while (array[y][x] && array[y][x] != '\0')
		{
			if (array[y][x] == '#')
			{
				tetri->coordinates[round][0] = y;
				tetri->coordinates[round][1] = x;
				round++;
			}
			x++;
		}
		x = 0;
		y++;
	}
	move_to_meridian(tetri);
}

/*
**	Goes through the array given as parameter 4 rows at a time, first making
**	sure that it is valid and then going through it again to save coordinates
**	for the tetrimino. Creates a new tetri for each tetrimino block and returns
**	a pointer to the first block.
*/

t_tetri		*get_tetrimino(char **array)
{
	t_tetri	*head;
	t_tetri	*temp;
	size_t	i;

	head = NULL;
	i = 0;
	while (array[i] != NULL)
	{
		if (!(check_tetrimino(&array[i], 0, 0)) || !(temp = tetrilist_new()))
		{
			tetrilist_delete(&head);
			ft_free2d(array);
			return (NULL);
		}
		gather_tetrimino(&array[i], temp);
		if (!head)
			head = temp;
		tetrilist_add(tetrilist_find_tail(head), temp);
		temp = temp->next;
		i += 4;
	}
	ft_free2d(array);
	return (head);
}
