
#include "lem-in.h"

int		is_valid(char *line, int bool)
{
	char *s;

	if (!bool)
	{
		while (*line)
			if (!ft_isdigit(*line++))
				return (0);
	}
	else
	{
		if (!(s = ft_strchr(line, ' ')) || !*(++s))
			return (0);
		while (*s && *s != ' ')
			if (!ft_isdigit(*s++))
				return (0);
		if (!*(++s))
			return (0);
		while (*s && *s != ' ')
			if (!ft_isdigit(*s++))
				return (0);
		if (*s)
			return (0);
	}
	return (1);
}

int		ibyname(t_lemin *ptr, char *name)
{
	t_hashmap	*tmp;
	int			c;

	c = 0;
	while (name[c] && name[c] != '-' && name[c] != ' ')
		c++;
	tmp = ptr->rooms;
	while (tmp)
	{
		if (name && !ft_strncmp(tmp->name, name, c))
			return (tmp->i);
		tmp = tmp->next;
	}
	return (-1);
}

void	create_elem(t_lemin *ptr, t_hashmap *tmp, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	tmp->name = ft_memalloc(sizeof(char) * (i + 1));
	tmp->next = NULL;
	if (ibyname(ptr, line) != -1)
		error(5, line);
	tmp->name = ft_strncpy(tmp->name, line, i);
	tmp->x = ft_atoi(ft_strchr(line, ' ') + 1);
	tmp->y = ft_atoi(ft_strrchr(line, ' ') + 1);
}

void	write_elem(t_lemin *ptr, char *line)
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
		if (!(tmp = malloc(sizeof(t_hashmap))))
			error(0, NULL);
		ptr->rooms = tmp;
	}
	else
	{
		if (!(tmp->next = malloc(sizeof(t_hashmap))))
			error(0, NULL);
		tmp = tmp->next;
	}
	create_elem(ptr, tmp, line);
	tmp->i = ptr->count_r;
	ptr->count_r++;
}

void	write_link(t_lemin *ptr, char *line)
{
	int i;

	i = 0;
	if (ptr->start == -1 || ptr->end == -1)
		error(4, NULL);
	ptr->links = malloc(sizeof(int*) * ptr->count_r);
	while (i < ptr->count_r)
		ptr->links[i++] = (int*)ft_memalloc(sizeof(int) * ptr->count_r);
	if (ibyname(ptr, line) == -1 || ibyname(ptr, ft_strchr(line, '-') + 1) == -1)
		error(3, line);
	ptr->links[ibyname(ptr, line)][ibyname(ptr, ft_strchr(line, '-') + 1)] = 1;
	ptr->links[ibyname(ptr, ft_strchr(line, '-') + 1)][ibyname(ptr, line)] = 1;
	ft_printf("%s\n", line);
	ft_strdel(&line);
	while (GNL(0, &line) > 0)
	{
		if (ft_strchr(line, '-') && !ft_strchr(line, '#'))
		{
			if (ibyname(ptr, line) == -1 || ibyname(ptr, ft_strchr(line, '-') + 1) == -1)
				error(3, line);
			ptr->links[ibyname(ptr, line)][ibyname(ptr, ft_strchr(line, '-') + 1)] = 1;
			ptr->links[ibyname(ptr, ft_strchr(line, '-') + 1)][ibyname(ptr, line)] = 1;
		}
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
}
