/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:22:02 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/08 11:21:06 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*alloc_cmd(t_llist *list, char *line_read)
{
	list->index = 0;
	list->new_cmd = 1;
	while (line_read[list->index])
	{
		while (line_read[list->index] == ' ')
			list->index++;
		if (line_read[list->index] == '<' || line_read[list->index] == '>')
		{
			if (list->new_cmd == 1)
				list = alloc_redi_cmd(list, line_read);
			else
				list = alloc_redi_arg(list, line_read);
		}
		else if (line_read[list->index] == '|')
			list = alloc_pipe(list);
		else if ((line_read[list->index] == '\"'
				|| line_read[list->index] == '\'') && list->new_cmd == 1)
			list = alloc_str(list, line_read);
		else if (list->new_cmd == 0 && line_read[list->index])
			list = alloc_arg(list, line_read);
		else if (line_read[list->index])
		{
			list = alloc_str(list, line_read);
		}
	}
	list = sort_redi(list);
	list = check_and_add_last_redi(list);
	list = alloc_heredoc(list, line_read);
	return (list);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line_read;
	t_llist		*list;

	(void)argc;
	(void)argv;
	line_read = NULL;
	list = init_llist(envp);
	while (1)
	{
		line_read = rl_gets(line_read);
		//line_read = ft_strdup("echo test");
		if (line_read)
		{
			if (check_syntaxe(line_read) == 1)
			{
				line_read = replace_home(list->first_env, line_read);
				line_read = replace_dollar(line_read, list->first_env, 0);
				if (line_read[0])
				{
					list = alloc_cmd(list, line_read);
					free(line_read);
					line_read = NULL;
					if (list->first_cmd)
					{
						list = del_redirection(list);
						print_t_cmd(list->first_cmd);
						fctnl_manager(list);
						//break;
					}
				}
				//if_tmpdelete(list);
				list = free_llist_cmd(list);
			}
		}
	}
	free_llist(list, line_read);
	rl_clear_history();
	return (0);
}
