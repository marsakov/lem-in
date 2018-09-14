/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 17:10:43 by msakovyc          #+#    #+#             */
/*   Updated: 2018/09/14 17:10:46 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_all_step(t_lemin *ptr)
{
	int			i;
	t_hashmap	*room;

	i = 1;
	room = elembyi(ptr, ptr->end);
	while (i <= ptr->ants)
		ft_printf("L%d-%s ", i++, room->name);
	ft_printf("\n");
	exit(0);
}

int			ants_not_in_end(t_lemin *ptr)
{
	int			i;
	t_hashmap	*room;

	i = -1;
	while (++i < ptr->ants)
	{
		if (ptr->ant_in_end[i])
			return (1);
	}
	room = ptr->rooms;
	while (room)
	{
		if (room->ant)
			return (1);
		room = room->next;
	}
	return (0);
}

int			ants_steps(t_lemin *ptr)
{
	int			i;
	t_hashmap	*room;

	i = -1;
	room = ptr->rooms;
	while (room)
	{
		if (room->ant && !ptr->ant_step[room->ant - 1])
			return (1);
		room = room->next;
	}
	return (0);
}
