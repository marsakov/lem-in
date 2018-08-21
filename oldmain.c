/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 20:05:41 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/09 20:05:43 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_hashmap	*elembyi(t_lemin *ptr, int i)
{
	t_hashmap	*tmp;

	tmp = ptr->rooms;
	while (tmp)
	{
		if (tmp->i == i)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	error(int e, char *line)
{
	ft_printf(RED "%s [", "ERROR" NC);
	if (e == 0)
		ft_printf("%s]\n", "MEM ALLOC ERROR");
	else if (e == 1)
		ft_printf("%s : '%s']\n", "INVALID ANTS", line);
	else if (e == 2)
		ft_printf("%s : '%s']\n", "INVALID ROOM", line);
	else if (e == 3)
		ft_printf("%s : '%s']\n", "INVALID LINK", line);
	else if (e == 4)
		ft_printf("%s]\n", "MISSING '##start' or '##end'");
	else if (e == 5)
		ft_printf("%s : '%s']\n", "ROOM HAS ALREADY EXIST", line);
	else if (e == 6)
		ft_printf("%s]\n", "NO LINKS");
	else if (e == 7)
		ft_printf("%s]\n", "NO WAYS");
	exit(1);
}

void	read_map(t_lemin *ptr)
{
	char *line;

	while (GNL(0, &line) > 0)
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		{
			if (!ft_strcmp(line, "##start"))
				ptr->start = ptr->count_r;
			else
				ptr->end = ptr->count_r;
			ft_printf("%s\n", line);
			ft_strdel(&line);
			while (GNL(0, &line) > 0 && ft_strchr(line, '#'))
			{
				ft_printf("%s\n", line);
				ft_strdel(&line);
			}
			write_elem(ptr, line);
		}
		else if (ft_strchr(line, '-') && !ft_strchr(line, '#') && ++ptr->l)
			write_link(ptr, line);
		else if (!ft_strchr(line, '#'))
			write_elem(ptr, line);
		else
			ft_printf("%s\n", line);
		if (line && *line && !(ft_strchr(line, '-') && !ft_strchr(line, '#')))
			ft_strdel(&line);
	}
	ft_printf(BLUE "END WRITTNG\n" NC);
}

void	mem_solv(int k, t_lemin *ptr, int m, t_ways *w)
{
	t_hashmap *tmp;
	t_hashmap *elem;

	tmp = w->way;
	elem = elembyi(ptr, k);
	if (m == 1)
	{
		tmp->i = m;
		tmp->name = ft_strdup(elem->name);
		tmp->x = elem->x;
		tmp->y = elem->y;
		tmp->next = NULL;
	}
	else
	{
		tmp->next = malloc(sizeof(t_hashmap));
		tmp->next->i = m;
		tmp->next->name = ft_strdup(elem->name);
		tmp->next->x = elem->x;
		tmp->next->y = elem->y;
		tmp->next->next = NULL;
		tmp = tmp->next;
	}
}

void	check_link(int k, t_lemin *ptr, int m, t_ways *w)
{
	if (k == ptr->end)
		return ;
	int i = 0;
	while (i < ptr->count_r)
	{
		if (ptr->links[k][i] == 1)
		{
			ptr->links[k][i] = m;
			ptr->links[i][k] = m;
			mem_solv(i, ptr, m - 1, w);
			check_link(i, ptr, m + 1, w);
		}
		i++;
	}
}

int		find_solutions(t_lemin *ptr)
{
	int	i;
	int	m;
	t_ways *w;

	m = 0;
	i = 0;
	ptr->solv = malloc(sizeof(t_ways));
	ptr->solv->way = malloc(sizeof(t_hashmap));
	ptr->solv->next = NULL;
	w = ptr->solv;
	while (i < ptr->count_r)
	{
		if (ptr->links[ptr->start][i] == 1 && (++m))
		{
			if (m != 1)
			{
				w->next = malloc(sizeof(t_ways));
				w->next->way = malloc(sizeof(t_hashmap));
				w->next->next = NULL;
			}
			ptr->links[ptr->start][i] = 2;
			ptr->links[i][ptr->start] = 2;
			mem_solv(i, ptr, 1, w);
			check_link(i, ptr, 3, w);
			if (m != 1)
				w = w->next;
		}
		i++;
	}
	i = 0;
	ptr->ways = 0;
	while (i < ptr->count_r)
		if (ptr->links[ptr->end][i++] != 0)
			ptr->ways++;
	ft_printf("ways = %d\n", ptr->ways);
	while (ptr->solv)
	{
		while (ptr->solv->way)
		{
			ft_printf("%s -> ", ptr->solv->way->name);
			ptr->solv->way = ptr->solv->way->next;
		}
		ft_printf("\n");
		ptr->solv = ptr->solv->next;
	}
	return (ptr->ways);
}

int		main(void)
{
	t_lemin	*ptr;
	char	*line;

	if (!(ptr = malloc(sizeof(t_lemin))))
		return (0);
	ptr->l = 0;
	ptr->count_r = 0;
	ptr->start = -1;
	ptr->end = -1;
	while (GNL(0, &line) > 0 && ft_printf("%s\n", line) && !(ptr->ants = ft_atoi(line)))
		ft_strdel(&line);
	if (!line || !is_valid(line, 0) || !ptr->ants)
		error(1, line);
	ft_printf("%s\n", line);
	ft_strdel(&line);
	read_map(ptr);
	if (ptr->l == 0)
		error(6, NULL);
	

	/* ------------------------------------------ */
	for (int j = 0; j < ptr->count_r; j++)
	{
		for (int k = 0; k < ptr->count_r; k++)
			ft_printf("%d ", ptr->links[j][k]);
		ft_printf("\n");
	}
	/* ------------------------------------------ */
	


	for (int i = 0; i < ptr->count_r; i++)
		ptr->links[i][ptr->start] = 0;
	if (!find_solutions(ptr))
		error(7, NULL);

	

	/* ----------------------------------------- */
	for (int j = 0; j < ptr->count_r; j++)
	{
		for (int k = 0; k < ptr->count_r; k++)
			ft_printf("%d ", ptr->links[j][k]);
		ft_printf("\n");
	}
	/* ---------------------------------------- */
	
	
	// while (1);
	return (0);
}