/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <msakovyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 13:43:23 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/25 13:43:25 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_step(t_lemin *ptr)
{
	int			i;
	t_hashmap	*room;

	i = -1;
	while (++i < ptr->ants)
	{
		if (ptr->ant_in_end[i])
		{
			ft_printf("L%d-%s ", i + 1, elembyi(ptr, ptr->end)->name);
			ptr->ant_in_end[i] = 0;
		}
	}
	room = ptr->rooms;
	while (room)
	{
		if (room->ant)
			ft_printf("L%d-%s ", room->ant, room->name);
		room = room->next;
	}
	ft_printf("\n");
}

int			find_linked_room(t_lemin *ptr, int index)
{
	t_ways		*tmp;
	int			i;

	tmp = ptr->solv;
	while (tmp)
	{
		i = 0;
		while (i < tmp->len)
		{
			if (tmp->way[i] == index)
				return (tmp->way[i + 1]);
			i++;
		}
		tmp = tmp->next;
	}
	return (-1);
}

void		next_step(t_lemin *ptr)
{
	t_hashmap	*rm;
	t_hashmap	*nxt_rm;

	rm = ptr->rooms;
	while (rm)
	{
		if (rm->ant)
		{
			nxt_rm = elembyi(ptr, find_linked_room(ptr, rm->i));
			if (nxt_rm && nxt_rm->i == ptr->end && !ptr->ant_step[rm->ant - 1])
			{
				ptr->ant_in_end[rm->ant - 1] = 1;
				ptr->ant_step[rm->ant - 1] = 1;
				rm->ant = 0;
			}
			else if (nxt_rm && !ptr->ant_step[rm->ant - 1] && !nxt_rm->ant)
			{
				nxt_rm->ant = rm->ant;
				ptr->ant_step[rm->ant - 1] = 1;
				rm->ant = 0;
			}
		}
		rm = rm->next;
	}
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

void		solution(t_lemin *ptr, int ant)
{
	t_ways		*tmp;
	t_hashmap	*room;

	ptr->ant_in_end = ft_memalloc(sizeof(int) * ptr->ants);
	ptr->ant_step = ft_memalloc(sizeof(int) * ptr->ants);
	while (ant <= ptr->ants || ants_not_in_end(ptr))
	{
		ft_bzero(ptr->ant_step, sizeof(int) * ptr->ants);
		next_step(ptr);
		next_step(ptr);
		tmp = ptr->solv;
		while (ant <= ptr->ants && tmp)
		{
			room = elembyi(ptr, tmp->way[1]);
			if (room->i == ptr->end)
				ptr->ant_in_end[ant++ - 1] = 1;
			else if (!room->ant)
				room->ant = ant++;
			tmp = tmp->next;
		}
		print_step(ptr);
	}
}
