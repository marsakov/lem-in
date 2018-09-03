/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <msakovyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 13:42:48 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/25 13:42:51 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_path(t_lemin *ptr)
{
	/* ------------------------------------------------ */
	ft_printf("___________ ways _________\n");
	t_ways *tmp = ptr->solv;
	while (tmp)
	{
		t_hashmap *tmp_way = tmp->way;
		ft_printf("index = %d | len = %d | ", tmp->i, tmp->len);
		while (tmp_way)
		{
			ft_printf("%s", tmp_way->name);
			if (tmp_way->next)
				ft_printf(" -> ");
			tmp_way = tmp_way->next;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("__________________________\n");
	ft_printf("ways = %d\n", ptr->ways);
	/* ------------------------------------------------ */
}

void	find_next(t_lemin *ptr, t_ways *solv, int numb, int row, int **arr)
{
	int			i;
	t_hashmap	*way;

	i = -1;
	solv->len++;
	if (row == ptr->start)
	{
		way = mem_room(ptr, row);
		way->next = solv->way;
		solv->way = way;
		return ;
	}
	while (++i < ptr->count_r)
		if (arr[row][i] == numb)
		{
			way = mem_room(ptr, row);
			way->next = solv->way;
			solv->way = way;
			find_next(ptr, solv, numb - 1, i, arr);
		}
}

void	mem_solv(t_lemin *ptr, int **arr)
{
	int			i;
	t_ways		*w;

	if (ptr->ways == 0)
		ptr->solv = NULL;
	i = -1;
	while (++i < ptr->count_r)
		if (arr[ptr->end][i] != 0 && arr[ptr->end][i] != 1)
		{
			!(w = malloc(sizeof(t_ways))) ? error(0, NULL) : 0;
			w->i = ptr->ways++;
			w->len = 0;
			w->way = mem_room(ptr, ptr->end);
			w->way->next = NULL;
			w->next = ptr->solv;
			ptr->solv = w;
			find_next(ptr, ptr->solv, arr[ptr->end][i] - 1, i, arr);
		}
}

int		**copy_arr(int **src, int size)
{
	int i;
	int j;
	int **arr;

	i = -1;
	!(arr = ft_memalloc(sizeof(int*) * size)) ? error(0, NULL) : 0;
	while (++i < size)
		!(arr[i] = ft_memalloc(sizeof(int) * size)) ? error (0, NULL) : 0;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			arr[i][j] = src[i][j];
	}
	return (arr);
}

void	check_link(int k, t_lemin *ptr, int m, int **arr)
{
	int i;
	int j;
	int	**next_arr;

	if (k == ptr->end)
	{
		mem_solv(ptr, arr);
		return ;
	}
	i = -1;
	while (++i < ptr->count_r)
		if (arr[k][i] == 1)
		{
			next_arr = copy_arr(arr, ptr->count_r);
			next_arr[k][i] = m;
			next_arr[i][k] = m;
			check_link(i, ptr, m + 1, next_arr);
			j = -1;
			while (++j < ptr->count_r)
				free(next_arr[j]);
			free(next_arr);
		}
}

int		find_ways(t_lemin *ptr)
{
	int	i;
	int	j;
	int	**arr;

	ptr->ways = 0;
	i = -1;
	while (++i < ptr->count_r)
		if (ptr->links[ptr->start][i] == 1)
		{
			arr = copy_arr(ptr->links, ptr->count_r);
			arr[ptr->start][i] = 2;
			arr[i][ptr->start] = 2;
			check_link(i, ptr, 3, arr);
			j = -1;
			while (++j < ptr->count_r)
				free(arr[j]);
			free(arr);
		}
	sort_ways(ptr, -1);
	if (ptr->all_path)
		print_path(ptr);
	del_double_ways(ptr, 0);
	if (ptr->true_path)
		print_path(ptr);
	return (ptr->ways);
}
