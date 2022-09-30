/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:41:59 by hmeur             #+#    #+#             */
/*   Updated: 2022/09/25 02:06:31 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini.h"

void	free_list(t_list **root, t_list *node)
{
	if (node == NULL)
		return ;
	free_list(root, node->next);
    free(node->str);
	free(node);
}



int is_word(char *str)
{
    int i;

    i = -1;
    while (str[++i] != 0)
    {
        if (str[i] == '|' || str[i] == '>' || str[i] == '<')
            return (FAILDE);
    }
    return (SUCCESS);
}

int check_type(char *str)
{
    int i = 0;
    if (is_word(str) == SUCCESS)
        return (WORD);
    else if (str[0] == '|' && str[1] == 0)
        return (PIPE);
    else if (str[0] == '>' && str[1] == 0)
        return (R_OUT);
    else if (str[0] == '<' && str [1] == 0)
        return(R_INP);
    else if (str[0] == '>' && str[1] == '>' && str[2] == 0)
        return (DR_OUT);
    else if (str[0] == '<' && str[1] == '<' && str[2] == 0)
        return (DR_INP);
    return (FAILDE);
}

t_list *new_list(char *str)
{
    t_list  *node;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->str = ft_strdup(str);
    node->type = check_type(str);
    if (node->type == FAILDE)
        return (NULL);
    node->next = NULL;
    return (node);
}


int add_back_list(t_list **head, t_list *new_node)
{
    t_list *temp = *head;

    if (new_node == NULL)
        return (printf("error add_back_list\n"), FAILDE);
    if (temp == NULL)
        return(*head = new_node, SUCCESS) ;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    return (SUCCESS);
}

int init_list(t_list **head, char *str)
{
    char    **cmnd;
    int     i;
    cmnd = ft_split(str, ' ');
    i = 0;
    *head = NULL;
    while (cmnd[i] != NULL)
    {
        if (add_back_list(head, new_list(cmnd[i++])) != SUCCESS)
            return (FAILDE);//free
    }
    ft_free(cmnd);
    return (SUCCESS);
}
