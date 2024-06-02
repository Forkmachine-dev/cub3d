/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_duplist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:02:31 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:54:18 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_to_dup_checklist(t_duplication_checklist **list, char *component)
{
	t_duplication_checklist	*new_node;
	t_duplication_checklist	*tmp;

	new_node = malloc(sizeof(t_duplication_checklist));
	new_node->component = component;
	new_node->next = NULL;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	dup_checklist(t_duplication_checklist **list, char *component)
{
	t_duplication_checklist	*tmp;
	int						len;

	len = ft_strlen(component);
	tmp = *list;
	while (tmp)
	{
		if (ft_strncmp(tmp->component, component, len + 1) == 0)
			return (1);
		tmp = tmp->next;
	}
	add_to_dup_checklist(list, component);
	return (0);
}

void	free_duplication_checklist(
	t_duplication_checklist *duplication_checklist)
{
	t_duplication_checklist	*tmp;

	while (duplication_checklist)
	{
		tmp = duplication_checklist;
		duplication_checklist = duplication_checklist->next;
		free(tmp);
	}
}
