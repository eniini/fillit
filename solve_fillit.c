/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_fillit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 21:24:47 by eniini            #+#    #+#             */
/*   Updated: 2020/10/01 16:48:16 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Creates a square to hold a solution. Increments its size on each call.
**	If malloc fails at any point, returns NULL and frees the charrays.
**	Returns the created board as a 2d charray.
*/

static char		**create_board(int boardsize)
{
	int			i;
	int			side;
	char		**board;
	static int	rescale;

	side = 2;
	while ((side * side) < boardsize)
		side++;
	i = 0;
	side += rescale++;
	if (!(board = (char**)malloc(sizeof(board) * (side + 1))))
		return (NULL);
	while (i < side)
	{
		if (!(board[i] = ft_strnew(side)))
		{
			ft_free_arr(board);
			return (NULL);
		}
		ft_memset(board[i], '.', side);
		i++;
	}
	board[i] = NULL;
	return (board);
}

/*
**	Checks through each of the four [head->coordinates] against [board's]
**	coordinates starting from an origin point given as [cursor],
**	and unless a non-empty position is found or coordinates are out-of-bounds,
**	returns [1].
*/

static int		checker(char **board, t_tetri *head, t_cursor *cursor)
{
	int		i;
	int		boardsize;

	i = 0;
	boardsize = ft_get_arr_size(board);
	while (i < 4)
	{
		if ((cursor->y + head->coordinates[i][0]) >= (int)boardsize)
			return (0);
		if (board[(cursor->y + head->coordinates[i][0])]
		[(cursor->x + head->coordinates[i][1])] != '.')
			return (0);
		i++;
	}
	return (1);
}

/*
**	Placer calls checker() on a specific x/y coordinate on [board].
**	If successful, it then inserts the given character on the four
**	[head->coordinates].
**	Alternatively, if called with '.' character, it will always
**	insert that under assumption that it was called with the same
**	coordinates as the last time (that's now being cleared).
*/

static int		placer(char **board, t_tetri *head, t_cursor *cursor, int c)
{
	int		i;
	int		x;
	int		y;

	y = cursor->y;
	x = cursor->x;
	i = 0;
	if (checker(board, head, cursor) || c == '.')
	{
		free(cursor);
		while (i < 4)
		{
			board[(head->coordinates[i][0] + y)]
			[(head->coordinates[i][1] + x)] = c;
			i++;
		}
		return (1);
	}
	free(cursor);
	return (0);
}

/*
**	On a successful placer() call, recursively calls itself again.
**	If recursive call cannot find a position for the next tetrimino, current
**	placement is reversed and board x/y cursor is incremented.
**	If all tetriminos on the linked list are placed successfully, returns [1].
*/

static int		solver(char **b, t_tetri *head, int c)
{
	int		y;
	int		x;

	if (head == NULL)
		return (1);
	y = 0;
	while (b[y] != NULL)
	{
		x = 0;
		while (b[y][x] != '\0')
		{
			if (placer(b, head, new_cursor(y, x), c))
			{
				if (solver(b, head->next, c + 1))
					return (1);
				else
					placer(b, head, new_cursor(y, x), '.');
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

/*
**	Create_board is called until solver returns [1] with it.
**	Returns last version of the board in its solved state.
*/

char			**solve_fillit(t_tetri *head, int tetricount)
{
	char	**board;

	if (!(board = create_board(tetricount * 4)))
		return (NULL);
	while (!(solver(board, head, 'A')))
	{
		if (board)
			ft_free_arr(board);
		if (!(board = create_board(tetricount * 4)))
			return (NULL);
	}
	return (board);
}
