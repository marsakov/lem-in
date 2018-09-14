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
			room = elembyi(ptr, ptr->end);
			ft_printf("L%d-%s ", i + 1, room->name);
			ptr->ant_in_end[i] = 0;
		}
		else if (ptr->ant_step[i])
		{
			room = ptr->rooms;
			while (room && room->ant != i + 1)
				room = room->next;
			ft_printf("L%d-%s ", i + 1, room->name);
			ptr->ant_step[i] = 0;
		}
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

	while (ants_steps(ptr) && (rm = ptr->rooms))
		while (rm)
		{
			if (rm->ant)
			{
				nxt_rm = elembyi(ptr, find_linked_room(ptr, rm->i));
				if (ANT_STEP && nxt_rm->i == ptr->end)
				{
					ptr->ant_in_end[rm->ant - 1] = 1;
					ptr->ant_step[rm->ant - 1] = 1;
					rm->ant = 0;
				}
				else if (ANT_STEP && !nxt_rm->ant)
				{
					nxt_rm->ant = rm->ant;
					ptr->ant_step[rm->ant - 1] = 1;
					rm->ant = 0;
				}
			}
			rm = rm->next;
		}
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
		tmp = ptr->solv;
		while (ant <= ptr->ants && tmp)
		{
			room = elembyi(ptr, tmp->way[1]);
			if (room && !room->ant)
			{
				ptr->ant_step[ant - 1] = 1;
				room->ant = ant++;
			}
			tmp = tmp->next;
		}
		print_step(ptr);
	}
}
