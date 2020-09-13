/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholopai <jholopai@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 14:39:14 by eniini            #+#    #+#             */
/*   Updated: 2020/09/13 20:16:17 by jholopai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct		s_tetri
{
	int				coordinates[4][2];
	struct s_tetri	*prev;
	struct s_tetri	*next;
}					t_tetri;

typedef struct		s_cursor
{
	int				x;
	int				y;
}					t_cursor;

t_tetri				*get_tetrimino(char **array);

char				**get_input(int fd);

char				**solve_fillit(t_tetri *tetrilist, int tn);

t_cursor			*new_cursor(int y, int x);

void				tetrilist_add(t_tetri *tail, t_tetri *new);

void				tetrilist_delete(t_tetri **head);

t_tetri				*tetrilist_new(void);

t_tetri				*tetrilist_find_tail(t_tetri *head);

#endif
