/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:53:32 by thbierne          #+#    #+#             */
/*   Updated: 2022/07/14 17:04:08 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_redir(t_arg *arg)
{
	int		x;
	t_arg	*tmp;

	x = 0;
	tmp = arg;
	while (tmp->next_arg)
	{
		if (tmp->nbr == -1 || tmp->nbr == -2)
			x++;
		tmp = tmp->next_arg;
	}
	return (x);
}

t_arg	**del_redir(t_arg *arg)
{
	t_arg *tmp;
	int		i;
	t_arg	**rtn;

	i = count_redir(arg);
	tmp = arg;
	rtn = &tmp;
	while (i > 1 && (tmp->nbr == -1 || tmp->nbr == -2))
	{
		larg_del_first(&tmp);
		larg_del_first(&tmp);
		i--;
	}
	while (tmp->next_arg && i > 1)
	{
		if (tmp->next_arg->nbr == -1 || tmp->next_arg->nbr == -2)
		{
			larg_del_next(&tmp);
			larg_del_next(&tmp);
			i--;
		}
		else
			tmp = tmp->next_arg;
	}
	return (rtn);
}

int		ft_redirection(char *str, char *filename)
{
	int	file;

	if (!filename)
		return (-1);
	if (access(filename, R_OK | W_OK) != 0)
		file = open(filename, O_CREAT | O_RDWR);
	else
		file = open(filename, O_RDWR | O_TRUNC);
	if (file == -1)
		return (-1);
	write(file, str, len(str));
	close(file);
	return (0);
}

int		ft_redirection_appen(char *str, char *filename)
{
	char	tmp;
	char	*join;
	char	*cpy;
	int		file;

	if (!filename)
		return (-1);
	if (access(filename, R_OK | W_OK) != 0)
	{
		ft_redirection(str, filename);
		return (0);
	}
	else
		file = open(filename, O_RDWR);
	if (file == -1)
		return (-1);
	join = NULL;
	while (read(file, &tmp, 1) > 0)
		{
			if (!join)
			{
				join = (char *)malloc(sizeof(char) * 2);
				join[0] = tmp;
				join[1] = '\0';
			}
			else
				join = join_char(join, tmp);
		}
	close(file);
	file = open(filename,O_RDONLY | O_WRONLY | O_TRUNC);
	cpy = ft_strjoin(join, "\0");
	free(join);
	join = ft_strjoin(cpy, str);
	free (cpy);
	write(file, join, len(join));
	free(join);
	close(file);
	return (0);
}

char	*ft_redirection_out(char *filename)
{
	int		file;
	char	*join;
	char	tmp;

	if (!filename)
		return (NULL);
	if (access(filename, R_OK) != 0)
		return (NULL);
	file = open(filename, O_RDWR);
	if (file == -1)
		return (NULL);
	join = NULL;
	while (read(file, &tmp, 1) > 0)
		{
			if (!join)
			{
				join = (char *)malloc(sizeof(char) * 2);
				join[0] = tmp;
				join[1] = '\0';
			}
			else
				join = join_char(join, tmp);
		}
	close(file);
	return (join);
}