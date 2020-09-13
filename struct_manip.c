/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholopai <jholopai@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 21:36:41 by eniini            #+#    #+#             */
/*   Updated: 2020/09/11 14:03:06 by jholopai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Create struct to move data effectively within solver functions.
*/

t_cursor	*new_cursor(int y, int x)
{
	t_cursor	*cursor;

	if (!(cursor = (t_cursor*)malloc(sizeof(cursor))))
		return (NULL);
	cursor->y = y;
	cursor->x = x;
	return (cursor);
}

/*
**	Create struct to hold individual tetrimino block coordinates.
*/

t_tetri		*tetrilist_new(void)
{
	t_tetri		*tetrimino;

	if (!(tetrimino = (t_tetri*)malloc(sizeof(t_tetri))))
		return (NULL);
	tetrimino->next = NULL;
	tetrimino->prev = NULL;
	return (tetrimino);
}

/*
**	Adds a new link after [tail].
*/

void		tetrilist_add(t_tetri *tail, t_tetri *new)
{
	if (tail != NULL && new != NULL)
	{
		new->prev = tail;
		tail->next = new;
		new->next = NULL;
	}
}

/*
**	Erase data and free pointers inside all of the structs.
*/

void		tetrilist_delete(t_tetri **head)
{
	t_tetri		*next;

	while (*head)
	{
		next = (*head)->next;
		(void)head;
		free(*head);
		*head = next;
	}
	*head = NULL;
}

/*
**	Finds the last link of the linked list.
*/

t_tetri		*tetrilist_find_tail(t_tetri *head)
{
	t_tetri		*temp;

	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
