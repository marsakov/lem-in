/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <msakovyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 13:42:57 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/25 13:43:00 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		free_way(t_ways *del)
{
	while (del->way)
	{
		free(del->way->name);
		free(del->way);
		del->way = del->way->next;
	}
	free(del);
}

int			equal_ways(t_ways *way1, t_ways *way2)
{
	t_hashmap *tmp1;
	t_hashmap *tmp2;

	tmp1 = way1->way;
	tmp2 = way2->way;
	while (tmp1 && tmp2)
	{
		if (ft_strcmp(tmp1->name, tmp2->name))
			return (0);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return (1);
}

void		del_double_ways(t_lemin *ptr, int i)
{
	t_ways	*tmp1;
	t_ways	*tmp2;

	tmp1 = ptr->solv;
	while (tmp1)
	{
		tmp2 = ptr->solv;
		while (tmp2->next)
			if (tmp1->i != tmp2->next->i && tmp1->len == tmp2->next->len
				&& equal_ways(tmp1, tmp2->next))
			{
				free_way(tmp2->next);
				tmp2->next = tmp2->next->next;
				ptr->ways--;
			}
			else
				tmp2 = tmp2->next;
		tmp1 = tmp1->next;
	}
	tmp1 = ptr->solv;
	while (tmp1)
	{
		tmp1->i = i++;
		tmp1 = tmp1->next;
	}
}

t_hashmap	*mem_room(t_lemin *ptr, int row)
{
	t_hashmap	*tmp;
	t_hashmap	*way;

	tmp = elembyi(ptr, row);
	way = malloc(sizeof(t_hashmap));
	way->i = tmp->i;
	way->name = ft_strdup(tmp->name);
	way->x = tmp->x;
	way->y = tmp->y;
	return (way);
}
