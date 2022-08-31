/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:58:17 by hameur            #+#    #+#             */
/*   Updated: 2022/08/31 00:14:29 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strdup(char *s1)
{
	char	*p;
	int		i;

	i = ft_strlen(s1);
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		p[i] = s1[i];
	p[i] = 0;
	return (p);
}

int ft_strlen(char *str)
{
	int i = -1;
		while (str[++i] != 0)
			;
	return (i);
}
char *ft_strlcat(char *s1, char *s2)
{
	int i;
	int	j;
	char *str;
	 
	j = -1;
	i = ft_strlen(s1);
	i += ft_strlen(s2);
	str = (char*)malloc(i + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		str[i] = s1[i];
	while (s2[++j] != 0)
		str[i++] = s2[j];
	return (str);
}

int	ft_strncmp(char *s1, char *s2, int i)
{
	int	x;

	x = 0;
	while (s1[x] != 0 && s2[x] != 0 && s1[x] == s2[x] && i > x)
		x++;
	if (s1[x] == s2[x] && i == x)
		return (0);
	return (s1[x] - s2[x]);
}

// int main(int ac, char **av, char **env)
// {
// 	// t_list *tst;

// 	// tst = (t_list *)malloc(sizeof(t_list));
// 	// tst->env = fct(env);
// 	(void)ac;
// 	char **argve;
// 	argve = (char **)malloc(4 * sizeof(char *));
// 	argve[0] = ft_strdup(av[1]);
// 	argve[1] = ft_strdup(av[2]);
// 	//argve[2] = ft_strdup(av[3]);
// 	argve[2] = NULL;
// 	int i = check_path(argve , env);
// 	printf(">>>>>>>>>%d\n", i);
// 	while(1);
// }