/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:20:45 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/21 21:20:49 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		equal_ways(t_ways *way1, t_ways *way2)
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

void	del_double_ways(t_lemin *ptr)
{
	t_ways	*tmp1;
	t_ways	*tmp2;
	int		i;

	tmp1 = ptr->solv;
	while (tmp1)
	{
		tmp2 = ptr->solv;
		while (tmp2->next)
		{
			if (tmp1->i != tmp2->next->i && tmp1->way->i == tmp2->next->way->i && equal_ways(tmp1, tmp2->next))
			{
				tmp2->next = tmp2->next->next;
				ptr->ways--;
			}
			else
				tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	tmp1 = ptr->solv;
	i = 0;
	while (tmp1)
	{
		tmp1->i = i++;
		tmp1 = tmp1->next;
	}
}


t_hashmap	*mem_room(t_lemin *ptr, int row, int index)
{
	t_hashmap	*tmp;
	t_hashmap	*way;

	tmp = elembyi(ptr, row);
	way = malloc(sizeof(t_hashmap));
	way->i = index;
	way->name = ft_strdup(tmp->name);
	way->x = tmp->x;
	way->y = tmp->y;
	return (way);
}

void		find_next(t_lemin *ptr, t_ways *solv, int numb, int row, int index, int **arr)
{
	int 		i;
	t_hashmap	*way;

	i = 0;
	if (row == ptr->start)
	{
		way = mem_room(ptr, row, index);
		way->next = solv->way;
		solv->way = way;
		return ;
	}
	while (i < ptr->count_r)
	{
		if (arr[row][i] == numb)
		{
			way = mem_room(ptr, row, index);
			way->next = solv->way;
			solv->way = way;
			find_next(ptr, solv, numb - 1, i, index + 1, arr);
		}
		i++;
	}
}

void		mem_solv(t_lemin *ptr, int **arr)
{
	int 		i;
	t_ways		*w;

	if (ptr->ways == 0)
		ptr->solv = NULL;
	i = 0;
	while (i < ptr->count_r)
	{
		if (arr[ptr->end][i] != 0 && arr[ptr->end][i] != 1)
		{
			w = malloc(sizeof(t_ways));
			w->i = ptr->ways++;
			w->way = mem_room(ptr, ptr->end, 0);
			w->way->next = NULL;
			w->next = ptr->solv;
			ptr->solv = w;
			find_next(ptr, ptr->solv, arr[ptr->end][i] - 1, i, 1, arr);
		}
		i++;
	}
}

int		**copy_arr(int **src, int size)
{
	int i;
	int j;
	int **arr;

	i = -1;
	arr = ft_memalloc(sizeof(int**));
	while (++i < size)
		arr[i] = ft_memalloc(sizeof(int*) * size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			arr[i][j] = src[i][j];
			j++;
		}
		i++;
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
		/* ----------------------------------------- */
		ft_printf("__________________________\n");
		for (int a = 0; a < ptr->count_r; a++)
		{
			for (int b = 0; b < ptr->count_r; b++)
				ft_printf("%d ", arr[a][b]);
			ft_printf("\n");
		}
		ft_printf("__________________________\n");
		/* ---------------------------------------- */
		mem_solv(ptr, arr);
		return ;
	}
	i = 0;
	while (i < ptr->count_r)
	{
		if (arr[k][i] == 1)
		{
			next_arr = copy_arr(arr, ptr->count_r);
			next_arr[k][i] = m;
			next_arr[i][k] = m;
			check_link(i, ptr, m + 1, next_arr);

			/* free array */
			j = -1;
			while (++j < ptr->count_r)
				free(next_arr[j]);
			free(next_arr);
			/*  -------  */

		}
		i++;
	}
}

int		find_solutions(t_lemin *ptr)
{
	int	i;
	int j;
	int **arr;

	ptr->ways = 0;
	i = 0;
	while (i < ptr->count_r)
	{
		if (ptr->links[ptr->start][i] == 1)
		{
			arr = copy_arr(ptr->links, ptr->count_r);
			arr[ptr->start][i] = 2;
			arr[i][ptr->start] = 2;
			check_link(i, ptr, 3, arr);

			/* free array */
			j = -1;
			while (++j < ptr->count_r)
				free(arr[j]);
			free(arr);
			/*  -------  */

		}
		i++;
	}
	del_double_ways(ptr);

	/* ------------------------------------------------*/
	ft_printf("_________ mem solv ________\n");
	t_ways *tmp = ptr->solv;
	while (tmp)
	{
		t_hashmap *tmp_way = tmp->way;
		ft_printf("index = %d | len = %d | ", tmp->i, tmp_way->i);
		while (tmp_way)
		{
			ft_printf("-> %s ", tmp_way->name);
			tmp_way = tmp_way->next;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("__________________________\n");
	/* ------------------------------------------------*/
	ft_printf("ways = %d\n", ptr->ways);
	return (ptr->ways);
}
