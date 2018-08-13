/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 22:54:44 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/02 20:15:12 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int		*ft_countalph(char const *s, char c, int words)
{
	int		*wordslen;
	int		counter;
	int		i_words;
	int		i;

	i = 0;
	i_words = 0;
	counter = 0;
	if (!(wordslen = (int *)malloc(sizeof(int) * words)))
		return (NULL);
	while (s[i] && words)
	{
		if (s[i] != c)
		{
			counter++;
			if (s[i + 1] == c || !s[i + 1])
			{
				wordslen[i_words++] = counter + 1;
				counter = 0;
				words--;
			}
		}
		i++;
	}
	return (wordslen);
}

static	int		ft_countwords(char const *s, char c)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			words++;
		i++;
	}
	return (words);
}

static	void	ft_fillarr(char const *s, char c, char **arr)
{
	int		i;
	int		i_words;
	int		i_alph;

	i = 0;
	i_words = 0;
	i_alph = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			arr[i_words][i_alph++] = s[i];
			if (!s[i + 1] || s[i + 1] == c)
			{
				arr[i_words][i_alph] = '\0';
				i_alph = 0;
				i_words++;
			}
		}
		i++;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**arr;
	int		words;
	int		i_words;
	int		*wordslen;

	i = 0;
	i_words = 0;
	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	wordslen = ft_countalph(s, c, words);
	if (!(arr = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (i_words < words)
	{
		if (!(arr[i_words] = (char *)malloc(sizeof(char) * wordslen[i_words])))
			return (NULL);
		i_words++;
	}
	ft_fillarr(s, c, arr);
	arr[i_words] = NULL;
	return (arr);
}
