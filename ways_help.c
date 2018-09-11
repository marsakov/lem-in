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

#include "lemin.h"

void		print_path(t_lemin *ptr)
{
	t_ways		*tmp;
	t_hashmap	*room;
	int			i;

	tmp = ptr->solv;
	ft_printf("___________ ways _________\n");
	while (tmp)
	{
		i = 0;
		ft_printf("index = %d | len = %d | ", tmp->i, tmp->len);
		while (i < tmp->len)
		{
			room = elembyi(ptr, tmp->way[i]);
			ft_printf("%s", room->name);
			if (i != tmp->len - 1)
				ft_printf(" -> ");
			i++;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("__________________________\n");
	ft_printf("ways = %d\n", ptr->ways);
}

void		sort_ways(t_lemin *ptr, int j)
{
	int			i;
	int			tmp_len;
	int			*tmp;
	t_ways		*p;

	while (++j < ptr->ways)
	{
		i = -1;
		p = ptr->solv;
		while (++i < ptr->ways - 1 && p && p->next)
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

int			cross_ways(t_ways *way1, t_ways *way2)
{
	int	i;
	int	j;

	i = 1;
	if (!way1 || !way2)
		return (1);
	while (i < way1->len - 1)
	{
		j = 1;
		while (j < way2->len - 1)
		{
			if (way1->way[i] == way2->way[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int			equal_ways(t_ways *way1, t_ways *way2)
{
	int i;

	i = 0;
	if (!way1 || !way2)
		return (0);
	if (way1->len != way2->len)
		return (0);
	while (i < way1->len)
	{
		if (way1->way[i] != way2->way[i])
			return (0);
		i++;
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
		while (tmp2 && tmp2->next)
			if (tmp1->i != tmp2->next->i && (equal_ways(tmp1, tmp2->next) ||
						cross_ways(tmp1, tmp2->next)) && (ptr->ways--))
			{
				free(tmp2->next->way);
				free(tmp2->next);
				tmp2->next = tmp2->next->next;
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
