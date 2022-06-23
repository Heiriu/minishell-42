/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:19:50 by avillar           #+#    #+#             */
/*   Updated: 2022/06/23 11:02:32 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_llist *list)
{
	char	*path;
	t_arg	*tmp;

	if (list->first_cmd->next_arg)
		tmp = list->first_cmd->next_arg;
	else
		tmp = NULL;
	(void)tmp;
	path = NULL;
	path = getcwd(path, 0);
	printf("%s\n", path);
	return (0);
}