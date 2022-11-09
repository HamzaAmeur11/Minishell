/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pro_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:36:22 by hameur            #+#    #+#             */
/*   Updated: 2022/11/09 23:31:51 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_special(char c, int key)
{
	if (key == 1)
		return (SUCCESS);
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (R_OUT);
	else if (c == '<')
		return (R_INP);
	return (FAILDE);
}

int end_red(char *str, char c)
{
	if (c == '|')
		return (0);
	if (str[0] == c && str[1] == c)
		return (1);
	return (0);
}

char *add_special(char *str, char c, int *i)
{
	int sp = is_special(c, 0);
	if (sp == PIPE)
		return ((*i)++, ft_strdup((char *)"|"));
	else if (sp == R_INP && str[(*i) + 1] == c)
		return((*i) += 2, ft_strdup((char *)"<<"));
	else if (sp == R_INP && str[(*i) + 1] != c)
		return((*i)++, ft_strdup((char *)"<"));
	else if (sp == R_OUT && str[(*i) + 1] == c)
		return((*i) += 2, ft_strdup((char *)">>"));
	else if (sp == R_OUT && str[(*i) + 1] != c)
		return((*i)++, ft_strdup((char *)">"));
	return (NULL);
}

char *add_value(char *str, int *i)
{
	int j = *i;
	char s[1024];
	int key = 0;
	char c = 0;
	
	while (str[(*i)] != 0 && str[(*i)] == ' ')
		(*i)++;
	if (is_special(str[j], 0) != FAILDE)
		return(add_special(str, str[(*i)], i));
	j = 0;
	while (str[(*i)] != 0 && str[(*i)] == ' ')
		(*i)++;
	while (str[(*i)] != 0 && str[(*i)] != ' ' && is_special(str[(*i)], key) == FAILDE && key == 0)
	{
		if ((str[(*i)] == SQUOTE || str[(*i)] == DQUOTE) && c == 0)
		{
			c = str[(*i)];
			s[j++] = str[(*i)++];
			while (str[(*i)] != 0 && str[(*i)] != c)
				s[j++] = str[(*i)++];
			if (str[(*i)] == 0)
				return (printf("Error Quotes\n"), NULL);
			c = 0;
			s[j++] = str[(*i)++];
			continue ;
		}
		s[j++] = str[(*i)++];
	}
	s[j] = 0;
	while (str[(*i)] == ' ')
		(*i)++;
	return (ft_strdup(s));
}		

char **ft_realloc(char **ret, char *str)
{
	int i = 0;
	char **cmnds = NULL;
	if (ret == NULL)
	{
		cmnds = (char **)malloc(sizeof(char *) * 2);
		cmnds[0] = str;
		cmnds[1] = NULL;
		return (cmnds);
	}
	while (ret != NULL && ret[i++] != NULL);
	cmnds = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (ret[++i] != NULL)
		cmnds[i]  = ft_strdup(ret[i]);
	cmnds[i++] = str;
	cmnds[i] = NULL;
	ft_free(ret);
	return (cmnds);
	
}

char **split_pro_max(char *str)
{
	int i = 0;
	char **ret = NULL;
	while (str[i] != 0)
	{	
		char *string = add_value(str, &i);
		ret = ft_realloc(ret, string);
	}
	return(ret);
}


// int main(int ac, char **av)
// {
// 	char **str;
// 	int i = -1;
// 	while (1)
// 	{
// 		i = 0;
// 		char *line = readline("zebi=>");
// 		str = split_pro_max (line);
// 		while (str[i])
// 			printf("split pro max : %s\n", str[i++]);
// 		// str = ft_split(line, '|');
// 		// i = -1;
// 		// while (str != NULL && str[++i])
// 		// 	printf("%s\n", str[i]);
// 		// ft_free(str);
// 		printf("\n");
// 	}
// }
