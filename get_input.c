/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 11:22:18 by eniini            #+#    #+#             */
/*   Updated: 2020/10/01 16:37:22 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Since we know exactly the intended shape of fillit input;
**	Check if every fifth char is linebreak, every other needs to be '.' or '#'.
**	If a valid line is found, we return that to [line] pointer.
**	Returns 1 if everything checks out.
*/

static int	buffercheck(char *buffer)
{
	size_t	i;
	size_t	linebreaks;

	i = 0;
	linebreaks = 0;
	while (buffer[i] != '\0')
	{
		if ((i > 0) && (!((i + 1) % 5) && (buffer[i] == '\n')))
		{
			linebreaks++;
			i++;
		}
		if (linebreaks == 4 && buffer[i] == '\0')
			break ;
		if ((linebreaks == 4 && buffer[i] == '\n') && (buffer[i + 1] == '\n' ||
		buffer[i + 1] == '\0'))
			break ;
		if (buffer[i] != '.' && buffer[i] != '#')
			return (0);
		i++;
	}
	if (linebreaks != 4)
		return (0);
	else
		return (1);
}

/*
**	Finds linebreaks and returns line before them into [line].
**	Returns 0 if anything fails. As the function is called
**	inside the read() loop in a loop for each read buffer,
**	we need to reset all variables whenever '\0' is reached.
*/

static int	bufferintocharray(char *buffer, char **line)
{
	static size_t	i;
	static size_t	start;
	static size_t	linebreaks;

	while (buffer[i] != '\0')
	{
		if (buffer[i + 1] == '\n' && linebreaks < 4)
		{
			if (!(*line = ft_strsub(buffer, start, 4)))
			{
				ft_free_arr(line);
				return (0);
			}
			start = i + 2;
			linebreaks++;
			i++;
			return (1);
		}
		i++;
	}
	i = 0;
	start = 0;
	linebreaks = 0;
	return (0);
}

/*
**	Allocates 2D charray into heap with maximum allowed tetrimino count.
**	Also, initializes [buffer] and [counter]-array to 0's.
**	Returns the 2D charray unless malloc() fails.
*/

static char	**input_init(char *buffer, ssize_t *counter)
{
	int		i;
	char	**charray;

	i = 0;
	ft_bzero(buffer, 22);
	if (!(charray = (char**)malloc(sizeof(charray) * 105)))
		return (NULL);
	while (i < 105)
		charray[i++] = NULL;
	i = 0;
	while (i < 3)
		counter[i++] = 0;
	return (charray);
}

/*
**	We're calling read() with specific value each time to check it against
**	intended tetri input in buffercheck(). Bufferintocharray() returns
**	single line per call that is then added into the 2D charray.
**	Counter[0] -> result;
**	Counter[1] -> indexer;
**	COunter[2] -> last result (checking for linebreak)
*/

char		**get_input(int fd)
{
	char			**charray;
	char			buffer[22];
	ssize_t			counter[3];

	charray = input_init(buffer, counter);
	while ((counter[0] = read(fd, buffer, 21)))
	{
		buffer[counter[0] + 1] = '\0';
		if (!(buffercheck(buffer)))
			return (NULL);
		while (bufferintocharray(buffer, &charray[counter[1]]))
		{
			if (counter[1]++ > 103)
			{
				ft_free_arr(charray);
				return (NULL);
			}
		}
		counter[2] = counter[0];
		ft_bzero(buffer, 21);
	}
	if (counter[2] == 21)
		return (NULL);
	return (charray);
}
