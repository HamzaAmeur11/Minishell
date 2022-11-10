/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:08:34 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 19:11:03 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_file(char *str)
{
	if (ft_strncmp(str, "./", 1) == SUCCESS)
		return (FAILDE);
	return (SUCCESS);
}

void	print_error(char *cmnd, int i)
{
	ft_putstr_fd(2, cmnd);
	if (i == 0)
		ft_putstr_fd(2, (char *)": No such file or directory\n");
	else if (i == 1)
		ft_putstr_fd(2, (char *)": command not found\n");
}
