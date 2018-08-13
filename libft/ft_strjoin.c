/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <msakovyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:23:22 by msakovyc          #+#    #+#             */
/*   Updated: 2018/03/27 18:06:18 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!newstr)
		return (0);
	while (*s1)
		*newstr++ = (char)*s1++;
	while (*s2)
		*newstr++ = (char)*s2++;
	*newstr = '\0';
	return (newstr - s1len - s2len);
}
