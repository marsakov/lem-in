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

#include "lem-in.h"

void		sort_ways(t_lemin *ptr, int j)
{
	int			i;
	int			tmp_len;
	t_hashmap	*tmp;
	t_ways		*p;

	while (++j < ptr->ways)
	{
		i = -1;
		p = ptr->solv;
		while (++i < ptr->ways - 1)
		{
			if (p->len > p->next->len)
			{
				tmp = p->way;
				tmp_len = p->len;
				p->len = p->next->len;
				p->way = p->next->way;
				p->next->way = tmp;
				p->next->len = tmp_len;
			}
			p = p->next;
		}
	}
}

void		print_step(t_lemin *ptr)
{
	int i;

	i = -1;
	while (++i < ptr->ants)
	{
		if (ptr->ant_in_end[i])
		{
			ft_printf("L%d-%s ", i + 1, elembyi(ptr, ptr->end)->name);
			ptr->ant_in_end[i] = 0;
		}
	}
	i = -1;
	while (++i < ptr->count_r)
		if (ptr->ant_in_room[i])
			ft_printf("L%d-%s ", ptr->ant_in_room[i], elembyi(ptr, i)->name);
	ft_printf("\n");
}

t_hashmap	*find_room(t_lemin *ptr, int index)
{
	t_ways		*tmp;
	t_hashmap	*room;

	tmp = ptr->solv;
	while (tmp)
	{
		room = tmp->way;
		while (room)
		{
			if (room->i == index)
				return (room);
			room = room->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void		next_step(t_lemin *ptr)
{
	int			i;
	t_hashmap	*room;

	i = -1;
	while (++i < ptr->count_r)
	{
		if (ptr->ant_in_room[i])
		{
			room = find_room(ptr, i)->next;
			if (room && !ptr->ant_step[ptr->ant_in_room[i] - 1] && room->i == ptr->end)
			{
				ptr->ant_in_end[ptr->ant_in_room[i] - 1] = 1;
				ptr->ant_step[ptr->ant_in_room[i] - 1] = 1;
				ptr->ant_in_room[i] = 0;
			}
			else if (room && !ptr->ant_step[ptr->ant_in_room[i] - 1] && !ptr->ant_in_room[room->i])
			{
				ptr->ant_in_room[room->i] = ptr->ant_in_room[i];
				ptr->ant_step[ptr->ant_in_room[i] - 1] = 1;
				ptr->ant_in_room[i] = 0;
			}
		}
	}
}

int			ants_not_in_end(t_lemin *ptr)
{
	int i;

	i = -1;
	while (++i < ptr->ants)
	{
		if (ptr->ant_in_end[i])
			return (1);
	}
	i = -1;
	while (++i < ptr->count_r)
		if (ptr->ant_in_room[i])
			return (1);
	return (0);
}

void		solution(t_lemin *ptr)
{
	int			ant;
	t_ways		*tmp;

	ant = 1;
	ptr->ant_in_room = ft_memalloc(sizeof(int) * ptr->count_r);
	ptr->ant_in_end = ft_memalloc(sizeof(int) * ptr->ants);
	ptr->ant_step = ft_memalloc(sizeof(int) * ptr->ants);
	tmp = ptr->solv;
	print_path(ptr);
	while (tmp)
	{
		free(tmp->way->name);
		free(tmp->way);
		tmp->way = tmp->way->next;
		tmp = tmp->next;
	}
	while (ant <= ptr->ants)
	{
		ft_bzero(ptr->ant_step, sizeof(int) * ptr->ants);
		next_step(ptr);
		next_step(ptr);
		tmp = ptr->solv;
		while (tmp && ant <= ptr->ants)
		{
			if (tmp->way->i == ptr->end)
			{
				ptr->ant_in_end[ant - 1] = 1;
				ant++;
			}
			else if (!ptr->ant_in_room[tmp->way->i])
				ptr->ant_in_room[tmp->way->i] = ant++;
			tmp = tmp->next;
		}
		print_step(ptr);
	}
	while (ants_not_in_end(ptr))
	{
		ft_bzero(ptr->ant_step, sizeof(int) * ptr->ants);
		next_step(ptr);
		print_step(ptr);
	}
}