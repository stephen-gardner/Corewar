/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 13:40:51 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/04 14:52:42 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while ((s[i] != 0) && (s[i] == c))
			i++;
		if (i < ft_strlen(s))
			n++;
		while ((s[i] != 0) && (s[i] != c))
			i++;
	}
	return (n);
}

static int	copy_words(char const *s, char c, char **a)
{
	size_t	i;
	size_t	k;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while ((s[i] != 0) && (s[i] == c))
			i++;
		if (i == ft_strlen(s))
			break ;
		k = i;
		while ((s[i] != 0) && (s[i] != c))
			i++;
		if ((a[j] = ft_memalloc((i - k + 1) * sizeof(char))) == NULL)
			return (0);
		ft_strncpy(a[j++], &s[k], i - k);
	}
	a[j] = NULL;
	return (1);
}

char		**ft_strsplit2(char const *s, char c)
{
	char	**arr;
	int		cw;

	cw = count_words(s, c);
	arr = (char **)ft_memalloc((cw + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (cw == 0)
	{
		arr[0] = NULL;
		return (arr);
	}
	if (!copy_words(s, c, arr))
		return (NULL);
	return (arr);
}
