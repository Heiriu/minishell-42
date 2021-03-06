/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fctnl_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:32:21 by avillar           #+#    #+#             */
/*   Updated: 2022/07/14 17:02:51 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_fd_name(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp->next_arg)
	{
		if (tmp->nbr > -3 && tmp->nbr < 0)
			break;
		tmp = tmp->next_arg;
	}
	if (tmp->next_arg)
	{
		tmp = tmp->next_arg;
		return (tmp->arg);
	}
	else
		return (0);
}

int	check_redir(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp)
	{
		if (tmp->nbr < 0)
			return (tmp->nbr);
		tmp = tmp->next_arg;
	}
	return (0);
}

int	fctnl_manager(t_llist *list)
{
	if (strncmp(list->first_cmd->cmd, "echo", 4) == 0)
		return (ft_echo(list->first_cmd));
	if (strncmp(list->first_cmd->cmd, "cd", 2) == 0)
		return (ft_cd(list));
	if (strncmp(list->first_cmd->cmd, "pwd", 3) == 0)
		return (ft_pwd(list));
	if (strncmp(list->first_cmd->cmd, "export", 6) == 0)
		return (ft_fullexport(&list));
	if (strncmp(list->first_cmd->cmd, "unset", 5) == 0)
		return (ft_unset(list));
	if (strncmp(list->first_cmd->cmd, "env", 3) == 0)
		return (ft_penv(list));
	if (strncmp(list->first_cmd->cmd, "exit", 4) == 0)
		return (ft_exit(list));
	else
		return (ft_exec_others(list));
}
