/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:20:32 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/21 21:20:36 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_valid(char *line, int bool)
{
	char *s;

	s = NULL;
	if (!bool)
	{
		(line[0] == '+') ? line++ : 0;
		while (*line)
			(!ft_isdigit(*line++)) ? error(1, line) : 0;
	}
	else
	{
		if (line[0] == 'L' || !(s = ft_strchr(line, ' ')) || !*(++s))
			error(2, line);
		while (line[bool - 1] && line[bool - 1] != *s)
			(line[bool++ - 1] == '-') ? error(2, line) : 0;
		(*s == '+' || *s == '-') ? s++ : 0;
		while (*s && *s != ' ')
			(!ft_isdigit(*s++)) ? error(2, line) : 0;
		(!*(++s)) ? error(2, line) : 0;
		(*s == '+' || *s == '-') ? s++ : 0;
		while (*s && *s != ' ')
			(!ft_isdigit(*s++)) ? error(2, line) : 0;
		(*s) ? error(2, line) : 0;
	}
	return (1);
}

int		ibyn(t_lemin *ptr, char *name)
{
	t_hashmap	*tmp;
	char		*name2;
	int			c;

	c = 0;
	while (name[c] && name[c] != '-' && name[c] != ' ')
		c++;
	name2 = ft_memalloc(sizeof(char) * c);
	name2 = ft_strncpy(name2, name, c);
	tmp = ptr->rooms;
	while (tmp)
	{
		if (name2 && !ft_strcmp(tmp->name, name2))
		{
			free(name2);
			return (tmp->i);
		}
		tmp = tmp->next;
	}
	free(name2);
	return (-1);
}

void	create_elem(t_lemin *ptr, t_hashmap *tmp, char *line)
{
	int			i;
	intmax_t	check;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	tmp->name = ft_memalloc(sizeof(char) * (i + 1));
	tmp->next = NULL;
	if (ibyn(ptr, line) != -1)
		error(5, line);
	tmp->name = ft_strncpy(tmp->name, line, i);
	check = ft_atointmxt(ft_strchr(line, ' ') + 1);
	if (check > 2147483648 || check < -2147483647)
		error(2, line);
	tmp->x = (int)check;
	check = ft_atointmxt(ft_strrchr(line, ' ') + 1);
	if (check > 2147483648 || check < -2147483647)
		error(2, line);
	tmp->y = (int)check;
	tmp->ant = 0;
}

int		write_elem(t_lemin *ptr, char *line)
{
	int			i;
	t_hashmap	*tmp;

	i = 0;
	if (!is_valid(line, 1))
		error(2, line);
	ft_printf("%s\n", line);
	tmp = ptr->rooms;
	while (i++ < ptr->count_r && tmp->next)
		tmp = tmp->next;
	if (!(i = 0) && !ptr->count_r)
	{
		!(tmp = malloc(sizeof(t_hashmap))) ? error(0, NULL) : 0;
		ptr->rooms = tmp;
	}
	else
	{
		!(tmp->next = malloc(sizeof(t_hashmap))) ? error(0, NULL) : 0;
		tmp = tmp->next;
	}
	create_elem(ptr, tmp, line);
	tmp->i = ptr->count_r;
	coord_exist(ptr, tmp) ? error(8, line) : 0;
	return (++ptr->count_r);
}

void	write_link(t_lemin *p, char *line, int i)
{
	if (p->start == -1 || p->end == -1)
		error(4, NULL);
	p->links = malloc(sizeof(int*) * p->count_r);
	while (i < p->count_r)
		p->links[i++] = (int*)ft_memalloc(sizeof(int) * p->count_r);
	while (line)
	{
		if (!ft_strchr(line, '#') && ft_strchr(line, '-'))
		{
			if (line[0] == '-' || line[ft_strlen(line) - 1] == '-' ||
				ft_strchr(line, '-') != ft_strrchr(line, '-') ||
			(ibyn(p, line) == -1 || ibyn(p, ft_strchr(line, '-') + 1) == -1))
				error(3, line);
			if (ibyn(p, line) == ibyn(p, ft_strchr(line, '-') + 1))
				error(9, line);
			p->links[ibyn(p, line)][ibyn(p, ft_strchr(line, '-') + 1)] = 1;
			p->links[ibyn(p, ft_strchr(line, '-') + 1)][ibyn(p, line)] = 1;
		}
		else if (!ft_strlen(line) || !ft_strchr(line, '#'))
			error(9, line);
		ft_printf("%s\n", line);
		free(line);
		if (GNL(0, &line) < 1)
			break ;
	}
}
