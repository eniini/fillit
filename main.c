/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 09:56:44 by eniini            #+#    #+#             */
/*   Updated: 2020/09/13 22:15:17 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Fillit is designed to process specifically formatted input file that
**	includes a list of 1 to 26 tetriminos. It then rearranges them into the
**	smallest possible square.
**	If the program encounters any faults in the given argument or fails during
**	any operation, it quits and prints out a generic error message. Otherwise
**	The solution is written to the standard output.
*/

#include "fillit.h"

/*
**	Final stage of the program, draws the created solution
**	and frees the charray from heap memory.
*/

static int	printbrd(char **board)
{
	size_t	i;

	if (board)
	{
		i = 0;
		while (board[i] != NULL)
		{
			ft_putendl(board[i]);
			i++;
		}
		ft_free2d(board);
		return (1);
	}
	return (0);
}

/*
**	Counts the amount of links in the given list.
*/

static int	count_tetris(t_tetri *tetrilist)
{
	int		counter;

	counter = 0;
	while (tetrilist)
	{
		tetrilist = tetrilist->next;
		counter++;
	}
	return (counter);
}

/*
**	Handles piping the given argument into functions that create a list of
**	tetriminos, then moves the created list into solution algorithm and
**	finally prints it.
*/

int			main(int argc, char **argv)
{
	int		fd;
	t_tetri	*tetrilist;
	char	**file_contents;

	if (argc != 2)
		return (write(1, "usage: fillit source_file\n", 26));
	if ((fd = open(argv[argc - 1], O_RDONLY)) != -1)
	{
		if ((file_contents = get_input(fd)))
		{
			if ((tetrilist = get_tetrimino(file_contents)))
			{
				if (printbrd(solve_fillit(tetrilist, count_tetris(tetrilist))))
				{
					tetrilist_delete(&tetrilist);
					if (close(fd) != -1)
						return (0);
				}
			}
		}
	}
	return (write(1, "error\n", 6));
}
