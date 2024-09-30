/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/30 21:01:22 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*ft_init_cmd(int type)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	if (!cmd)
		panic("malloc");
	cmd->type = type;
	return ((t_cmd *)cmd);
}

void	init_cmd_args(t_cmd *cmd)
{
	cmd->argv = malloc(sizeof(char *) * 11);
	if (!cmd->argv)
		panic("malloc");
	bzero(cmd->argv, 11 * sizeof(char *));
}

void	add_argument(t_cmd *cmd, char *q, char *eq, int *argc)
{
	cmd->argv[*argc] = ft_substring(q, eq);
	(*argc)++;
	if (*argc >= MAXARGS)
		panic("too many args");
	cmd->argv[*argc] = NULL;
}
