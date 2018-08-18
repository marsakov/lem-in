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

char	*namebyi(t_lemin *ptr, int i)
{
	t_hashmap	*tmp;

	tmp = ptr->rooms;
	while (tmp)
	{
		if (tmp->i == i)
			return (tmp->name);
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

int		check_link(int n, int k, t_lemin *ptr, int m)
{
	if (n == ptr->end)
	{
		ft_printf("%s\n", namebyi(ptr, n));
		return (1);
	}
	if (ptr->links[n][k] != 1)
		return (0);

	ft_printf("%s -> ", namebyi(ptr, n));
	ptr->links[n][k] = m;
	ptr->links[k][n] = 0;
	int i = 0;
	while (i < ptr->count_r)
		check_link(k, i++, ptr, m + 1);
	return (1);
}

int		find_solutions(t_lemin *ptr)
{
	int	i;

	i = 0;
	ptr->ways = 0;
	while (i < ptr->count_r)
	{
		if (i != ptr->end)
			if (check_link(ptr->start, i, ptr, 2))
				ptr->ways++;
		i++;
	}
	ft_printf("solutions = %d\n", ptr->ways);
	return (1);
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
	for (int j = 0; j < ptr->count_r; j++)
	{
		for (int k = 0; k < ptr->count_r; k++)
			ft_printf("%d ", ptr->links[j][k]);
		ft_printf("\n");
	}
	for (int i = 0; i < ptr->count_r; i++)
		ptr->links[i][ptr->start] = 0;
	find_solutions(ptr);
	for (int j = 0; j < ptr->count_r; j++)
	{
		for (int k = 0; k < ptr->count_r; k++)
			ft_printf("%d ", ptr->links[j][k]);
		ft_printf("\n");
	}
	// while (1);
	return (0);
}