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

void	sort_ways(t_lemin *ptr, int j)
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

void	solution(t_lemin *ptr)
{
	sort_ways(ptr, -1);
	/* ------------------------------------------------ 
	ft_printf("_________ sort solv ________\n");
	t_ways *tmp = ptr->solv;
	while (tmp)
	{
		t_hashmap *tmp_way = tmp->way;
		ft_printf("index = %d | len = %d | ", tmp->i, tmp->len);
		while (tmp_way)
		{
			ft_printf("-> %s ", tmp_way->name);
			tmp_way = tmp_way->next;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("__________________________\n");
	 ------------------------------------------------ */
	ptr->full_empty = ft_memalloc(sizeof(int) * ptr->count_r);
	while (ptr->ants)
	{
		while ()
		{

		}
	}
}