/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:42:01 by hameur            #+#    #+#             */
/*   Updated: 2022/08/30 21:14:52 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	nbr_mots(char const *s, char c)
{
	int	i;
	int	nbr_mots;

	i = 0;
	nbr_mots = 0;
	if (s[0] != c && s[0])
		nbr_mots++;
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != 0)
			{
				nbr_mots++;
				i++;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (nbr_mots);
}

char *ft_copy(char *str, int start, int end)
{
	char *ret;
	int	i = 0;
	int j = start;
	ret = (char *)malloc((end - start + 1) * sizeof(char));
	while (j < end)
		ret[i++] = str[j++];
	ret[i] = 0;
	return (ret);
}

int find_char(char *str, int pos, char c, int id)
{
	while(str[pos] == c)
		pos++;
	while (str[pos] != c && str[pos] != 0)
		pos++;
	if (id == 2)
	{
		while (str[pos + 1] == c)
			pos++;
	}
	if (str[pos] == 0 && id == 0)
		return(0);
	return (pos);
}

static char	**ft_remplissage(char *s, char **copy, char c)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (s[start] == c)
		start++;
	end = 0;
	end = find_char(s, end, c, 0);
	while (end != 0)
	{
		copy[i++] = ft_copy(s, start, end);
		end = find_char(s, end + 1, c, 0);
		start = find_char(s, start, c, 2) + 1;
	}
	end =  find_char(s, start + 1, c, 2);
	if ((size_t)start != strlen(s))
		copy[i++] = ft_copy(s, start, end);
	copy[i] = NULL;
	return (copy);
}

char	**ft_split(char *s, char c)
{
	char	**copy;

	if (!s)
		return (NULL);
	if (!*s)
	{
		copy = (char **)malloc (sizeof (char *) * 1);
		if (!copy)
			return (NULL);
		copy[0] = NULL;
		return (copy);
	}
	copy = (char **)malloc(sizeof(char *) * (nbr_mots(s, c) + 1));
	if (!copy)
		return (NULL);
	return (ft_remplissage(s, copy, c));
}